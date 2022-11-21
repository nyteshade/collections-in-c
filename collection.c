#include "collection.h"
#include "lists.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Collection *NECollectionCreate(void) {
    Collection *self = calloc(1, sizeof(Collection));
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
    return self;
}

void NECollectionFree(Collection *self) {
    NEDestroyList(self->list);
    free(self);
}

void NECollectionAdd(Collection *self, KeyValue value) {
  CollectionItem *item = 0L;

  item = calloc(1, sizeof(CollectionItem));
  if (item) {
    item->keyValue = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddByte(Collection *self, NEByte value) {
  CollectionItem *item = 0L;

  item = calloc(1, sizeof(CollectionItem));
  if (item) {
    item->keyValue.type = NE_BYTE;
    item->keyValue.data.byte = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddInteger(Collection *self, NEInteger value) {
  CollectionItem *item = 0L;

  item = calloc(1, sizeof(CollectionItem));
  if (item) {
    item->keyValue.type = NE_INTEGER;
    item->keyValue.data.integer = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddDecimal(Collection *self, NEDecimal value) {
  CollectionItem *item = 0L;

  item = calloc(1, sizeof(CollectionItem));
  if (item) {
    item->keyValue.type = NE_DECIMAL;
    item->keyValue.data.decimal = value;
    self->list->addNode(self->list, (NENode *)item);
  }
} 

void NECollectionAddString(Collection *self, const NEStrPtr value) {
  CollectionItem *item = 0L;

  item = calloc(1, sizeof(CollectionItem));
  if (item) {
    item->keyValue.type = NE_STRING;
    item->keyValue.data.string = strdup(value);
    item->keyValue.length = strlen(value);
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddPointer(Collection *self, NEPointer value) {
  CollectionItem *item = 0L;

  item = calloc(1, sizeof(CollectionItem));
  if (item) {
    item->keyValue.type = NE_POINTER;
    item->keyValue.data.pointer = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

KeyValue *NECollectionFindByte(Collection *self, NEByte value) {
  CollectionItem *item = NULL;
  NEForEachNodeDo(CollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_BYTE && item->keyValue.data.byte == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}

KeyValue *NECollectionFindInteger(Collection *self, NEInteger value) {
  CollectionItem *item = NULL;
  NEForEachNodeDo(CollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_INTEGER && item->keyValue.data.integer == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}
KeyValue *NECollectionFindDecimal(Collection *self, NEDecimal value) {
  CollectionItem *item = NULL;
  NEForEachNodeDo(CollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_DECIMAL && item->keyValue.data.decimal == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}
KeyValue *NECollectionFindString(Collection *self, const NEStrPtr value) {
  CollectionItem *item = NULL;
  NEForEachNodeDo(CollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_STRING && strcmp(item->keyValue.data.string, value) == 0) {
      return &item->keyValue;
    }
  }
  return NULL;
}
KeyValue *NECollectionFindPointer(Collection *self, NEPointer value) {
  CollectionItem *item = NULL;
  NEForEachNodeDo(CollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_POINTER && item->keyValue.data.pointer == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}

KeyValue *NECollectionAt(Collection *self, NEInteger index) {
  CollectionItem *item = (CollectionItem *)NEListGetNodeAtIndex(self->list, index);
  if (item) {
    return &item->keyValue;
  }
  return NULL;
}
NEInteger NECollectionCount(Collection *self) {
  return NEListSize(self->list);
}
void NECollectionClear(Collection *self) {
  NEDestroyList(self->list);
  self->list = NECreateList();
}
void NECollectionSort(Collection *self, NECollectionSorter sorter) {
  return;
}
