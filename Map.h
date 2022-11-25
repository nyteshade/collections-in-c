#ifndef NE_MAP_H
#define NE_MAP_H

#include "Lists.h"
#include "Collection.h"
#include "KeyValue.h"

/* Struct and typedef prototypes */
typedef struct NEMap NEMap;
typedef struct NEMapNode NEMapNode;
typedef struct NEMapNodeSet NEMapNodeSet;

/* Primary Struct Definition */
typedef struct NEMap {
  NEMapNode **data;
  NEULong *entryCounts;
  NEULong size;

  void (*setByteByte)(struct NEMap *map, NEByte key, NEByte value);
  void (*setByteInteger)(struct NEMap *map, NEByte key, NEInteger value);
  void (*setByteDecimal)(struct NEMap *map, NEByte key, NEDecimal value);
  void (*setByteString)(struct NEMap *map, NEByte key, NEStrPtr value);
  void (*setBytePointer)(struct NEMap *map, NEByte key, NEPointer value);
  void (*setByteCollection)(struct NEMap *map, NEByte key, NECollection *value);

  void (*setIntegerByte)(struct NEMap *map, NEInteger key, NEByte value);
  void (*setIntegerInteger)(struct NEMap *map, NEInteger key, NEInteger value);
  void (*setIntegerDecimal)(struct NEMap *map, NEInteger key, NEDecimal value);
  void (*setIntegerString)(struct NEMap *map, NEInteger key, NEStrPtr value);
  void (*setIntegerPointer)(struct NEMap *map, NEInteger key, NEPointer value);
  void (*setIntegerCollection)(struct NEMap *map, NEInteger key, NECollection *value);

  void (*setDecimalByte)(struct NEMap *map, NEDecimal key, NEByte value);
  void (*setDecimalInteger)(struct NEMap *map, NEDecimal key, NEInteger value);
  void (*setDecimalDecimal)(struct NEMap *map, NEDecimal key, NEDecimal value);
  void (*setDecimalString)(struct NEMap *map, NEDecimal key, NEStrPtr value);
  void (*setDecimalPointer)(struct NEMap *map, NEDecimal key, NEPointer value);
  void (*setDecimalCollection)(struct NEMap *map, NEDecimal key, NECollection *value);

  void (*setStringByte)(struct NEMap *map, NEStrPtr key, NEByte value);
  void (*setStringInteger)(struct NEMap *map, NEStrPtr key, NEInteger value);
  void (*setStringDecimal)(struct NEMap *map, NEStrPtr key, NEDecimal value);
  void (*setStringString)(struct NEMap *map, NEStrPtr key, NEStrPtr value);
  void (*setStringPointer)(struct NEMap *map, NEStrPtr key, NEPointer value);
  void (*setStringCollection)(struct NEMap *map, NEStrPtr key, NECollection *value);

  void (*setPointerByte)(struct NEMap *map, NEPointer key, NEByte value);
  void (*setPointerInteger)(struct NEMap *map, NEPointer key, NEInteger value);
  void (*setPointerDecimal)(struct NEMap *map, NEPointer key, NEDecimal value);
  void (*setPointerString)(struct NEMap *map, NEPointer key, NEStrPtr value);
  void (*setPointerPointer)(struct NEMap *map, NEPointer key, NEPointer value);
  void (*setPointerCollection)(struct NEMap *map, NEPointer key, NECollection *value);

  void (*setCollectionByte)(struct NEMap *map, NECollection *key, NEByte value);
  void (*setCollectionInteger)(struct NEMap *map, NECollection *key, NEInteger value);
  void (*setCollectionDecimal)(struct NEMap *map, NECollection *key, NEDecimal value);
  void (*setCollectionString)(struct NEMap *map, NECollection *key, NEStrPtr value);
  void (*setCollectionPointer)(struct NEMap *map, NECollection *key, NEPointer value);
  void (*setCollectionCollection)(struct NEMap *map, NECollection *key, NECollection *value);

  NEULong (*countEntries)(struct NEMap *map);
  void (*freeMap)(struct NEMap *map);
} NEMap;

/* Function prototypes */
NEULong ne_hash(NEUStrPtr str);
NEULong ne_hash_keyvalue(KeyValue key);
NEULong NECountMapEntries(NEMap *map);

