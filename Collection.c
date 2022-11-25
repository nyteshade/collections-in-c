#include "Collection.h"
#include "Lists.h"
#include "Map.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void _NECollectionNodeFreer(NENode *node);

NECollection *NECollectionCreate(void) {
    NECollection *self = calloc(1, sizeof(NECollection));
    self->list = NECreateList();
    self->add = NECollectionAdd;
    self->addByte = NECollectionAddByte;
    self->addInteger = NECollectionAddInteger;
    self->addDecimal = NECollectionAddDecimal;
    self->addString = NECollectionAddString;
    self->addPointer = NECollectionAddPointer;
    self->addCollection = NECollectionAddCollection;
    self->addMapNode = NECollectionAddMapNode;
    self->addMap = NECollectionAddMap;
    self->findByte = NECollectionFindByte;
    self->findInteger = NECollectionFindInteger;
    self->findDecimal = NECollectionFindDecimal;
    self->findString = NECollectionFindString;
    self->findPointer = NECollectionFindPointer;
    self->findCollection = NECollectionFindCollection;
    self->findMapNode = NECollectionFindMapNode;
    self->findMap = NECollectionFindMap;
    self->at = NECollectionAt;
    self->byteAt = NECollectionByteAt;
    self->integerAt = NECollectionIntegerAt;
    self->decimalAt = NECollectionDecimalAt;
    self->stringAt = NECollectionStringAt;
    self->pointerAt = NECollectionPointerAt;
    self->collectionAt = NECollectionCollectionAt;
    self->mapNodeAt = NECollectionMapNodeAt;
    self->mapAt = NECollectionMapAt;
    self->count = NECollectionCount;
    self->clear = NECollectionClear;
    self->sort = NECollectionSort;
    self->filter = NECollectionFilter;
    self->forEach = NECollectionForEach;
    self->map = NECollectionMap;
    return self;
}

void _NECollectionNodeFreer(NENode *node) {
  NECollectionItem *item = (NECollectionItem *)node;

  if (item->keyValue.type == NE_COLLECTION) {
    NECollectionFree(item->keyValue.data.collection);
    item->keyValue.data.collection = NULL;
  }
}

void NECollectionFree(NECollection *self) {
    NEDestroyListCustom(self->list, _NECollectionNodeFreer);
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

void NECollectionAddCollection(NECollection *self, NECollection *value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_COLLECTION;
    item->keyValue.data.collection = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddMapNode(NECollection *self, NEMapNode *value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_MAPNODE;
    item->keyValue.data.mapNode = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionAddMap(NECollection *self, NEMap *value) {
  NECollectionItem *item = 0L;

  item = calloc(1, sizeof(NECollectionItem));
  if (item) {
    item->keyValue.type = NE_MAP;
    item->keyValue.data.map = value;
    self->list->addNode(self->list, (NENode *)item);
  }
}

void NECollectionForEach(NECollection *self, NECollectionIterator iterator) {
  NECollectionItem *item = NULL;
  NEULong index = 0;

  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    iterator(&item->keyValue, index);
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
    NEBool result = validator(&item->keyValue, index);

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
    NECollectionMapResult result = mapper(&item->keyValue, index);

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
KeyValue *NECollectionFindString(NECollection *self, const NEStrPtr value, NEBool caseSensitive) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (
      item->keyValue.type == NE_STRING &&
      (caseSensitive
        ? strcmp(item->keyValue.data.string, value)
        : strcasecmp(item->keyValue.data.string, value)
      ) == 0
    ) {
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
KeyValue *NECollectionFindCollection(NECollection *self, NECollection *value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_COLLECTION && item->keyValue.data.collection == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}

KeyValue *NECollectionFindMapNode(NECollection *self, NEMapNode *value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_MAPNODE && item->keyValue.data.mapNode == value) {
      return &item->keyValue;
    }
  }
  return NULL;
}

KeyValue *NECollectionFindMap(NECollection *self, NEMap *value) {
  NECollectionItem *item = NULL;
  NEForEachNodeDo(NECollectionItem*, self->list->head, item) {
    if (item->keyValue.type == NE_MAP && item->keyValue.data.map == value) {
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

NECollectionByteAtResult NECollectionByteAt(NECollection *self, NEInteger index) {
  NECollectionByteAtResult result = {NEFalse, 0};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_BYTE) {
    result.value = item->data.byte;
    result.found = NETrue;
  }
  return result;
}

NECollectionIntegerAtResult NECollectionIntegerAt(NECollection *self, NEInteger index) {
  NECollectionIntegerAtResult result = {NEFalse, 0};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_INTEGER) {
    result.value = item->data.integer;
    result.found = NETrue;
  }
  return result;
}

NECollectionDecimalAtResult NECollectionDecimalAt(NECollection *self, NEInteger index) {
  NECollectionDecimalAtResult result = {NEFalse, 0};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_DECIMAL) {
    result.value = item->data.decimal;
    result.found = NETrue;
  }
  return result;
}

NECollectionStringAtResult NECollectionStringAt(NECollection *self, NEInteger index) {
  NECollectionStringAtResult result = {NEFalse, NULL};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_STRING) {
    result.value = item->data.string;
    result.found = NETrue;
  }
  return result;
}

NECollectionPointerAtResult NECollectionPointerAt(NECollection *self, NEInteger index) {
  NECollectionPointerAtResult result = {NEFalse, NULL};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_POINTER) {
    result.value = item->data.pointer;
    result.found = NETrue;
  }
  return result;
}

NECollectionCollectionAtResult NECollectionCollectionAt(NECollection *self, NEInteger index) {
  NECollectionCollectionAtResult result = {NEFalse, NULL};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_COLLECTION) {
    result.value = item->data.collection;
    result.found = NETrue;
  }
  return result;
}

NECollectionMapNodeAtResult NECollectionMapNodeAt(NECollection *self, NEInteger index) {
  NECollectionMapNodeAtResult result = {NEFalse, NULL};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_MAPNODE) {
    result.value = item->data.mapNode;
    result.found = NETrue;
  }
  return result;
}

NECollectionMapAtResult NECollectionMapAt(NECollection *self, NEInteger index) {
  NECollectionMapAtResult result = {NEFalse, NULL};
  KeyValue *item = NECollectionAt(self, index);
  if (item && item->type == NE_MAP) {
    result.value = item->data.map;
    result.found = NETrue;
  }
  return result;
}

NEInteger NECollectionCount(NECollection *self) {
  return NEListSize(self->list);
}
void NECollectionClear(NECollection *self) {
  NEDestroyListCustom(self->list, _NECollectionNodeFreer);
  self->list = NECreateList();
}
void NECollectionSort(NECollection *self, NECollectionSorter sorter) {
  return;
}
