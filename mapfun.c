#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

int main(int argc, char **argv) {
  unsigned long hashsize = 5;
  Map map = CreateMap(hashsize);
  MapNode node;
  NECollection *set = 0L;
  unsigned long size = 0;
  unsigned long i = 0;
  unsigned long index = ne_hash_keyvalue(CreateKeyValueByte('a')) % hashsize;

  printf("Hash value for 'a' is %ld\n", index);

  printf("Setting a -> b in map\n");
  map.setByteByte(&map, 'a', 'b');

  printf("Setting b -> a in map\n");
  map.setByteByte(&map, 'b', 'a');

  printf("Setting apple to a in map\n");
  map.setStringByte(&map, "apple", 'a');

  printf("Setting c -> d in map\n");
  map.setByteByte(&map, 'c', 'd');

  printf("Setting 't' to \"Brie is great\"\n");
  map.setStringString(&map, "t", "Brie is great");

  printf("Setting \"name\" to \"Brie\"\n");
  map.setStringString(&map, "name", "Brie");

  printf("Setting 12 to \"count\"\n");
  map.setIntegerString(&map, 12, "count");

  printf("Setting \"namae\" to \"Brie\"\n");
  map.setStringString(&map, "namae", "Brie");

  printf("Setting \"names\" to 1\n");
  map.setStringInteger(&map, "names", 1);

  printf("Setting \"namez\" to 1\n");
  map.setStringInteger(&map, "namez", 1);

  printf("Size is %ld\n", map.countEntries(&map));

  //node = map.data[index]->data;

  printf("\nWe have a map with %ld entries\n", map.countEntries(&map));

  set = GatherMapNodes(&map);
  if (set) {
    

  for (i = 0; i < set.count; i++) {
    PrintKeyValueStruct("Set key", set.data[i].key);
  }

  printf("---------------------\n");
  PrintMap(&map);

  return 0;
}
