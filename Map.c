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

    case NE_MAPNODE:
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
  MapNode *left = (MapNode *)cur;
  MapNode *right = (MapNode *)target;
  if (CompareKeyValues(&left->key, &right->key))
    return 1;
  return 0;
}

void ne_assign_add_node(Map* map, unsigned long index, MapNode *node) {
  MapNode *list = NULL;

  if (!map) {
    printf("Skipping add, map is NULL\n");
    return;
  }

  if (index >= map->size) {
    printf("Skipping add, index %ld is out of bounds. We have size %ld\n", index, map->size);
    return;
  }

  list = map->data && map->data[index] ? map->data[index] : NULL;

  // Check for an existing first node
  // If there is a first node,
  //   traverse to end (checking for key on each)
  //   if there is a matching key, replace the value
  //   else add new node to end.
  // else
  //   create new first node
  //   set data on first node to data to be set

  if (list) {
    MapNode *cur = list, *next = NULL;

    printf("List is not null for index %ld\n", index);

    while (cur) {
      if (CompareKeyValues(&cur->key, &node->key)) {
        printf("  Found matching key, replacing value in node (%p)\n", cur);
        cur->value = node->value;
        return;
      }
      cur = (MapNode*)cur->node.next;
    }

    // If we get here, we didn't find a matching key
    // so we need to add a new node to the end of the list
    printf("  No matching key found, adding new node to end of list\n");
    cur = list;
    while (cur->node.next) {
      cur = (MapNode*)cur->node.next;
    }

    printf("  Adding new node (%p) to end of list (%p)\n", &node, cur);

    next = (MapNode *)calloc(1, sizeof(MapNode));
    CopyMapNodeData(next, node);
    next->node.next = NULL;
    cur->node.next = (NENode*)next;
    map->entryCounts[index]++;
  } 
  else {
    printf("Creating new list for index %ld\n", index);
    list = (MapNode *)calloc(1, sizeof(MapNode));
    CopyMapNodeData(list, node);
    list->node.next = NULL;
    map->data[index] = list;
    map->entryCounts[index]++;
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

MapNode *CreateMapNode(KeyValue key, KeyValue value, void *userDefined) {
  MapNode *node = (MapNode *)calloc(1, sizeof(MapNode));

  if (!node) {
    return NULL;
  }

  node->hash = ne_hash_keyvalue(key);
  node->key = key;
  node->value = value;
  node->userDefined = userDefined;

  return node;
}

MapNode *CopyMapNode(MapNode *node) {
  MapNode *copy = NULL;

  if (!node) {
    return NULL;
  }

  copy = (MapNode *)calloc(1, sizeof(MapNode));
  copy->hash = node->hash;
  copy->key = node->key;
  copy->value = node->value;
  copy->userDefined = node->userDefined;

  return copy;
}

void CopyMapNodeData(MapNode *dest, MapNode *src) {
  if (!dest || !src) {
    return;
  }

  memset(dest, 0L, sizeof(MapNode));

  dest->hash = src->hash;
  dest->key = src->key;
  dest->value = src->value;
  dest->userDefined = src->userDefined;
}

NECollection *GatherMapNodes(Map *map) {
  // walk through each entry in map data
  //   for each entry walk through the linked list
  //     for each node add to node->data to collection

  NECollection *set = NECollectionCreate();

  if (!map || !map->data) {
    return set;
  }

  for (unsigned long i = 0; i < map->size; i++) {
    MapNode *cur = map->data[i];
    printf("Gathering from index %lu\n", i);
    if (cur) {
      printf("  node at index %lu is valid (%p)\n", i, cur);
      for (MapNode *node = cur; node; node = (MapNode*)node->node.next) {
        printf("    adding node %p to collection\n", node);
        set->addMapNode(set, node);
      }
    }
  }

  return set;
}

Map *CreateMap(unsigned long hashLanes) {
  Map *map = (Map *)calloc(1, sizeof(Map));
  unsigned long i;

  map->data = calloc(hashLanes, sizeof(MapNode*));
  map->entryCounts = calloc(hashLanes, sizeof(unsigned long));
  map->size = hashLanes;

  map->setByteByte = MapSetByteByte;
  map->setByteInteger = MapSetByteInteger;
  map->setByteDecimal = MapSetByteDecimal;
  map->setByteString = MapSetByteString;
  map->setBytePointer = MapSetBytePointer;
  map->setByteCollection = MapSetByteCollection;

  map->setIntegerByte = MapSetIntegerByte;
  map->setIntegerInteger = MapSetIntegerInteger;
  map->setIntegerDecimal = MapSetIntegerDecimal;
  map->setIntegerString = MapSetIntegerString;
  map->setIntegerPointer = MapSetIntegerPointer;
  map->setIntegerCollection = MapSetIntegerCollection;

  map->setDecimalByte = MapSetDecimalByte;
  map->setDecimalInteger = MapSetDecimalInteger;
  map->setDecimalDecimal = MapSetDecimalDecimal;
  map->setDecimalString = MapSetDecimalString;
  map->setDecimalPointer = MapSetDecimalPointer;
  map->setDecimalCollection = MapSetDecimalCollection;

  map->setStringByte = MapSetStringByte;
  map->setStringInteger = MapSetStringInteger;
  map->setStringDecimal = MapSetStringDecimal;
  map->setStringString = MapSetStringString;
  map->setStringPointer = MapSetStringPointer;
  map->setStringCollection = MapSetStringCollection;

  map->setPointerByte = MapSetPointerByte;
  map->setPointerInteger = MapSetPointerInteger;
  map->setPointerDecimal = MapSetPointerDecimal;
  map->setPointerString = MapSetPointerString;
  map->setPointerPointer = MapSetPointerPointer;
  map->setPointerCollection = MapSetPointerCollection;

  map->setCollectionByte = MapSetCollectionByte;
  map->setCollectionInteger = MapSetCollectionInteger;
  map->setCollectionDecimal = MapSetCollectionDecimal;
  map->setCollectionString = MapSetCollectionString;
  map->setCollectionPointer = MapSetCollectionPointer;
  map->setCollectionCollection = MapSetCollectionCollection;

  map->countEntries = CountMapEntries;
  map->freeMap = MapFree;

  return map;
}

void MapSetByteByte(Map *map, unsigned char key, unsigned char value) {
  MapNode *node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void MapSetByteInteger(Map *map, unsigned char key, long value) {
  MapNode *node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetByteDecimal(Map *map, unsigned char key, double value) {
  MapNode *node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetByteString(Map *map, unsigned char key, char *value) {
  MapNode *node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetBytePointer(Map *map, unsigned char key, void *value) {
  MapNode *node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetByteCollection(Map *map, unsigned char key, NECollection *value) {
  MapNode *node = CreateMapNode(CreateKeyValueByte(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetIntegerByte(Map *map, long key, unsigned char value) {
  MapNode *node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetIntegerInteger(Map *map, long key, long value) {
  MapNode *node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetIntegerDecimal(Map *map, long key, double value) {
  MapNode *node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetIntegerString(Map *map, long key, char *value) {
  MapNode *node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void MapSetIntegerPointer(Map *map, long key, void *value) {
  MapNode *node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetIntegerCollection(Map *map, long key, NECollection *value) {
  MapNode *node = CreateMapNode(CreateKeyValueInteger(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetDecimalByte(Map *map, double key, unsigned char value) {
  MapNode *node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetDecimalInteger(Map *map, double key, long value) {
  MapNode *node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetDecimalDecimal(Map *map, double key, double value) {
  MapNode *node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetDecimalString(Map *map, double key, char *value) {
  MapNode *node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetDecimalPointer(Map *map, double key, void *value) {
  MapNode *node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetDecimalCollection(Map *map, double key, NECollection *value) {
  MapNode *node = CreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetStringByte(Map *map, char *key, unsigned char value) {
  MapNode *node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void MapSetStringInteger(Map *map, char *key, long value) {
  MapNode *node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void MapSetStringDecimal(Map *map, char *key, double value) {
  MapNode *node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetStringString(Map *map, char *key, char *value) {
  MapNode *node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void MapSetStringPointer(Map *map, char *key, void *value) {
  MapNode *node = CreateMapNode(CreateKeyValueString(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetStringCollection(Map *map, char *key, NECollection *value) {
  MapNode *node = CreateMapNode(CreateKeyValueString(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetPointerByte(Map *map, void *key, unsigned char value) {
  MapNode *node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetPointerInteger(Map *map, void *key, long value) {
  MapNode *node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetPointerDecimal(Map *map, void *key, double value) {
  MapNode *node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetPointerString(Map *map, void *key, char *value) {
  MapNode *node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetPointerPointer(Map *map, void *key, void *value) {
  MapNode *node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void MapSetPointerCollection(Map *map, void *key, NECollection *value) {
  MapNode *node = CreateMapNode(CreateKeyValuePointer(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetCollectionByte(Map *map, NECollection *key, NEByte value) {
  MapNode *node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetCollectionInteger(Map *map, NECollection *key, long value) {
  MapNode *node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetCollectionDecimal(Map *map, NECollection *key, double value) {
  MapNode *node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetCollectionString(Map *map, NECollection *key, char *value) {
  MapNode *node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetCollectionPointer(Map *map, NECollection *key, void *value) {
  MapNode *node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void MapSetCollectionCollection(Map *map, NECollection *key, NECollection *value) {
  MapNode *node = CreateMapNode(CreateKeyValueCollection(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void MapFree(Map *map) {
  for (unsigned long i = 0; i < map->size; i++) {
    MapNode *node = map->data[i];
    free(node);
  }
  free(map->data);
  free(map->entryCounts);
  free(map);
}

void SPrintMapNode(char *buffer, const NEStrPtr title, MapNode *node) {
  char keyBuffer[1024];
  char valueBuffer[1024];

  memset(keyBuffer, 0, 1024);
  memset(valueBuffer, 0, 1024);

  SPrintKeyValueStruct(keyBuffer, "Key", node->key);
  SPrintKeyValueStruct(valueBuffer, "Value", node->value);

  sprintf(
    buffer, 
    "MapNode for %s (Hash: %ld User Defined: %p)\n  %s  %s", 
    title,
    node->hash, 
    node->userDefined,
    keyBuffer,
    valueBuffer
  );
}

void PrintMapNode(const NEStrPtr title, MapNode *node) {
  char *buffer = calloc(1, sizeof(char) * 10240);
  SPrintMapNode(buffer, title, node);
  printf("%s", buffer);
  free(buffer);
}

void SPrintMap(char *buffer, Map *map) {
  unsigned long i, j, k = 0;
  char title[20];

  if (!map || !map->data) {
    return;
  }

  sprintf(buffer, "Map Hash Lanes: %ld\n", map->size);
  sprintf(buffer, "Map Hash Lane Counts\n");
  for (i = 0; i < map->size; i++) {
    sprintf(buffer, "  %ld: %ld\n", i, map->entryCounts[i]);
  }
  sprintf(buffer, "\nMap Nodes\n");
  for(i = 0; i < map->size; i++) {
    MapNode *node = NULL;
    node = map->data[i];
    sprintf(buffer, "Lane %ld\n", i);
    while (node) {
      sprintf(buffer, "%s  ", title);
      SPrintMapNode(buffer, title, node);
      sprintf(buffer, "\n");
      node = (MapNode*)node->node.next;
    }
  }
}

void PrintMap(Map *map) {
  char buffer[1024];
  SPrintMap(buffer, map);
  printf("%s", buffer);
}
