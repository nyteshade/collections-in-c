#ifndef NE_MAP_H
#define NE_MAP_H

#include "lists.h"
#include "collection.h"
#include "keyvalue.h"

/* Struct and typedef prototypes */
typedef struct Map Map;
typedef struct MapNode MapNode;
typedef struct HashDataRowNode HashDataRowNode;
typedef struct MapNodeSet MapNodeSet;

/* Primary Struct Definition */
typedef struct Map {
  HashDataRowNode **data;
  NEULong *entryCounts;
  NEULong size;

  void (*setByteByte)(struct Map *map, NEByte key, NEByte value);
  void (*setByteInteger)(struct Map *map, NEByte key, NEInteger value);
  void (*setByteDecimal)(struct Map *map, NEByte key, NEDecimal value);
  void (*setByteString)(struct Map *map, NEByte key, NEStrPtr value);
  void (*setBytePointer)(struct Map *map, NEByte key, NEPointer value);
  void (*setByteCollection)(struct Map *map, NEByte key, NECollection *value);

  void (*setIntegerByte)(struct Map *map, NEInteger key, NEByte value);
  void (*setIntegerInteger)(struct Map *map, NEInteger key, NEInteger value);
  void (*setIntegerDecimal)(struct Map *map, NEInteger key, NEDecimal value);
  void (*setIntegerString)(struct Map *map, NEInteger key, NEStrPtr value);
  void (*setIntegerPointer)(struct Map *map, NEInteger key, NEPointer value);
  void (*setIntegerCollection)(struct Map *map, NEInteger key, NECollection *value);

  void (*setDecimalByte)(struct Map *map, NEDecimal key, NEByte value);
  void (*setDecimalInteger)(struct Map *map, NEDecimal key, NEInteger value);
  void (*setDecimalDecimal)(struct Map *map, NEDecimal key, NEDecimal value);
  void (*setDecimalString)(struct Map *map, NEDecimal key, NEStrPtr value);
  void (*setDecimalPointer)(struct Map *map, NEDecimal key, NEPointer value);
  void (*setDecimalCollection)(struct Map *map, NEDecimal key, NECollection *value);

  void (*setStringByte)(struct Map *map, NEStrPtr key, NEByte value);
  void (*setStringInteger)(struct Map *map, NEStrPtr key, NEInteger value);
  void (*setStringDecimal)(struct Map *map, NEStrPtr key, NEDecimal value);
  void (*setStringString)(struct Map *map, NEStrPtr key, NEStrPtr value);
  void (*setStringPointer)(struct Map *map, NEStrPtr key, NEPointer value);
  void (*setStringCollection)(struct Map *map, NEStrPtr key, NECollection *value);

  void (*setPointerByte)(struct Map *map, NEPointer key, NEByte value);
  void (*setPointerInteger)(struct Map *map, NEPointer key, NEInteger value);
  void (*setPointerDecimal)(struct Map *map, NEPointer key, NEDecimal value);
  void (*setPointerString)(struct Map *map, NEPointer key, NEStrPtr value);
  void (*setPointerPointer)(struct Map *map, NEPointer key, NEPointer value);
  void (*setPointerCollection)(struct Map *map, NEPointer key, NECollection *value);

  void (*setCollectionByte)(struct Map *map, NECollection *key, NEByte value);
  void (*setCollectionInteger)(struct Map *map, NECollection *key, NEInteger value);
  void (*setCollectionDecimal)(struct Map *map, NECollection *key, NEDecimal value);
  void (*setCollectionString)(struct Map *map, NECollection *key, NEStrPtr value);
  void (*setCollectionPointer)(struct Map *map, NECollection *key, NEPointer value);
  void (*setCollectionCollection)(struct Map *map, NECollection *key, NECollection *value);

  NEULong (*countEntries)(struct Map *map);
  void (*freeMap)(struct Map *map);
} Map;

/* Function prototypes */
NEULong ne_hash(NEUStrPtr str);
NEULong ne_hash_keyvalue(KeyValue key);
NEULong CountMapEntries(Map *map);

void PrintMapNode(const NEStrPtr title, MapNode node);
void PrintMap(Map *map);

MapNode CreateMapNode(KeyValue key, KeyValue value, NEPointer userDefined);
NECollection *GatherMapNodes(Map *map);
Map CreateMap(NEULong hashLanes);

