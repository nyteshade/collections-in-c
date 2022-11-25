#ifndef NE_COLLECTION_H
#define NE_COLLECTION_H

#include "KeyValue.h"
#include "Lists.h"
#include "Types.h"
#include "Map.h"

/* Struct and typedef prototypes */
typedef struct NECollection NECollection;
typedef struct NEMapNode NEMapNode;

typedef struct NECollectionByteAtResult NECollectionByteAtResult;
typedef struct NECollectionIntegerAtResult NECollectionIntegerAtResult;
typedef struct NECollectionDecimalAtResult NECollectionDecimalAtResult;
typedef struct NECollectionStringAtResult NECollectionStringAtResult;
typedef struct NECollectionPointerAtResult NECollectionPointerAtResult;
typedef struct NECollectionCollectionAtResult NECollectionCollectionAtResult;
typedef struct NECollectionMapNodeAtResult NECollectionMapNodeAtResult;
typedef struct NECollectionMapAtResult NECollectionMapAtResult;

typedef struct NECollectionItem NECollectionItem;
typedef struct NECollectionMapResult NECollectionMapResult;

/* Function typedef definitions */
typedef NEInteger (*NECollectionSorter)(KeyValue left, KeyValue right);
typedef NECollectionMapResult (*NECollectionMapper)(KeyValue *value, NEULong index);
typedef void (*NECollectionIterator)(KeyValue *value, NEULong index);
typedef NEBool (*NECollectionValidator)(KeyValue *value, NEULong index);

/* Primary Struct Definition */
struct NECollection {
    NEList *list;

    void (*add)(struct NECollection *self, KeyValue value);
    void (*addByte)(struct NECollection *self, NEByte value);
    void (*addInteger)(struct NECollection *self, NEInteger value);
    void (*addDecimal)(struct NECollection *self, NEDecimal value);
    void (*addString)(struct NECollection *self, const NEStrPtr value);
    void (*addPointer)(struct NECollection *self, NEPointer value);
    void (*addCollection)(struct NECollection *self, NECollection *value);
    void (*addMapNode)(struct NECollection *self, NEMapNode *node);
    void (*addMap)(struct NECollection *self, NEMap *map);

    KeyValue *(*findByte)(struct NECollection *self, NEByte value);
    KeyValue *(*findInteger)(struct NECollection *self, NEInteger value);
    KeyValue *(*findDecimal)(struct NECollection *self, NEDecimal value);
    KeyValue *(*findString)(struct NECollection *self, const NEStrPtr value, NEBool caseSensitive);
    KeyValue *(*findPointer)(struct NECollection *self, NEPointer value);
    KeyValue *(*findCollection)(struct NECollection *self, NECollection *value);
    KeyValue *(*findMapNode)(struct NECollection *self, NEMapNode *node);
    KeyValue *(*findMap)(struct NECollection *self, NEMap *map);

    KeyValue *(*at)(struct NECollection *self, NEInteger index);
    NECollectionByteAtResult (*byteAt)(struct NECollection *self, NEInteger index);
    NECollectionIntegerAtResult (*integerAt)(struct NECollection *self, NEInteger index);
    NECollectionDecimalAtResult (*decimalAt)(struct NECollection *self, NEInteger index);
    NECollectionStringAtResult (*stringAt)(struct NECollection *self, NEInteger index);
    NECollectionPointerAtResult (*pointerAt)(struct NECollection *self, NEInteger index);
    NECollectionCollectionAtResult (*collectionAt)(struct NECollection *self, NEInteger index);
    NECollectionMapNodeAtResult (*mapNodeAt)(struct NECollection *self, NEInteger index);
    NECollectionMapAtResult (*mapAt)(struct NECollection *self, NEInteger index);

    NEInteger (*count)(struct NECollection *self);
    void (*clear)(struct NECollection *self);
    void (*sort)(struct NECollection *self, NECollectionSorter sorter);

    NECollection *(*map)(struct NECollection *self, NECollectionMapper mapper);
    NECollection *(*filter)(struct NECollection *self, NECollectionValidator validator);
    void (*forEach)(struct NECollection *self, NECollectionIterator iterator);
};

