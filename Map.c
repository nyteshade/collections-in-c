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

    case NE_MAP:
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
  NEMapNode *left = (NEMapNode *)cur;
  NEMapNode *right = (NEMapNode *)target;
  if (CompareKeyValues(&left->key, &right->key))
    return 1;
  return 0;
}

void ne_assign_add_node(NEMap* map, unsigned long index, NEMapNode *node) {
  NEMapNode *list = NULL;

  if (!map || (index >= map->size)) {
    return;
  }

  list = map->data && map->data[index] ? map->data[index] : NULL;

  if (list) {
    NEMapNode *cur = list, *next = NULL;

    while (cur) {
      if (CompareKeyValues(&cur->key, &node->key)) {
        cur->value = node->value;
        return;
      }
      cur = (NEMapNode*)cur->node.next;
    }

    // If we get here, we didn't find a matching key
    // so we need to add a new node to the end of the list
    cur = list;
    while (cur->node.next) {
      cur = (NEMapNode*)cur->node.next;
    }

    next = (NEMapNode *)calloc(1, sizeof(NEMapNode));
    NECopyMapNodeData(next, node);
    next->node.next = NULL;
    cur->node.next = (NENode*)next;
    map->entryCounts[index]++;
  } 
  else {
    list = (NEMapNode *)calloc(1, sizeof(NEMapNode));
    NECopyMapNodeData(list, node);
    list->node.next = NULL;
    map->data[index] = list;
    map->entryCounts[index]++;
  }
}

unsigned long NECountMapEntries(NEMap *map) {
  unsigned long i = 0;
  unsigned long size = 0;

  for (i = 0; i < map->size; i++) {
    size += map->entryCounts[i];
  }

  return size;
}

NEMapNode *NECreateMapNode(KeyValue key, KeyValue value, void *userDefined) {
  NEMapNode *node = (NEMapNode *)calloc(1, sizeof(NEMapNode));

  if (!node) {
    return NULL;
  }

  node->hash = ne_hash_keyvalue(key);
  node->key = key;
  node->value = value;
  node->userDefined = userDefined;

  return node;
}

NEMapNode *NEDuplicateMapNode(NEMapNode *node) {
  NEMapNode *copy = NULL;

  if (!node) {
    return NULL;
  }

  copy = (NEMapNode *)calloc(1, sizeof(NEMapNode));
  copy->hash = node->hash;
  copy->key = node->key;
  copy->value = node->value;
  copy->userDefined = node->userDefined;

  return copy;
}

void NECopyMapNodeData(NEMapNode *dest, NEMapNode *src) {
  if (!dest || !src) {
    return;
  }

  memset(dest, 0L, sizeof(NEMapNode));

  dest->hash = src->hash;
  dest->key = src->key;
  dest->value = src->value;
  dest->userDefined = src->userDefined;
}

NECollection *NEGatherMapNodes(NEMap *map) {
  NECollection *set = NECollectionCreate();

  if (!map || !map->data) {
    return set;
  }

  for (unsigned long i = 0; i < map->size; i++) {
    NEMapNode *cur = map->data[i];
    //printf("Gathering from index %lu\n", i);
    if (cur) {
      //printf("  node at index %lu is valid (%p)\n", i, cur);
      for (NEMapNode *node = cur; node; node = (NEMapNode*)node->node.next) {
        //printf("    adding node %p to collection\n", node);
        set->addMapNode(set, node);
      }
    }
  }

  return set;
}