/*
NEByte MapGetByteByte(Map *map, NEByte key);
NEInteger MapGetByteInteger(Map *map, NEByte key);
NEDecimal MapGetByteDecimal(Map *map, NEByte key);
NEStrPtr MapGetByteString(Map *map, NEByte key);
NEPointer MapGetBytePointer(Map *map, NEByte key);
NECollection *MapGetByteCollection(Map *map, NEByte key);

NEByte MapGetIntegerByte(Map *map, NEInteger key);
NEInteger MapGetIntegerInteger(Map *map, NEInteger key);
NEDecimal MapGetIntegerDecimal(Map *map, NEInteger key);
NEStrPtr MapGetIntegerString(Map *map, NEInteger key);
NEPointer MapGetIntegerPointer(Map *map, NEInteger key);
NECollection *MapGetIntegerCollection(Map *map, NEInteger key);

NEByte MapGetDecimalByte(Map *map, NEDecimal key);
NEInteger MapGetDecimalInteger(Map *map, NEDecimal key);
NEDecimal MapGetDecimalDecimal(Map *map, NEDecimal key);
NEStrPtr MapGetDecimalString(Map *map, NEDecimal key);
NEPointer MapGetDecimalPointer(Map *map, NEDecimal key);
NECollection *MapGetDecimalCollection(Map *map, NEDecimal key);

NEByte MapGetStringByte(Map *map, NEStrPtr key);
NEInteger MapGetStringInteger(Map *map, NEStrPtr key);
NEDecimal MapGetStringDecimal(Map *map, NEStrPtr key);
NEStrPtr MapGetStringString(Map *map, NEStrPtr key);
NEPointer MapGetStringPointer(Map *map, NEStrPtr key);
NECollection *MapGetStringCollection(Map *map, NEStrPtr key);

NEByte MapGetPointerByte(Map *map, NEPointer key);
NEInteger MapGetPointerInteger(Map *map, NEPointer key);
NEDecimal MapGetPointerDecimal(Map *map, NEPointer key);
NEStrPtr MapGetPointerString(Map *map, NEPointer key);
NEPointer MapGetPointerPointer(Map *map, NEPointer key);
NECollection *MapGetPointerCollection(Map *map, NEPointer key);

NEByte MapGetCollectionByte(Map *map, NECollection *key);
NEInteger MapGetCollectionInteger(Map *map, NECollection *key);
NEDecimal MapGetCollectionDecimal(Map *map, NECollection *key);
NEStrPtr MapGetCollectionString(Map *map, NECollection *key);
NEPointer MapGetCollectionPointer(Map *map, NECollection *key);
NECollection *MapGetCollectionCollection(Map *map, NECollection *key);
*/

void MapSetByteByte(Map *map, NEByte key, NEByte value);
void MapSetByteInteger(Map *map, NEByte key, NEInteger value);
void MapSetByteDecimal(Map *map, NEByte key, NEDecimal value);
void MapSetByteString(Map *map, NEByte key, NEStrPtr value);
void MapSetBytePointer(Map *map, NEByte key, NEPointer value);
void MapSetByteCollection(Map *map, NEByte key, NECollection *value);

void MapSetIntegerByte(Map *map, NEInteger key, NEByte value);
void MapSetIntegerInteger(Map *map, NEInteger key, NEInteger value);
void MapSetIntegerDecimal(Map *map, NEInteger key, NEDecimal value);
void MapSetIntegerString(Map *map, NEInteger key, NEStrPtr value);
void MapSetIntegerPointer(Map *map, NEInteger key, NEPointer value);
void MapSetIntegerCollection(Map *map, NEInteger key, NECollection *value);

void MapSetDecimalByte(Map *map, NEDecimal key, NEByte value);
void MapSetDecimalInteger(Map *map, NEDecimal key, NEInteger value);
void MapSetDecimalDecimal(Map *map, NEDecimal key, NEDecimal value);
void MapSetDecimalString(Map *map, NEDecimal key, NEStrPtr value);
void MapSetDecimalPointer(Map *map, NEDecimal key, NEPointer value);
void MapSetDecimalCollection(Map *map, NEDecimal key, NECollection *value);

void MapSetStringByte(Map *map, NEStrPtr key, NEByte value);
void MapSetStringInteger(Map *map, NEStrPtr key, NEInteger value);
void MapSetStringDecimal(Map *map, NEStrPtr key, NEDecimal value);
void MapSetStringString(Map *map, NEStrPtr key, NEStrPtr value);
void MapSetStringPointer(Map *map, NEStrPtr key, NEPointer value);
void MapSetStringCollection(Map *map, NEStrPtr key, NECollection *value);

void MapSetPointerByte(Map *map, NEPointer key, NEByte value);
void MapSetPointerInteger(Map *map, NEPointer key, NEInteger value);
void MapSetPointerDecimal(Map *map, NEPointer key, NEDecimal value);
void MapSetPointerString(Map *map, NEPointer key, NEStrPtr value);
void MapSetPointerPointer(Map *map, NEPointer key, NEPointer value);
void MapSetPointerCollection(Map *map, NEPointer key, NECollection *value);

void MapSetCollectionByte(Map *map, NECollection *key, NEByte value);
void MapSetCollectionInteger(Map *map, NECollection *key, NEInteger value);
void MapSetCollectionDecimal(Map *map, NECollection *key, NEDecimal value);
void MapSetCollectionString(Map *map, NECollection *key, NEStrPtr value);
void MapSetCollectionPointer(Map *map, NECollection *key, NEPointer value);
void MapSetCollectionCollection(Map *map, NECollection *key, NECollection *value);

void MapFree(Map *map);

/* Struct and typedef definitions */
typedef struct MapNode {
  NEULong hash;
  KeyValue key;
  KeyValue value;
  NEPointer userDefined;
} MapNode;

typedef struct HashDataRowNode {
  NENode node;
  MapNode data;
} HashDataRowNode;

#endif