/* Function prototypes */
NECollection *NECollectionCreate(void);
void NECollectionFree(NECollection *self);

void NECollectionAdd(NECollection *self, KeyValue value);
void NECollectionAddByte(NECollection *self, NEByte value);
void NECollectionAddInteger(NECollection *self, NEInteger value);
void NECollectionAddDecimal(NECollection *self, NEDecimal value);
void NECollectionAddString(NECollection *self, const NEStrPtr value);
void NECollectionAddPointer(NECollection *self, NEPointer value);
void NECollectionAddCollection(NECollection *self, NECollection *value);
void NECollectionAddMapNode(NECollection *self, NEMapNode *node);
void NECollectionAddMap(NECollection *self, NEMap *map);

NECollection *NECollectionMap(NECollection *self, NECollectionMapper mapper);
NECollection *NECollectionFilter(NECollection *self, NECollectionValidator validator);
void NECollectionForEach(NECollection *self, NECollectionIterator iterator);

KeyValue *NECollectionFindByte(NECollection *self, NEByte value);
KeyValue *NECollectionFindInteger(NECollection *self, NEInteger value);
KeyValue *NECollectionFindDecimal(NECollection *self, NEDecimal value);
KeyValue *NECollectionFindString(NECollection *self, const NEStrPtr value, NEBool caseSensitive);
KeyValue *NECollectionFindPointer(NECollection *self, NEPointer value);
KeyValue *NECollectionFindCollection(NECollection *self, NECollection *value);
KeyValue *NECollectionFindMapNode(NECollection *self, NEMapNode *node);
KeyValue *NECollectionFindMap(NECollection *self, NEMap *map);

KeyValue *NECollectionAt(NECollection *self, NEInteger index);
NECollectionByteAtResult NECollectionByteAt(NECollection *self, NEInteger index);
NECollectionIntegerAtResult NECollectionIntegerAt(NECollection *self, NEInteger index);
NECollectionDecimalAtResult NECollectionDecimalAt(NECollection *self, NEInteger index);
NECollectionStringAtResult NECollectionStringAt(NECollection *self, NEInteger index);
NECollectionPointerAtResult NECollectionPointerAt(NECollection *self, NEInteger index);
NECollectionCollectionAtResult NECollectionCollectionAt(NECollection *self, NEInteger index);
NECollectionMapNodeAtResult NECollectionMapNodeAt(NECollection *self, NEInteger index);
NECollectionMapAtResult NECollectionMapAt(NECollection *self, NEInteger index);

NEInteger NECollectionCount(NECollection *self);
void NECollectionClear(NECollection *self);
void NECollectionSort(NECollection *self, NECollectionSorter sorter);

/* Struct and typedef definitions */
typedef struct NECollectionByteAtResult {
  NEBool found;
  NEByte value;
} NECollectionByteAtResult;

typedef struct NECollectionIntegerAtResult {
  NEBool found;
  NEInteger value;
} NECollectionIntegerAtResult;

typedef struct NECollectionDecimalAtResult {
  NEBool found;
  NEDecimal value;
} NECollectionDecimalAtResult;

typedef struct NECollectionStringAtResult {
  NEBool found;
  NEStrPtr value;
} NECollectionStringAtResult;

typedef struct NECollectionPointerAtResult {
  NEBool found;
  NEPointer value;
} NECollectionPointerAtResult;

typedef struct NECollectionCollectionAtResult {
  NEBool found;
  NECollection *value;
} NECollectionCollectionAtResult;

typedef struct NECollectionMapNodeAtResult {
  NEBool found;
  NEMapNode *value;
} NECollectionMapNodeAtResult;

typedef struct NECollectionMapAtResult {
  NEBool found;
  NEMap *value;
} NECollectionMapAtResult;

typedef struct NECollectionMapResult {
  KeyValue value;
  NEDataMapDecision decision;
} NECollectionMapResult;

typedef struct NECollectionItem {
  NENode node;
  KeyValue keyValue;
} NECollectionItem;

#endif