NEMap *NECreateMap(unsigned long hashLanes) {
  NEMap *map = (NEMap *)calloc(1, sizeof(NEMap));
  unsigned long i;

  map->data = calloc(hashLanes, sizeof(NEMapNode*));
  map->entryCounts = calloc(hashLanes, sizeof(unsigned long));
  map->size = hashLanes;

  map->setByteByte = NEMapSetByteByte;
  map->setByteInteger = NEMapSetByteInteger;
  map->setByteDecimal = NEMapSetByteDecimal;
  map->setByteString = NEMapSetByteString;
  map->setBytePointer = NEMapSetBytePointer;
  map->setByteCollection = NEMapSetByteCollection;
  map->setByteMap = NEMapSetByteMap;

  map->setIntegerByte = NEMapSetIntegerByte;
  map->setIntegerInteger = NEMapSetIntegerInteger;
  map->setIntegerDecimal = NEMapSetIntegerDecimal;
  map->setIntegerString = NEMapSetIntegerString;
  map->setIntegerPointer = NEMapSetIntegerPointer;
  map->setIntegerCollection = NEMapSetIntegerCollection;
  map->setIntegerMap = NEMapSetIntegerMap;

  map->setDecimalByte = NEMapSetDecimalByte;
  map->setDecimalInteger = NEMapSetDecimalInteger;
  map->setDecimalDecimal = NEMapSetDecimalDecimal;
  map->setDecimalString = NEMapSetDecimalString;
  map->setDecimalPointer = NEMapSetDecimalPointer;
  map->setDecimalCollection = NEMapSetDecimalCollection;
  map->setDecimalMap = NEMapSetDecimalMap;

  map->setStringByte = NEMapSetStringByte;
  map->setStringInteger = NEMapSetStringInteger;
  map->setStringDecimal = NEMapSetStringDecimal;
  map->setStringString = NEMapSetStringString;
  map->setStringPointer = NEMapSetStringPointer;
  map->setStringCollection = NEMapSetStringCollection;
  map->setStringMap = NEMapSetStringMap;

  map->setPointerByte = NEMapSetPointerByte;
  map->setPointerInteger = NEMapSetPointerInteger;
  map->setPointerDecimal = NEMapSetPointerDecimal;
  map->setPointerString = NEMapSetPointerString;
  map->setPointerPointer = NEMapSetPointerPointer;
  map->setPointerCollection = NEMapSetPointerCollection;
  map->setPointerMap = NEMapSetPointerMap;

  map->setCollectionByte = NEMapSetCollectionByte;
  map->setCollectionInteger = NEMapSetCollectionInteger;
  map->setCollectionDecimal = NEMapSetCollectionDecimal;
  map->setCollectionString = NEMapSetCollectionString;
  map->setCollectionPointer = NEMapSetCollectionPointer;
  map->setCollectionCollection = NEMapSetCollectionCollection;
  map->setCollectionMap = NEMapSetCollectionMap;

  map->setMapByte = NEMapSetMapByte;
  map->setMapInteger = NEMapSetMapInteger;
  map->setMapDecimal = NEMapSetMapDecimal;
  map->setMapString = NEMapSetMapString;
  map->setMapPointer = NEMapSetMapPointer;
  map->setMapCollection = NEMapSetMapCollection;
  map->setMapMap = NEMapSetMapMap;

  map->countEntries = NECountMapEntries;
  map->freeMap = NEMapFree;

  return map;
}

