#ifndef NE_MAP_H
#define NE_MAP_H

#include "lists.h"
#include "keyvalue.h"

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

typedef struct MapNodeSet {
  MapNode *data;
  NEULong count;
} MapNodeSet;

typedef struct Map {
  HashDataRowNode **data;
  NEULong *entryCounts;
  NEULong size;

  void (*setByteByte)(struct Map *map, NEByte key, NEByte value);
  void (*setByteInteger)(struct Map *map, NEByte key, NEInteger value);
  void (*setByteDecimal)(struct Map *map, NEByte key, NEDecimal value);
  void (*setByteString)(struct Map *map, NEByte key, NEStrPtr value);
  void (*setBytePointer)(struct Map *map, NEByte key, NEPointer value);

  void (*setIntegerByte)(struct Map *map, NEInteger key, NEByte value);
  void (*setIntegerInteger)(struct Map *map, NEInteger key, NEInteger value);
  void (*setIntegerDecimal)(struct Map *map, NEInteger key, NEDecimal value);
  void (*setIntegerString)(struct Map *map, NEInteger key, NEStrPtr value);
  void (*setIntegerPointer)(struct Map *map, NEInteger key, NEPointer value);

  void (*setDecimalByte)(struct Map *map, NEDecimal key, NEByte value);
  void (*setDecimalInteger)(struct Map *map, NEDecimal key, NEInteger value);
  void (*setDecimalDecimal)(struct Map *map, NEDecimal key, NEDecimal value);
  void (*setDecimalString)(struct Map *map, NEDecimal key, NEStrPtr value);
  void (*setDecimalPointer)(struct Map *map, NEDecimal key, NEPointer value);

  void (*setStringByte)(struct Map *map, NEStrPtr key, NEByte value);
  void (*setStringInteger)(struct Map *map, NEStrPtr key, NEInteger value);
  void (*setStringDecimal)(struct Map *map, NEStrPtr key, NEDecimal value);
  void (*setStringString)(struct Map *map, NEStrPtr key, NEStrPtr value);
  void (*setStringPointer)(struct Map *map, NEStrPtr key, NEPointer value);

  void (*setPointerByte)(struct Map *map, NEPointer key, NEByte value);
  void (*setPointerInteger)(struct Map *map, NEPointer key, NEInteger value);
  void (*setPointerDecimal)(struct Map *map, NEPointer key, NEDecimal value);
  void (*setPointerString)(struct Map *map, NEPointer key, NEStrPtr value);
  void (*setPointerPointer)(struct Map *map, NEPointer key, NEPointer value);

  NEULong (*countEntries)(struct Map *map);
  void (*freeMap)(struct Map *map);
} Map;

NEULong ne_hash(NEUStrPtr str);
NEULong ne_hash_keyvalue(KeyValue key);
NEULong CountMapEntries(Map *map);

void PrintMapNode(const NEStrPtr title, MapNode node);
void PrintMap(Map *map);

MapNode CreateMapNode(KeyValue key, KeyValue value, NEPointer userDefined);
MapNodeSet GatherMapNodes(Map *map);
Map CreateMap(NEULong hashLanes);

void MapSetByteByte(Map *map, NEByte key, NEByte value);
void MapSetByteInteger(Map *map, NEByte key, NEInteger value);
void MapSetByteDecimal(Map *map, NEByte key, NEDecimal value);
void MapSetByteString(Map *map, NEByte key, NEStrPtr value);
void MapSetBytePointer(Map *map, NEByte key, NEPointer value);

void MapSetIntegerByte(Map *map, NEInteger key, NEByte value);
void MapSetIntegerInteger(Map *map, NEInteger key, NEInteger value);
void MapSetIntegerDecimal(Map *map, NEInteger key, NEDecimal value);
void MapSetIntegerString(Map *map, NEInteger key, NEStrPtr value);
void MapSetIntegerPointer(Map *map, NEInteger key, NEPointer value);

void MapSetDecimalByte(Map *map, NEDecimal key, NEByte value);
void MapSetDecimalInteger(Map *map, NEDecimal key, NEInteger value);
void MapSetDecimalDecimal(Map *map, NEDecimal key, NEDecimal value);
void MapSetDecimalString(Map *map, NEDecimal key, NEStrPtr value);
void MapSetDecimalPointer(Map *map, NEDecimal key, NEPointer value);

void MapSetStringByte(Map *map, NEStrPtr key, NEByte value);
void MapSetStringInteger(Map *map, NEStrPtr key, NEInteger value);
void MapSetStringDecimal(Map *map, NEStrPtr key, NEDecimal value);
void MapSetStringString(Map *map, NEStrPtr key, NEStrPtr value);
void MapSetStringPointer(Map *map, NEStrPtr key, NEPointer value);

void MapSetPointerByte(Map *map, NEPointer key, NEByte value);
void MapSetPointerInteger(Map *map, NEPointer key, NEInteger value);
void MapSetPointerDecimal(Map *map, NEPointer key, NEDecimal value);
void MapSetPointerString(Map *map, NEPointer key, NEStrPtr value);
void MapSetPointerPointer(Map *map, NEPointer key, NEPointer value);

void MapFree(Map *map);

#endif
