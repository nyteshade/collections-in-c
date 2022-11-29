#ifndef NE_MAP_H
#define NE_MAP_H

#include <NECollections/NEList.h>
#include <NECollections/NECollection.h>
#include <NECollections/NEKeyValue.h>

/* Struct and typedef prototypes */
typedef struct NEMap NEMap;
typedef struct NEMapNode NEMapNode;
typedef struct NEMapNodeSet NEMapNodeSet;

/* Primary Struct Definition */
typedef struct NEMap {
  NEMapNode **data;
  NEULong *entryCounts;
  NEULong size;

  NEByte (*getByteByte)(NEMap *map, NEByte key);
  NEInteger (*getByteInteger)(NEMap *map, NEByte key);
  NEDecimal (*getByteDecimal)(NEMap *map, NEByte key);
  NEStrPtr (*getByteString)(NEMap *map, NEByte key);
  NEPointer (*getBytePointer)(NEMap *map, NEByte key);
  NECollection *(*getByteCollection)(NEMap *map, NEByte key);
  NEMap *(*getByteMap)(NEMap *map, NEByte key);

  NEByte (*getIntegerByte)(NEMap *map, NEInteger key);
  NEInteger (*getIntegerInteger)(NEMap *map, NEInteger key);
  NEDecimal (*getIntegerDecimal)(NEMap *map, NEInteger key);
  NEStrPtr (*getIntegerString)(NEMap *map, NEInteger key);
  NEPointer (*getIntegerPointer)(NEMap *map, NEInteger key);
  NECollection *(*getIntegerCollection)(NEMap *map, NEInteger key);
  NEMap *(*getIntegerMap)(NEMap *map, NEInteger key);

  NEByte (*getDecimalByte)(NEMap *map, NEDecimal key);
  NEInteger (*getDecimalInteger)(NEMap *map, NEDecimal key);
  NEDecimal (*getDecimalDecimal)(NEMap *map, NEDecimal key);
  NEStrPtr (*getDecimalString)(NEMap *map, NEDecimal key);
  NEPointer (*getDecimalPointer)(NEMap *map, NEDecimal key);
  NECollection *(*getDecimalCollection)(NEMap *map, NEDecimal key);
  NEMap *(*getDecimalMap)(NEMap *map, NEDecimal key);

  NEByte (*getStringByte)(NEMap *map, NEStrPtr key);
  NEInteger (*getStringInteger)(NEMap *map, NEStrPtr key);
  NEDecimal (*getStringDecimal)(NEMap *map, NEStrPtr key);
  NEStrPtr (*getStringString)(NEMap *map, NEStrPtr key);
  NEPointer (*getStringPointer)(NEMap *map, NEStrPtr key);
  NECollection *(*getStringCollection)(NEMap *map, NEStrPtr key);
  NEMap *(*getStringMap)(NEMap *map, NEStrPtr key);

  NEByte (*getPointerByte)(NEMap *map, NEPointer key);
  NEInteger (*getPointerInteger)(NEMap *map, NEPointer key);
  NEDecimal (*getPointerDecimal)(NEMap *map, NEPointer key);
  NEStrPtr (*getPointerString)(NEMap *map, NEPointer key);
  NEPointer (*getPointerPointer)(NEMap *map, NEPointer key);
  NECollection *(*getPointerCollection)(NEMap *map, NEPointer key);
  NEMap *(*getPointerMap)(NEMap *map, NEPointer key);

  NEByte (*getCollectionByte)(NEMap *map, NECollection *key);
  NEInteger (*getCollectionInteger)(NEMap *map, NECollection *key);
  NEDecimal (*getCollectionDecimal)(NEMap *map, NECollection *key);
  NEStrPtr (*getCollectionString)(NEMap *map, NECollection *key);
  NEPointer (*getCollectionPointer)(NEMap *map, NECollection *key);
  NECollection *(*getCollectionCollection)(NEMap *map, NECollection *key);
  NEMap *(*getCollectionMap)(NEMap *map, NECollection *key);

  NEByte (*getMapByte)(NEMap *map, NEMap *key);
  NEInteger (*getMapInteger)(NEMap *map, NEMap *key);
  NEDecimal (*getMapDecimal)(NEMap *map, NEMap *key);
  NEStrPtr (*getMapString)(NEMap *map, NEMap *key);
  NEPointer (*getMapPointer)(NEMap *map, NEMap *key);
  NECollection *(*getMapCollection)(NEMap *map, NEMap *key);
  NEMap *(*getMapMap)(NEMap *map, NEMap *key);

  void (*setByteByte)(struct NEMap *map, NEByte key, NEByte value);
  void (*setByteInteger)(struct NEMap *map, NEByte key, NEInteger value);
  void (*setByteDecimal)(struct NEMap *map, NEByte key, NEDecimal value);
  void (*setByteString)(struct NEMap *map, NEByte key, NEStrPtr value);
  void (*setBytePointer)(struct NEMap *map, NEByte key, NEPointer value);
  void (*setByteCollection)(struct NEMap *map, NEByte key, NECollection *value);
  void (*setByteMap)(struct NEMap *map, NEByte key, NEMap *value);

  void (*setIntegerByte)(struct NEMap *map, NEInteger key, NEByte value);
  void (*setIntegerInteger)(struct NEMap *map, NEInteger key, NEInteger value);
  void (*setIntegerDecimal)(struct NEMap *map, NEInteger key, NEDecimal value);
  void (*setIntegerString)(struct NEMap *map, NEInteger key, NEStrPtr value);
  void (*setIntegerPointer)(struct NEMap *map, NEInteger key, NEPointer value);
  void (*setIntegerCollection)(struct NEMap *map, NEInteger key, NECollection *value);
  void (*setIntegerMap)(struct NEMap *map, NEInteger key, NEMap *value);

  void (*setDecimalByte)(struct NEMap *map, NEDecimal key, NEByte value);
  void (*setDecimalInteger)(struct NEMap *map, NEDecimal key, NEInteger value);
  void (*setDecimalDecimal)(struct NEMap *map, NEDecimal key, NEDecimal value);
  void (*setDecimalString)(struct NEMap *map, NEDecimal key, NEStrPtr value);
  void (*setDecimalPointer)(struct NEMap *map, NEDecimal key, NEPointer value);
  void (*setDecimalCollection)(struct NEMap *map, NEDecimal key, NECollection *value);
  void (*setDecimalMap)(struct NEMap *map, NEDecimal key, NEMap *value);

  void (*setStringByte)(struct NEMap *map, NEStrPtr key, NEByte value);
  void (*setStringInteger)(struct NEMap *map, NEStrPtr key, NEInteger value);
  void (*setStringDecimal)(struct NEMap *map, NEStrPtr key, NEDecimal value);
  void (*setStringString)(struct NEMap *map, NEStrPtr key, NEStrPtr value);
  void (*setStringPointer)(struct NEMap *map, NEStrPtr key, NEPointer value);
  void (*setStringCollection)(struct NEMap *map, NEStrPtr key, NECollection *value);
  void (*setStringMap)(struct NEMap *map, NEStrPtr key, NEMap *value);

  void (*setPointerByte)(struct NEMap *map, NEPointer key, NEByte value);
  void (*setPointerInteger)(struct NEMap *map, NEPointer key, NEInteger value);
  void (*setPointerDecimal)(struct NEMap *map, NEPointer key, NEDecimal value);
  void (*setPointerString)(struct NEMap *map, NEPointer key, NEStrPtr value);
  void (*setPointerPointer)(struct NEMap *map, NEPointer key, NEPointer value);
  void (*setPointerCollection)(struct NEMap *map, NEPointer key, NECollection *value);
  void (*setPointerMap)(struct NEMap *map, NEPointer key, NEMap *value);

  void (*setCollectionByte)(struct NEMap *map, NECollection *key, NEByte value);
  void (*setCollectionInteger)(struct NEMap *map, NECollection *key, NEInteger value);
  void (*setCollectionDecimal)(struct NEMap *map, NECollection *key, NEDecimal value);
  void (*setCollectionString)(struct NEMap *map, NECollection *key, NEStrPtr value);
  void (*setCollectionPointer)(struct NEMap *map, NECollection *key, NEPointer value);
  void (*setCollectionCollection)(struct NEMap *map, NECollection *key, NECollection *value);
  void (*setCollectionMap)(struct NEMap *map, NECollection *key, NEMap *value);

  void (*setMapByte)(struct NEMap *map, NEMap *key, NEByte value);
  void (*setMapInteger)(struct NEMap *map, NEMap *key, NEInteger value);
  void (*setMapDecimal)(struct NEMap *map, NEMap *key, NEDecimal value);
  void (*setMapString)(struct NEMap *map, NEMap *key, NEStrPtr value);
  void (*setMapPointer)(struct NEMap *map, NEMap *key, NEPointer value);
  void (*setMapCollection)(struct NEMap *map, NEMap *key, NECollection *value);
  void (*setMapMap)(struct NEMap *map, NEMap *key, NEMap *value);

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

NEByte NEMapGetByteByte(NEMap *map, NEByte key);
NEInteger NEMapGetByteInteger(NEMap *map, NEByte key);
NEDecimal NEMapGetByteDecimal(NEMap *map, NEByte key);
NEStrPtr NEMapGetByteString(NEMap *map, NEByte key);
NEPointer NEMapGetBytePointer(NEMap *map, NEByte key);
NECollection *NEMapGetByteCollection(NEMap *map, NEByte key);
NEMap *NEMapGetByteMap(NEMap *map, NEByte key);

NEByte NEMapGetIntegerByte(NEMap *map, NEInteger key);
NEInteger NEMapGetIntegerInteger(NEMap *map, NEInteger key);
NEDecimal NEMapGetIntegerDecimal(NEMap *map, NEInteger key);
NEStrPtr NEMapGetIntegerString(NEMap *map, NEInteger key);
NEPointer NEMapGetIntegerPointer(NEMap *map, NEInteger key);
NECollection *NEMapGetIntegerCollection(NEMap *map, NEInteger key);
NEMap *NEMapGetIntegerMap(NEMap *map, NEInteger key);

NEByte NEMapGetDecimalByte(NEMap *map, NEDecimal key);
NEInteger NEMapGetDecimalInteger(NEMap *map, NEDecimal key);
NEDecimal NEMapGetDecimalDecimal(NEMap *map, NEDecimal key);
NEStrPtr NEMapGetDecimalString(NEMap *map, NEDecimal key);
NEPointer NEMapGetDecimalPointer(NEMap *map, NEDecimal key);
NECollection *NEMapGetDecimalCollection(NEMap *map, NEDecimal key);
NEMap *NEMapGetDecimalMap(NEMap *map, NEDecimal key);

NEByte NEMapGetStringByte(NEMap *map, NEStrPtr key);
NEInteger NEMapGetStringInteger(NEMap *map, NEStrPtr key);
NEDecimal NEMapGetStringDecimal(NEMap *map, NEStrPtr key);
NEStrPtr NEMapGetStringString(NEMap *map, NEStrPtr key);
NEPointer NEMapGetStringPointer(NEMap *map, NEStrPtr key);
NECollection *NEMapGetStringCollection(NEMap *map, NEStrPtr key);
NEMap *NEMapGetStringMap(NEMap *map, NEStrPtr key);

NEByte NEMapGetPointerByte(NEMap *map, NEPointer key);
NEInteger NEMapGetPointerInteger(NEMap *map, NEPointer key);
NEDecimal NEMapGetPointerDecimal(NEMap *map, NEPointer key);
NEStrPtr NEMapGetPointerString(NEMap *map, NEPointer key);
NEPointer NEMapGetPointerPointer(NEMap *map, NEPointer key);
NECollection *NEMapGetPointerCollection(NEMap *map, NEPointer key);
NEMap *NEMapGetPointerMap(NEMap *map, NEPointer key);

NEByte NEMapGetCollectionByte(NEMap *map, NECollection *key);
NEInteger NEMapGetCollectionInteger(NEMap *map, NECollection *key);
NEDecimal NEMapGetCollectionDecimal(NEMap *map, NECollection *key);
NEStrPtr NEMapGetCollectionString(NEMap *map, NECollection *key);
NEPointer NEMapGetCollectionPointer(NEMap *map, NECollection *key);
NECollection *NEMapGetCollectionCollection(NEMap *map, NECollection *key);
NEMap *NEMapGetCollectionMap(NEMap *map, NECollection *key);

NEByte NEMapGetMapByte(NEMap *map, NEMap *key);
NEInteger NEMapGetMapInteger(NEMap *map, NEMap *key);
NEDecimal NEMapGetMapDecimal(NEMap *map, NEMap *key);
NEStrPtr NEMapGetMapString(NEMap *map, NEMap *key);
NEPointer NEMapGetMapPointer(NEMap *map, NEMap *key);
NECollection *NEMapGetMapCollection(NEMap *map, NEMap *key);
NEMap *NEMapGetMapMap(NEMap *map, NEMap *key);

void NEMapSetByteByte(NEMap *map, NEByte key, NEByte value);
void NEMapSetByteInteger(NEMap *map, NEByte key, NEInteger value);
void NEMapSetByteDecimal(NEMap *map, NEByte key, NEDecimal value);
void NEMapSetByteString(NEMap *map, NEByte key, NEStrPtr value);
void NEMapSetBytePointer(NEMap *map, NEByte key, NEPointer value);
void NEMapSetByteCollection(NEMap *map, NEByte key, NECollection *value);
void NEMapSetByteMap(NEMap *map, NEByte key, NEMap *value);

void NEMapSetIntegerByte(NEMap *map, NEInteger key, NEByte value);
void NEMapSetIntegerInteger(NEMap *map, NEInteger key, NEInteger value);
void NEMapSetIntegerDecimal(NEMap *map, NEInteger key, NEDecimal value);
void NEMapSetIntegerString(NEMap *map, NEInteger key, NEStrPtr value);
void NEMapSetIntegerPointer(NEMap *map, NEInteger key, NEPointer value);
void NEMapSetIntegerCollection(NEMap *map, NEInteger key, NECollection *value);
void NEMapSetIntegerMap(NEMap *map, NEInteger key, NEMap *value);

void NEMapSetDecimalByte(NEMap *map, NEDecimal key, NEByte value);
void NEMapSetDecimalInteger(NEMap *map, NEDecimal key, NEInteger value);
void NEMapSetDecimalDecimal(NEMap *map, NEDecimal key, NEDecimal value);
void NEMapSetDecimalString(NEMap *map, NEDecimal key, NEStrPtr value);
void NEMapSetDecimalPointer(NEMap *map, NEDecimal key, NEPointer value);
void NEMapSetDecimalCollection(NEMap *map, NEDecimal key, NECollection *value);
void NEMapSetDecimalMap(NEMap *map, NEDecimal key, NEMap *value);

void NEMapSetStringByte(NEMap *map, NEStrPtr key, NEByte value);
void NEMapSetStringInteger(NEMap *map, NEStrPtr key, NEInteger value);
void NEMapSetStringDecimal(NEMap *map, NEStrPtr key, NEDecimal value);
void NEMapSetStringString(NEMap *map, NEStrPtr key, NEStrPtr value);
void NEMapSetStringPointer(NEMap *map, NEStrPtr key, NEPointer value);
void NEMapSetStringCollection(NEMap *map, NEStrPtr key, NECollection *value);
void NEMapSetStringMap(NEMap *map, NEStrPtr key, NEMap *value);

void NEMapSetPointerByte(NEMap *map, NEPointer key, NEByte value);
void NEMapSetPointerInteger(NEMap *map, NEPointer key, NEInteger value);
void NEMapSetPointerDecimal(NEMap *map, NEPointer key, NEDecimal value);
void NEMapSetPointerString(NEMap *map, NEPointer key, NEStrPtr value);
void NEMapSetPointerPointer(NEMap *map, NEPointer key, NEPointer value);
void NEMapSetPointerCollection(NEMap *map, NEPointer key, NECollection *value);
void NEMapSetPointerMap(NEMap *map, NEPointer key, NEMap *value);

void NEMapSetCollectionByte(NEMap *map, NECollection *key, NEByte value);
void NEMapSetCollectionInteger(NEMap *map, NECollection *key, NEInteger value);
void NEMapSetCollectionDecimal(NEMap *map, NECollection *key, NEDecimal value);
void NEMapSetCollectionString(NEMap *map, NECollection *key, NEStrPtr value);
void NEMapSetCollectionPointer(NEMap *map, NECollection *key, NEPointer value);
void NEMapSetCollectionCollection(NEMap *map, NECollection *key, NECollection *value);
void NEMapSetCollectionMap(NEMap *map, NECollection *key, NEMap *value);

void NEMapSetMapByte(NEMap *map, NEMap *key, NEByte value);
void NEMapSetMapInteger(NEMap *map, NEMap *key, NEInteger value);
void NEMapSetMapDecimal(NEMap *map, NEMap *key, NEDecimal value);
void NEMapSetMapString(NEMap *map, NEMap *key, NEStrPtr value);
void NEMapSetMapPointer(NEMap *map, NEMap *key, NEPointer value);
void NEMapSetMapCollection(NEMap *map, NEMap *key, NECollection *value);
void NEMapSetMapMap(NEMap *map, NEMap *key, NEMap *value);

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
