#ifndef NE_COLLECTION_H
#define NE_COLLECTION_H

#include "keyvalue.h"
#include "lists.h"
#include "types.h"

typedef NEInteger (*NECollectionSorter)(KeyValue left, KeyValue right);

typedef struct NECollectionItem {
  NENode node;
  KeyValue keyValue;
} NECollectionItem;

typedef struct NECollection {
    NEList *list;

    void (*add)(struct NECollection *self, KeyValue value);
    void (*addByte)(struct NECollection *self, NEByte value);
    void (*addInteger)(struct NECollection *self, NEInteger value);
    void (*addDecimal)(struct NECollection *self, NEDecimal value);
    void (*addString)(struct NECollection *self, const NEStrPtr value);
    void (*addPointer)(struct NECollection *self, NEPointer value);

    KeyValue *(*findByte)(struct NECollection *self, NEByte value);
    KeyValue *(*findInteger)(struct NECollection *self, NEInteger value);
    KeyValue *(*findDecimal)(struct NECollection *self, NEDecimal value);
    KeyValue *(*findString)(struct NECollection *self, const NEStrPtr value);
    KeyValue *(*findPointer)(struct NECollection *self, NEPointer value);

    KeyValue *(*at)(struct NECollection *self, NEInteger index);
    NEInteger (*count)(struct NECollection *self);
    void (*clear)(struct NECollection *self);
    void (*sort)(struct NECollection *self, NECollectionSorter sorter);
} NECollection;

NECollection *NECollectionCreate(void);
void NECollectionFree(NECollection *self);

void NECollectionAdd(NECollection *self, KeyValue value);
void NECollectionAddByte(NECollection *self, NEByte value);
void NECollectionAddInteger(NECollection *self, NEInteger value);
void NECollectionAddDecimal(NECollection *self, NEDecimal value);
void NECollectionAddString(NECollection *self, const NEStrPtr value);
void NECollectionAddPointer(NECollection *self, NEPointer value);

KeyValue *NECollectionFindByte(NECollection *self, NEByte value);
KeyValue *NECollectionFindInteger(NECollection *self, NEInteger value);
KeyValue *NECollectionFindDecimal(NECollection *self, NEDecimal value);
KeyValue *NECollectionFindString(NECollection *self, const NEStrPtr value);
KeyValue *NECollectionFindPointer(NECollection *self, NEPointer value);

KeyValue *NECollectionAt(NECollection *self, NEInteger index);
NEInteger NECollectionCount(NECollection *self);
void NECollectionClear(NECollection *self);
void NECollectionSort(NECollection *self, NECollectionSorter sorter);


#endif
