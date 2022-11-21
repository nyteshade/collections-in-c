#ifndef NE_COLLECTION_H
#define NE_COLLECTION_H

#include "keyvalue.h"
#include "lists.h"
#include "types.h"

typedef NEInteger (*NECollectionSorter)(KeyValue left, KeyValue right);

typedef struct CollectionItem {
  NENode node;
  KeyValue keyValue;
} CollectionItem;

typedef struct Collection {
    NEList *list;

    void (*add)(struct Collection *self, KeyValue value);
    void (*addByte)(struct Collection *self, NEByte value);
    void (*addInteger)(struct Collection *self, NEInteger value);
    void (*addDecimal)(struct Collection *self, NEDecimal value);
    void (*addString)(struct Collection *self, const NEStrPtr value);
    void (*addPointer)(struct Collection *self, NEPointer value);

    KeyValue *(*findByte)(struct Collection *self, NEByte value);
    KeyValue *(*findInteger)(struct Collection *self, NEInteger value);
    KeyValue *(*findDecimal)(struct Collection *self, NEDecimal value);
    KeyValue *(*findString)(struct Collection *self, const NEStrPtr value);
    KeyValue *(*findPointer)(struct Collection *self, NEPointer value);

    KeyValue *(*at)(struct Collection *self, NEInteger index);
    NEInteger (*count)(struct Collection *self);
    void (*clear)(struct Collection *self);
    void (*sort)(struct Collection *self, NECollectionSorter sorter);
} Collection;

Collection *NECollectionCreate(void);
void NECollectionFree(Collection *self);

void NECollectionAdd(Collection *self, KeyValue value);
void NECollectionAddByte(Collection *self, NEByte value);
void NECollectionAddInteger(Collection *self, NEInteger value);
void NECollectionAddDecimal(Collection *self, NEDecimal value);
void NECollectionAddString(Collection *self, const NEStrPtr value);
void NECollectionAddPointer(Collection *self, NEPointer value);

KeyValue *NECollectionFindByte(Collection *self, NEByte value);
KeyValue *NECollectionFindInteger(Collection *self, NEInteger value);
KeyValue *NECollectionFindDecimal(Collection *self, NEDecimal value);
KeyValue *NECollectionFindString(Collection *self, const NEStrPtr value);
KeyValue *NECollectionFindPointer(Collection *self, NEPointer value);

KeyValue *NECollectionAt(Collection *self, NEInteger index);
NEInteger NECollectionCount(Collection *self);
void NECollectionClear(Collection *self);
void NECollectionSort(Collection *self, NECollectionSorter sorter);


#endif
