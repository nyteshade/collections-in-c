#include "Map.h"
#include "Lists.h"
#include "Collection.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

unsigned long
ne_hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

unsigned long
ne_hash_keyvalue(KeyValue key) {
  unsigned long hash = 0;
  unsigned char string[16];
  int i = 0;

  memset(string, 0L, 16);

  switch (key.type) {
    case NE_BYTE:
      string[0] = (unsigned char)key.data.byte;
      return ne_hash((unsigned char *)string);

    case NE_STRING:
      return ne_hash((unsigned char *)key.data.string);

    case NE_COLLECTION:
    case NE_POINTER:
    case NE_DECIMAL:
    case NE_INTEGER:
      for (i = 0; i < sizeof(long); i++)
        string[i] = *((char *)&key.data.integer + i);

      return ne_hash((unsigned char *)string);
  }

  return hash;
}

unsigned char __ne_compare_hash_keys(NENode *cur, NENode *target) {
  HashDataRowNode *left = (HashDataRowNode *)cur;
  HashDataRowNode *right = (HashDataRowNode *)target;
  if (CompareKeyValues(&left->data.key, &right->data.key))
    return 1;
  return 0;
}

void ne_assign_add_node(Map* map, unsigned long index, MapNode node) {
  HashDataRowNode *list = NULL;

  if (!map) {
    return;
  }

  if (map->size >= index) {
    return;
  }

  list = map->data[index];

  if (!list) {
    // If we don't have an active NENode or "list" at the index specified
    // and the index is less than the map size (which is the number of hash
    // lanes) then we can just assign a new node to the index.
    map->data[index] = calloc(1, sizeof(HashDataRowNode));
    map->data[index]->data = node;
    list = map->data[index];
  } else {
    // NENode is the meat of a linked list with only next and prev
    // pointers.  If we already have a "list" which is our NENode,
    // we can use the NENodeAdd function to add a new node to the list

    // Problem: we will just be adding to the end leaving us with a duplicate
    // key in some cases.
    HashDataRowNode *nextNode = 0L;
    NEBool found = NEFalse;

    NEForEachNodeDo(HashDataRowNode*, list, nextNode) {
      if (CompareKeyValues(&nextNode->data.key, &node.key)) {
        // We have a duplicate key, so we need to replace the value
        // with the new value.
        nextNode->data.value = node.value;
        found = NETrue;
        break;
      }
    }

    if (!found) {
    HashDataRowNode *newNode = calloc(1, sizeof(HashDataRowNode));
    newNode->data = node;
    NENodeAdd((NENode *)list, (NENode *)newNode);
  }
}
}

unsigned long CountMapEntries(Map *map) {
  unsigned long i = 0;
  unsigned long size = 0;

  for (i = 0; i < map->size; i++) {
    size += map->entryCounts[i];
  }

  return size;
}

MapNode CreateMapNode(KeyValue key, KeyValue value, void *userDefined) {
  MapNode node;

  memset(&node, 0L, sizeof(MapNode));

  node.hash = ne_hash_keyvalue(key);
  node.key = key;
  node.value = value;
  node.userDefined = userDefined;

  return node;
}

NECollection *GatherMapNodes(Map *map) {
  NECollection *set = NECollectionCreate();
  unsigned long i, j, k = 0;

  if (!map || !map->data) {
    return set;
  }

  for(i = 0; i < map->size; i++) {
    for (j = 0; j < map->entryCounts[i]; j++) {
      HashDataRowNode *node = NULL;
      NEForEachNodeDo(HashDataRowNode*, map->data[i], node) {
        set->addPointer(set, &node->data);
      }
    }
  }

  return set;
}

Map CreateMap(unsigned long hashLanes) {
  Map map;
  unsigned long i;

  map.data = calloc(hashLanes, sizeof(HashDataRowNode*));
  map.entryCounts = calloc(hashLanes, sizeof(unsigned long));
  map.size = hashLanes;

  map.setByteByte = MapSetByteByte;
  map.setByteInteger = MapSetByteInteger;
  map.setByteDecimal = MapSetByteDecimal;
  map.setByteString = MapSetByteString;
  map.setBytePointer = MapSetBytePointer;
  map.setByteCollection = MapSetByteCollection;

  map.setIntegerByte = MapSetIntegerByte;
  map.setIntegerInteger = MapSetIntegerInteger;
  map.setIntegerDecimal = MapSetIntegerDecimal;
  map.setIntegerString = MapSetIntegerString;
  map.setIntegerPointer = MapSetIntegerPointer;
  map.setIntegerCollection = MapSetIntegerCollection;

  map.setDecimalByte = MapSetDecimalByte;
  map.setDecimalInteger = MapSetDecimalInteger;
  map.setDecimalDecimal = MapSetDecimalDecimal;
  map.setDecimalString = MapSetDecimalString;
  map.setDecimalPointer = MapSetDecimalPointer;
  map.setDecimalCollection = MapSetDecimalCollection;

  map.setStringByte = MapSetStringByte;
  map.setStringInteger = MapSetStringInteger;
  map.setStringDecimal = MapSetStringDecimal;
  map.setStringString = MapSetStringString;
  map.setStringPointer = MapSetStringPointer;
  map.setStringCollection = MapSetStringCollection;

  map.setPointerByte = MapSetPointerByte;
  map.setPointerInteger = MapSetPointerInteger;
  map.setPointerDecimal = MapSetPointerDecimal;
  map.setPointerString = MapSetPointerString;
  map.setPointerPointer = MapSetPointerPointer;
  map.setPointerCollection = MapSetPointerCollection;

  map.setCollectionByte = MapSetCollectionByte;
  map.setCollectionInteger = MapSetCollectionInteger;
  map.setCollectionDecimal = MapSetCollectionDecimal;
  map.setCollectionString = MapSetCollectionString;
  map.setCollectionPointer = MapSetCollectionPointer;
  map.setCollectionCollection = MapSetCollectionCollection;

  map.countEntries = CountMapEntries;
  map.freeMap = MapFree;

  return map;
}

