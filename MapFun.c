#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"

int main(int argc, char **argv) {
  unsigned long hashsize = 5;
  NEMap *map = NECreateMap(hashsize);
  NEMap *map2 = NECreateMap(20);
  NEMapNode *node;
  NECollection *set = 0L;
  unsigned long size = 0;
  unsigned long i = 0;
  unsigned long index = ne_hash_keyvalue(CreateKeyValueByte('a')) % hashsize;

  printf("Hash value for 'a' is %ld\n", ne_hash_keyvalue(CreateKeyValueByte('a')));
  printf("Hash index for 'a' is %ld\n", index);
  printf("Size of an empty map is %ld bytes\n\n", sizeof(NEMap));

  printf("Setting a -> b in map\n");
  map->setByteByte(map, 'a', 'b');
  printf("Getting a from map -> %c\n", map->getByteByte(map, 'a'));

  printf("Setting b -> a in map\n");
  map->setByteByte(map, 'b', 'a');
  printf("Getting b from map -> %c\n", map->getByteByte(map, 'b'));

  printf("Setting apple to a in map\n");
  map->setStringByte(map, "apple", 'a');
  printf("Getting apple from map -> %c\n", map->getStringByte(map, "apple"));

  printf("Setting c -> d in map\n");
  map->setByteByte(map, 'c', 'd');
  printf("Getting c from map -> %c\n", map->getByteByte(map, 'c'));

  printf("Setting 't' to \"Brie is great\"\n");
  map->setStringString(map, "t", "Brie is great");
  printf("Getting 't' from map -> %s\n", map->getStringString(map, "t"));

  printf("Setting \"name\" to \"Brie\"\n");
  map->setStringString(map, "name", "Brie");
  printf("Getting \"name\" from map -> %s\n", map->getStringString(map, "name"));

  printf("Setting 12 to \"count\"\n");
  map->setIntegerString(map, 12, "count");
  printf("Getting 12 from map -> %s\n", map->getIntegerString(map, 12));

  printf("Setting \"namae\" to \"Brie\"\n");
  map->setStringString(map, "namae", "Brie");
  printf("Getting \"namae\" from map -> %s\n", map->getStringString(map, "namae"));

  printf("Setting \"names\" to 1\n");
  map->setStringInteger(map, "names", 1);
  printf("Getting \"names\" from map -> %ld\n", map->getStringInteger(map, "names"));

  printf("Setting \"namez\" to 1\n");
  map->setStringInteger(map, "namez", 1);
  printf("Getting \"namez\" from map -> %ld\n", map->getStringInteger(map, "namez"));

  printf("  Setting submap \"name\" to \"Brie\"\n");
  map2->setStringString(map2, "name", "Brie");
  printf("  Getting submap \"name\" from submap -> %s\n", map2->getStringString(map2, "name"));
  printf("Setting \"submap\" (%p) to map\n", map2);
  map->setStringMap(map, "submap", map2);
  printf("  Getting \"submap\" from map -> %p\n", map->getStringMap(map, "submap"));
  printf("  Getting name from submap -> %s\n", map->getStringMap(map, "submap")->getStringString(map->getStringMap(map, "submap"), "name"));

  printf("Size is %ld\n", map->countEntries(map));

  printf("\nWe have a map with %ld entries\n", map->countEntries(map));

  NEPrintMap(map);

  set = NEGatherMapNodes(map);
  if (set) {
    size = set->count(set);
    printf("We have a set with %ld entries\n", size);
    for (i = 0; i < size; i++) {
      node = set->mapNodeAt(set, i).value;
      NEPrintMapNode("Node", node);
    }
    NECollectionFree(set);
  }

  NEMapFree(map);
  NEMapFree(map2);

  return 0;
}