void NESPrintMapNode(char *buffer, const NEStrPtr title, NEMapNode *node);
void NEPrintMapNode(const NEStrPtr title, NEMapNode *node);
void NESPrintMap(char *buffer, NEMap *map);
void NEPrintMap(NEMap *map);

NEMapNode *NECreateMapNode(KeyValue key, KeyValue value, NEPointer userDefined);
NEMapNode *NEDuplicateMapNode(NEMapNode *node);
void NECopyMapNodeData(NEMapNode *dest, NEMapNode *src);
NECollection *NEGatherMapNodes(NEMap *map);
NEMap *NECreateMap(NEULong hashLanes);

void NEMapSetByteByte(NEMap *map, NEByte key, NEByte value);
void NEMapSetByteInteger(NEMap *map, NEByte key, NEInteger value);
void NEMapSetByteDecimal(NEMap *map, NEByte key, NEDecimal value);
void NEMapSetByteString(NEMap *map, NEByte key, NEStrPtr value);
void NEMapSetBytePointer(NEMap *map, NEByte key, NEPointer value);
void NEMapSetByteCollection(NEMap *map, NEByte key, NECollection *value);

void NEMapSetIntegerByte(NEMap *map, NEInteger key, NEByte value);
void NEMapSetIntegerInteger(NEMap *map, NEInteger key, NEInteger value);
void NEMapSetIntegerDecimal(NEMap *map, NEInteger key, NEDecimal value);
void NEMapSetIntegerString(NEMap *map, NEInteger key, NEStrPtr value);
void NEMapSetIntegerPointer(NEMap *map, NEInteger key, NEPointer value);
void NEMapSetIntegerCollection(NEMap *map, NEInteger key, NECollection *value);

void NEMapSetDecimalByte(NEMap *map, NEDecimal key, NEByte value);
void NEMapSetDecimalInteger(NEMap *map, NEDecimal key, NEInteger value);
void NEMapSetDecimalDecimal(NEMap *map, NEDecimal key, NEDecimal value);
void NEMapSetDecimalString(NEMap *map, NEDecimal key, NEStrPtr value);
void NEMapSetDecimalPointer(NEMap *map, NEDecimal key, NEPointer value);
void NEMapSetDecimalCollection(NEMap *map, NEDecimal key, NECollection *value);

void NEMapSetStringByte(NEMap *map, NEStrPtr key, NEByte value);
void NEMapSetStringInteger(NEMap *map, NEStrPtr key, NEInteger value);
void NEMapSetStringDecimal(NEMap *map, NEStrPtr key, NEDecimal value);
void NEMapSetStringString(NEMap *map, NEStrPtr key, NEStrPtr value);
void NEMapSetStringPointer(NEMap *map, NEStrPtr key, NEPointer value);
void NEMapSetStringCollection(NEMap *map, NEStrPtr key, NECollection *value);

void NEMapSetPointerByte(NEMap *map, NEPointer key, NEByte value);
void NEMapSetPointerInteger(NEMap *map, NEPointer key, NEInteger value);
void NEMapSetPointerDecimal(NEMap *map, NEPointer key, NEDecimal value);
void NEMapSetPointerString(NEMap *map, NEPointer key, NEStrPtr value);
void NEMapSetPointerPointer(NEMap *map, NEPointer key, NEPointer value);
void NEMapSetPointerCollection(NEMap *map, NEPointer key, NECollection *value);

void NEMapSetCollectionByte(NEMap *map, NECollection *key, NEByte value);
void NEMapSetCollectionInteger(NEMap *map, NECollection *key, NEInteger value);
void NEMapSetCollectionDecimal(NEMap *map, NECollection *key, NEDecimal value);
void NEMapSetCollectionString(NEMap *map, NECollection *key, NEStrPtr value);
void NEMapSetCollectionPointer(NEMap *map, NECollection *key, NEPointer value);
void NEMapSetCollectionCollection(NEMap *map, NECollection *key, NECollection *value);

void NEMapFree(NEMap *map);

/* Struct and typedef definitions */
typedef struct NEMapNode {
  NENode node;
  NEULong hash;
  KeyValue key;
  KeyValue value;
  NEPointer userDefined;
} NEMapNode;

#endif