void MapSetByteByte(Map *map, unsigned char key, unsigned char value) {
  MapNode node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  PrintMapNode("", node);
  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetByteInteger(Map *map, unsigned char key, long value) {
  MapNode node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetByteDecimal(Map *map, unsigned char key, double value) {
  MapNode node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetByteString(Map *map, unsigned char key, char *value) {
  MapNode node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueString(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetBytePointer(Map *map, unsigned char key, void *value) {
  MapNode node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetByteCollection(Map *map, unsigned char key, NECollection *value) {
  MapNode node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetIntegerByte(Map *map, long key, unsigned char value) {
  MapNode node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetIntegerInteger(Map *map, long key, long value) {
  MapNode node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetIntegerDecimal(Map *map, long key, double value) {
  MapNode node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetIntegerString(Map *map, long key, char *value) {
  MapNode node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueString(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  PrintMapNode("", node);
  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetIntegerPointer(Map *map, long key, void *value) {
  MapNode node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetIntegerCollection(Map *map, long key, NECollection *value) {
  MapNode node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetDecimalByte(Map *map, double key, unsigned char value) {
  MapNode node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetDecimalInteger(Map *map, double key, long value) {
  MapNode node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetDecimalDecimal(Map *map, double key, double value) {
  MapNode node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetDecimalString(Map *map, double key, char *value) {
  MapNode node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueString(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetDecimalPointer(Map *map, double key, void *value) {
  MapNode node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetDecimalCollection(Map *map, double key, NECollection *value) {
  MapNode node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetStringByte(Map *map, char *key, unsigned char value) {
  MapNode node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  PrintMapNode("", node);
  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetStringInteger(Map *map, char *key, long value) {
  MapNode node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  PrintMapNode("", node);
  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetStringDecimal(Map *map, char *key, double value) {
  MapNode node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetStringString(Map *map, char *key, char *value) {
  MapNode node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueString(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  PrintMapNode("", node);
  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetStringPointer(Map *map, char *key, void *value) {
  MapNode node = CreateMapNode(CreateKeyValueString(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetStringCollection(Map *map, char *key, NECollection *value) {
  MapNode node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetPointerByte(Map *map, void *key, unsigned char value) {
  MapNode node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetPointerInteger(Map *map, void *key, long value) {
  MapNode node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetPointerDecimal(Map *map, void *key, double value) {
  MapNode node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetPointerString(Map *map, void *key, char *value) {
  MapNode node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueString(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetPointerPointer(Map *map, void *key, void *value) {
  MapNode node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}
void MapSetPointerCollection(Map *map, void *key, NECollection *value) {
  MapNode node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetCollectionByte(Map *map, NECollection *key, NEByte value) {
  MapNode node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetCollectionInteger(Map *map, NECollection *key, long value) {
  MapNode node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetCollectionDecimal(Map *map, NECollection *key, double value) {
  MapNode node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetCollectionString(Map *map, NECollection *key, char *value) {
  MapNode node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueString(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetCollectionPointer(Map *map, NECollection *key, void *value) {
  MapNode node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapSetCollectionCollection(Map *map, NECollection *key, NECollection *value) {
  MapNode node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node.hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapFree(Map *map) {
  for (unsigned long i = 0; i < map->size; i++) {
    HashDataRowNode *node = map->data[i];
    free(node);
  }
  free(map->data);
  free(map->entryCounts);
  free(map);
}

void PrintMapNode(const NEStrPtr title, MapNode node) {
  printf("MapNode for %s (Hash: %ld User Defined: %lx)\n", title, node.hash, (unsigned long)node.userDefined);
  printf("  ");PrintKeyValueStruct("Key", node.key);
  printf("  ");PrintKeyValueStruct("Value", node.value);
}

void PrintMap(Map *map) {
  unsigned long i, j, k = 0;
  char title[20];

  if (!map || !map->data) {
    return;
  }

  printf("Map Hash Lanes: %ld\n", map->size);
  printf("Map Hash Lane Counts\n");
  for (i = 0; i < map->size; i++) {
    printf("  %ld: %ld\n", i, map->entryCounts[i]);
  }
  printf("\nMap Nodes\n");
  for(i = 0; i < map->size; i++) {
    HashDataRowNode *node = NULL;
    node = map->data[i];
    printf("Lane %ld\n", i);
    while (node) {
      sprintf(title, "");
      printf("  ");PrintMapNode(title, node->data);printf("\n");
      node = (HashDataRowNode*)node->node.next;
    }
  }
}
