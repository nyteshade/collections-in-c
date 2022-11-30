#ifndef NE_COLLECTION_H
#define NE_COLLECTION_H

#include <NECollections/NEKeyValue.h>
#include <NECollections/NEList.h>
#include <NECollections/NETypes.h>
#include <NECollections/NEMap.h>
#include <NECollections/NEString.h>

/* Struct and typedef prototypes */
struct NECollectionMapResult;

/* Function typedef definitions */
typedef NEInteger (*NECollectionSorter)(KeyValue left, KeyValue right);
typedef struct NECollectionMapResult (*NECollectionMapper)(KeyValue *value, NEULong index);
typedef void (*NECollectionIterator)(KeyValue *value, NEULong index);
typedef NEBool (*NECollectionValidator)(KeyValue *value, NEULong index);

/* Primary Struct Definition */
typedef struct NECollection {
    NEList *list;

    void (*add)(struct NECollection *self, KeyValue value);
    void (*addByte)(struct NECollection *self, NEByte value);
    void (*addInteger)(struct NECollection *self, NEInteger value);
    void (*addDecimal)(struct NECollection *self, NEDecimal value);
    void (*addString)(struct NECollection *self, const NEStrPtr value);
    void (*addNEString)(struct NECollection *self, NEString *value);
    void (*addPointer)(struct NECollection *self, NEPointer value);
    void (*addCollection)(struct NECollection *self, struct NECollection *value);
    void (*addMapNode)(struct NECollection *self, struct NEMapNode *node);
    void (*addMap)(struct NECollection *self, struct NEMap *map);

    KeyValue *(*findByte)(struct NECollection *self, NEByte value);
    KeyValue *(*findInteger)(struct NECollection *self, NEInteger value);
    KeyValue *(*findDecimal)(struct NECollection *self, NEDecimal value);
    KeyValue *(*findString)(struct NECollection *self, const NEStrPtr value, NEBool caseSensitive);
    KeyValue *(*findNEString)(struct NECollection *self, NEString *value, NEBool caseSensitive);
    KeyValue *(*findPointer)(struct NECollection *self, NEPointer value);
    KeyValue *(*findCollection)(struct NECollection *self, struct NECollection *value);
    KeyValue *(*findMapNode)(struct NECollection *self, struct NEMapNode *node);
    KeyValue *(*findMap)(struct NECollection *self, struct NEMap *map);

    KeyValue *(*at)(struct NECollection *self, NEInteger index);
    struct NECollectionByteAtResult (*byteAt)(struct NECollection *self, NEInteger index);
    struct NECollectionIntegerAtResult (*integerAt)(struct NECollection *self, NEInteger index);
    struct NECollectionDecimalAtResult (*decimalAt)(struct NECollection *self, NEInteger index);
    struct NECollectionStringAtResult (*stringAt)(struct NECollection *self, NEInteger index);
    struct NECollectionNEStringAtResult (*neStringAt)(struct NECollection *self, NEInteger index);
    struct NECollectionPointerAtResult (*pointerAt)(struct NECollection *self, NEInteger index);
    struct NECollectionCollectionAtResult (*collectionAt)(struct NECollection *self, NEInteger index);
    struct NECollectionMapNodeAtResult (*mapNodeAt)(struct NECollection *self, NEInteger index);
    struct NECollectionMapAtResult (*mapAt)(struct NECollection *self, NEInteger index);

    NEInteger (*count)(struct NECollection *self);
    void (*clear)(struct NECollection *self);
    void (*sort)(struct NECollection *self, NECollectionSorter sorter);

    struct NECollection *(*map)(struct NECollection *self, NECollectionMapper mapper);
    struct NECollection *(*filter)(struct NECollection *self, NECollectionValidator validator);
    void (*forEach)(struct NECollection *self, NECollectionIterator iterator);
} NECollection;

/* Function prototypes */
NECollection *NECollectionCreate(void);
void NECollectionFree(NECollection *self);

void NECollectionAdd(NECollection *self, KeyValue value);
void NECollectionAddByte(NECollection *self, NEByte value);
void NECollectionAddInteger(NECollection *self, NEInteger value);
void NECollectionAddDecimal(NECollection *self, NEDecimal value);
void NECollectionAddString(NECollection *self, const NEStrPtr value);
void NECollectionAddNEString(NECollection *self, NEString *value);
void NECollectionAddPointer(NECollection *self, NEPointer value);
void NECollectionAddCollection(NECollection *self, NECollection *value);
void NECollectionAddMapNode(NECollection *self, struct NEMapNode *node);
void NECollectionAddMap(NECollection *self, struct NEMap *map);

NECollection *NECollectionMap(NECollection *self, NECollectionMapper mapper);
NECollection *NECollectionFilter(NECollection *self, NECollectionValidator validator);
void NECollectionForEach(NECollection *self, NECollectionIterator iterator);

KeyValue *NECollectionFindByte(NECollection *self, NEByte value);
KeyValue *NECollectionFindInteger(NECollection *self, NEInteger value);
KeyValue *NECollectionFindDecimal(NECollection *self, NEDecimal value);
KeyValue *NECollectionFindString(NECollection *self, const NEStrPtr value, NEBool caseSensitive);
KeyValue *NECollectionFindNEString(NECollection *self, NEString *value, NEBool caseSensitive);
KeyValue *NECollectionFindPointer(NECollection *self, NEPointer value);
KeyValue *NECollectionFindCollection(NECollection *self, NECollection *value);
KeyValue *NECollectionFindMapNode(NECollection *self, struct NEMapNode *node);
KeyValue *NECollectionFindMap(NECollection *self, struct NEMap *map);

KeyValue *NECollectionAt(NECollection *self, NEInteger index);
struct NECollectionByteAtResult NECollectionByteAt(NECollection *self, NEInteger index);
struct NECollectionIntegerAtResult NECollectionIntegerAt(NECollection *self, NEInteger index);
struct NECollectionDecimalAtResult NECollectionDecimalAt(NECollection *self, NEInteger index);
struct NECollectionStringAtResult NECollectionStringAt(NECollection *self, NEInteger index);
struct NECollectionNEStringAtResult NECollectionNEStringAt(NECollection *self, NEInteger index);
struct NECollectionPointerAtResult NECollectionPointerAt(NECollection *self, NEInteger index);
struct NECollectionCollectionAtResult NECollectionCollectionAt(NECollection *self, NEInteger index);
struct NECollectionMapNodeAtResult NECollectionMapNodeAt(NECollection *self, NEInteger index);
struct NECollectionMapAtResult NECollectionMapAt(NECollection *self, NEInteger index);

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

typedef struct NECollectionNEStringAtResult {
  NEBool found;
  NEString *value;
} NECollectionNEStringAtResult;

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
  struct NEMapNode *value;
} NECollectionMapNodeAtResult;

typedef struct NECollectionMapAtResult {
  NEBool found;
  struct NEMap *value;
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