void NEMapSetByteByte(NEMap *map, unsigned char key, unsigned char value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueByte(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void NEMapSetByteInteger(NEMap *map, unsigned char key, long value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueByte(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetByteDecimal(NEMap *map, unsigned char key, double value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueByte(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetByteString(NEMap *map, unsigned char key, char *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueByte(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetBytePointer(NEMap *map, unsigned char key, void *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueByte(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetByteCollection(NEMap *map, unsigned char key, NECollection *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueByte(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetByteMap(NEMap *map, unsigned char key, NEMap *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueByte(key), CreateKeyValueMap(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetIntegerByte(NEMap *map, long key, unsigned char value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueInteger(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetIntegerInteger(NEMap *map, long key, long value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueInteger(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetIntegerDecimal(NEMap *map, long key, double value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueInteger(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetIntegerString(NEMap *map, long key, char *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueInteger(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void NEMapSetIntegerPointer(NEMap *map, long key, void *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueInteger(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetIntegerCollection(NEMap *map, long key, NECollection *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueInteger(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetIntegerMap(NEMap *map, long key, NEMap *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueInteger(key), CreateKeyValueMap(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetDecimalByte(NEMap *map, double key, unsigned char value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetDecimalInteger(NEMap *map, double key, long value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetDecimalDecimal(NEMap *map, double key, double value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetDecimalString(NEMap *map, double key, char *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetDecimalPointer(NEMap *map, double key, void *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueDecimal(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetDecimalCollection(NEMap *map, double key, NECollection *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetDecimalMap(NEMap *map, double key, NEMap *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueDecimal(key), CreateKeyValueMap(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetStringByte(NEMap *map, char *key, unsigned char value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueString(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void NEMapSetStringInteger(NEMap *map, char *key, long value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueString(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void NEMapSetStringDecimal(NEMap *map, char *key, double value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueString(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetStringString(NEMap *map, char *key, char *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueString(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];
  ne_assign_add_node(map, index, node);
}
void NEMapSetStringPointer(NEMap *map, char *key, void *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueString(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetStringCollection(NEMap *map, char *key, NECollection *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueString(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetStringMap(NEMap *map, char *key, NEMap *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueString(key), CreateKeyValueMap(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetPointerByte(NEMap *map, void *key, unsigned char value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValuePointer(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetPointerInteger(NEMap *map, void *key, long value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValuePointer(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetPointerDecimal(NEMap *map, void *key, double value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValuePointer(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetPointerString(NEMap *map, void *key, char *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValuePointer(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetPointerPointer(NEMap *map, void *key, void *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValuePointer(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetPointerCollection(NEMap *map, void *key, NECollection *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValuePointer(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}
void NEMapSetPointerMap(NEMap *map, void *key, NEMap *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValuePointer(key), CreateKeyValueMap(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetCollectionByte(NEMap *map, NECollection *key, NEByte value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueCollection(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetCollectionInteger(NEMap *map, NECollection *key, long value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueCollection(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetCollectionDecimal(NEMap *map, NECollection *key, double value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueCollection(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetCollectionString(NEMap *map, NECollection *key, char *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueCollection(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetCollectionPointer(NEMap *map, NECollection *key, void *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueCollection(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetCollectionCollection(NEMap *map, NECollection *key, NECollection *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueCollection(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
  map->entryCounts[index]++;
}

void NEMapSetCollectionMap(NEMap *map, NECollection *key, NEMap *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueCollection(key), CreateKeyValueMap(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetMapByte(NEMap *map, NEMap *key, NEByte value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueMap(key), CreateKeyValueByte(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetMapInteger(NEMap *map, NEMap *key, long value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueMap(key), CreateKeyValueInteger(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetMapDecimal(NEMap *map, NEMap *key, double value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueMap(key), CreateKeyValueDecimal(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetMapString(NEMap *map, NEMap *key, char *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueMap(key), CreateKeyValueString(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetMapPointer(NEMap *map, NEMap *key, void *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueMap(key), CreateKeyValuePointer(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetMapCollection(NEMap *map, NEMap *key, NECollection *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueMap(key), CreateKeyValueCollection(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapSetMapMap(NEMap *map, NEMap *key, NEMap *value) {
  NEMapNode *node = NECreateMapNode(CreateKeyValueMap(key), CreateKeyValueMap(value), NULL);
  unsigned long index = node->hash % map->size;
  unsigned long curItemsAtIndex = map->entryCounts[index];

  ne_assign_add_node(map, index, node);
}

void NEMapFree(NEMap *map) {
  for (unsigned long i = 0; i < map->size; i++) {
    NEMapNode *node = map->data[i];
    free(node);
  }
  free(map->data);
  free(map->entryCounts);
  free(map);
}

void NESPrintMapNode(char *buffer, const NEStrPtr title, NEMapNode *node) {
  char keyBuffer[1024];
  char valueBuffer[1024];

  memset(keyBuffer, 0, 1024);
  memset(valueBuffer, 0, 1024);

  SPrintKeyValueStruct(keyBuffer, "Key", node->key);
  SPrintKeyValueStruct(valueBuffer, "Value", node->value);

  sprintf(
    buffer, 
    "NEMapNode for %s (Hash: %ld User Defined: %p)\n  %s  %s", 
    title,
    node->hash, 
    node->userDefined,
    keyBuffer,
    valueBuffer
  );
}

void NEPrintMapNode(const NEStrPtr title, NEMapNode *node) {
  char *buffer = calloc(1, sizeof(char) * 10240);
  NESPrintMapNode(buffer, title, node);
  printf("%s", buffer);
  free(buffer);
}

void NESPrintMap(char *buffer, NEMap *map) {
  unsigned long i, j, k = 0;
  char title[20];

  if (!map || !map->data) {
    return;
  }

  sprintf(buffer, "NEMap Hash Lanes: %ld\n", map->size);
  sprintf(buffer, "NEMap Hash Lane Counts\n");
  for (i = 0; i < map->size; i++) {
    sprintf(buffer, "  %ld: %ld\n", i, map->entryCounts[i]);
  }
  sprintf(buffer, "\nMap Nodes\n");
  for(i = 0; i < map->size; i++) {
    NEMapNode *node = NULL;
    node = map->data[i];
    sprintf(buffer, "Lane %ld\n", i);
    while (node) {
      sprintf(buffer, "%s  ", title);
      NESPrintMapNode(buffer, title, node);
      sprintf(buffer, "\n");
      node = (NEMapNode*)node->node.next;
    }
  }
}

void NEPrintMap(NEMap *map) {
  char buffer[1024];
  NESPrintMap(buffer, map);
  printf("%s", buffer);
}
