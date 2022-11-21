#include "collection.h"
#include "lists.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

NECollection *NECollectionCreate(void) {
    NECollection *self = calloc(1, sizeof(NECollection));
    self->list = NECreateList();
    self->add = NECollectionAdd;
    self->addByte = NECollectionAddByte;
    self->addInteger = NECollectionAddInteger;
    self->addDecimal = NECollectionAddDecimal;
    self->addString = NECollectionAddString;
    self->addPointer = NECollectionAddPointer;
    self->findByte = NECollectionFindByte;
    self->findInteger = NECollectionFindInteger;
    self->findDecimal = NECollectionFindDecimal;
    self->findString = NECollectionFindString;
    self->findPointer = NECollectionFindPointer;
    self->at = NECollectionAt;
    self->count = NECollectionCount;
    self->clear = NECollectionClear;
    self->sort = NECollectionSort;
    self->map = NECollectionMap;
    self->filter = NECollectionFilter;
    self->forEach = NECollectionForEach;
    return self;
}

void NECollectionFree(NECollection *self) {
    NEDestroyList(self->list);
    free(self);
}

void NECollectionAdd(NECollection *self, KeyValue value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddByte(NECollection *self, NEByte value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_BYTE;
    item->keyValue.data.byte = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddInteger(NECollection *self, NEInteger value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_INTEGER;
    item->keyValue.data.integer = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddDecimal(NECollection *self, NEDecimal value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_DECIMAL;
    item->keyValue.data.decimal = value;
    self->list->addNode(self->list, (NENode *)item);
  }
} 

void NECollectionAddString(NECollection *self, const NEStrPtr value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_STRING;
    item->keyValue.data.string = strdup(value);
    item->keyValue.length = strlen(value);
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddPointer(NECollection *self, NEPointer value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_POINTER;
    item->keyValue.data.pointer = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionForEach(NECollection *self, NECollectionIterator iterator) {
  NECollectionItem *item = NULL;
  NEULong index = 0;

  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    iterator(item->keyValue, index);
    index++;
  }
}

NECollection *NECollectionFilter(NECollection *self, NECollectionValidator validator) {
  NECollection *newCollection = NECollectionCreate();
  NECollectionItem *item = NULL;
  NEULong index = 0;

  if (!newCollection) {
    return NULL;
  }

  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    NEBool result = validator(item->keyValue, index);

    if (result) {
      newCollection->add(newCollection, item->keyValue);
    }

    index++;
  }

  return newCollection;
}

NECollection *NECollectionMap(NECollection *self, NECollectionMapper mapper) {
  NECollection *newCollection = NECollectionCreate();
  NECollectionItem *item = NULL;
  NEULong index = 0;

  if (!newCollection) {
    return NULL;
  }

  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    NECollectionMapResult result = mapper(item->keyValue, index);

    switch (result.decision) {
      case NE_IGNORE:
        newCollection->add(newCollection, item->keyValue);
        break;

      case NE_DROP:
        break;

      case NE_TRANSFORM: 
        newCollection->add(newCollection, result.value);
        break;
    }

    index++;
  }

  return newCollection;
}

KeyValue *NECollectionFindByte(NECollection *self, NEByte value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_BYTE && item->keyValue.data.byte == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}

KeyValue *NECollectionFindInteger(NECollection *self, NEInteger value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_INTEGER && item->keyValue.data.integer == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}
KeyValue *NECollectionFindDecimal(NECollection *self, NEDecimal value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_DECIMAL && item->keyValue.data.decimal == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}
KeyValue *NECollectionFindString(NECollection *self, const NEStrPtr value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_STRING && strcmp(item->keyValue.data.string, value) == 0) {
      return &item->keyValue;
    }
  }
  return NULL;
}
KeyValue *NECollectionFindPointer(NECollection *self, NEPointer value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_POINTER && item->keyValue.data.pointer == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}

KeyValue *NECollectionAt(NECollection *self, NEInteger index) {
  NECollectionItem *item = (NECollectionItem *)NEListGetNodeAtIndex(self->list, index);
  if (item) {
    return &item->keyValue;
  }
  return NULL;
}
NEInteger NECollectionCount(NECollection *self) {
  return NEListSize(self->list);
}
void NECollectionClear(NECollection *self) {
  NEDestroyList(self->list);
  self->list = NECreateList();
}
void NECollectionSort(NECollection *self, NECollectionSorter sorter) {
  return;
}
