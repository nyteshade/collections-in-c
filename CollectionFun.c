#include "Collection.h"
#include "Map.h"

#include <stdio.h>

void printTypesAndValues(KeyValue *value, NEULong index);
NEBool filterForStrings(KeyValue *value, NEULong index);
NECollectionMapResult mapToInteger(KeyValue *value, NEULong index);

int main(int argc, char **argv) {
  NECollection *collection = NECollectionCreate();
  NECollection *collection2 = NULL;

  const char found[] = "\x1b[32mFound\x1b[0m";
  const char notFound[] = "\x1b[31mNot Found\x1b[0m";

  collection->addByte(collection, 65);
  collection->addInteger(collection, 365);
  collection->addDecimal(collection, 3.14159);
  collection->addString(collection, "Brielle Was Here");
  collection->addPointer(collection, collection);
  collection->addCollection(collection, NECollectionCreate());

  printf("Collection (%p) Count: %ld\n", collection, collection->count(collection));
  collection->forEach(collection, printTypesAndValues);

  collection2 = (NECollection*)(collection->at(collection, 5)->data.collection);
  printf("\nWorking with sub collection (%p)\n", collection2);
  collection2->addString(collection2, "This is a nested collection");
  collection2->forEach(collection2, printTypesAndValues);

  printf("\nSearching in (%p) for byte 65: %s\n", collection, collection->findByte(collection, 65) ? found : notFound);
  printf("Searching in (%p) for byte 64: %s\n", collection, collection->findByte(collection, 64) ? found : notFound);
  printf("Searching in (%p) for integer 365: %s\n", collection, collection->findInteger(collection, 365) ? found : notFound);
  printf("Searching in (%p) for integer 123: %s\n", collection, collection->findInteger(collection, 123) ? found : notFound);
  printf("Searching in (%p) for decimal 3.14159: %s\n", collection, collection->findDecimal(collection, 3.14159) ? found : notFound);
  printf("Searching in (%p) for decimal 1.53232: %s\n", collection, collection->findDecimal(collection, 1.53232) ? found : notFound);
  printf("Searching in (%p) for string Brielle Was Here (sensitive): %s\n", collection, collection->findString(collection, "Brielle Was Here", NETrue) ? found : notFound);
  printf("Searching in (%p) for string brielle was here (sensitive): %s\n", collection, collection->findString(collection, "brielle was here", NETrue) ? found : notFound);
  printf("Searching in (%p) for string Brielle Was Here (insensitive): %s\n", collection, collection->findString(collection, "Brielle Was Here", NEFalse) ? found : notFound);
  printf("Searching in (%p) for string brielle was here (insensitive): %s\n", collection, collection->findString(collection, "brielle was here", NEFalse) ? found : notFound);
  printf("Searching in (%p) for pointer %p: %s\n", collection, collection, collection->findPointer(collection, collection) ? found : notFound);
  printf("Searching in (%p) for pointer %p: %s\n\n", collection, collection->list, collection->findPointer(collection, collection->list) ? found : notFound);

  printf("Item at index 2 in %p should be: decimal 3.14159. It is %f\n", collection, collection->at(collection, 2)->data.decimal);
  printf("Item at index 4 in %p should be: pointer %p. It is %p\n", collection, collection, collection->at(collection, 4)->data.pointer);

  printf("\nByte at 0 is %d (found: %s)\n", collection->byteAt(collection, 0).value, collection->byteAt(collection, 0).found ? found : notFound);
  printf("Integer at 1 is %ld (found: %s)\n", collection->integerAt(collection, 1).value, collection->integerAt(collection, 1).found ? found : notFound);
  printf("String at 1 is %s (found: %s)\n", collection->stringAt(collection, 1).value, collection->stringAt(collection, 1).found ? found : notFound);
  printf("Decimal at 2 is %f (found: %s)\n", collection->decimalAt(collection, 2).value, collection->decimalAt(collection, 2).found ? found : notFound);
  printf("String at 3 is %s (found: %s)\n", collection->stringAt(collection, 3).value, collection->stringAt(collection, 3).found ? found : notFound);
  printf("Pointer at 4 is %p (found: %s)\n", collection->pointerAt(collection, 4).value, collection->pointerAt(collection, 4).found ? found : notFound);
  printf("Collection at 5 is %p (found: %s)\n", collection->collectionAt(collection, 5).value, collection->collectionAt(collection, 5).found ? found : notFound);

  printf("\nFiltering collection (%p) for Strings...", collection);
  collection2 = collection->filter(collection, filterForStrings);
  printf("(%p) generated\n", collection2);
  printf("Collection (%p) Count: %ld\n", collection2, collection2->count(collection2));
  collection2->forEach(collection2, printTypesAndValues);
  printf("Freeing %p\n", collection2);
  NECollectionFree(collection2);
  collection2 = NULL;

  printf("Collection 1 is %p\n", collection);
  printf("Collection 2 is %p\n", collection2);

  printf("\nMapping collection (%p) to Integers...", collection);
  printf("  using mapToInteger (%p)\n", mapToInteger);
  printf("  collection->map (%p)", collection->map);
  collection2 = collection->map(collection, mapToInteger);
  printf("(%p) generated\n", collection2);
  printf("Collection (%p) Count: %ld\n", collection2, collection2->count(collection2));
  collection2->forEach(collection2, printTypesAndValues);
  printf("Collection 1 is %p\n", collection);
  printf("Collection 2 is %p\n", collection2);
  printf("Freeing collection 2 (%p), with count %ld\n", collection2, collection2->count(collection2));
  NECollectionFree(collection2);
  collection2 = NULL;

  printf("\nClearing Collection (%p)\n", collection);
  collection->clear(collection);
  printf("Collection (%p) Count: %ld\n", collection, collection->count(collection));
  collection->forEach(collection, printTypesAndValues);

  printf("Freeing collection 1 (%p), with count %ld\n", collection, collection->count(collection));
  NECollectionFree(collection);

  return 0;
}

void printTypesAndValues(KeyValue *value, NEULong index) {
  char type[32] = "";
  char string[256] = "";

  switch(value->type) {
    case NE_BYTE:
      sprintf(type, "Byte (%d)", value->type);
      sprintf(string, "%d", value->data.byte);
      break;
    case NE_INTEGER:
      sprintf(type, "Long (%d)", value->type);
      sprintf(string, "%ld", value->data.integer);
      break;
    case NE_DECIMAL:
      sprintf(type, "Floating Point (%d)", value->type);
      sprintf(string, "%f", value->data.decimal);
      break;
    case NE_POINTER:
      sprintf(type, "Pointer (%d)", value->type);
      sprintf(string, "%p", value->data.pointer);
      break;
    case NE_STRING:
      sprintf(type, "String (%d)", value->type);
      sprintf(string, "%s", value->data.string);
      break;
    case NE_NESTRING:
      sprintf(type, "NEString (%d)", value->type);
      sprintf(string, "%s", value->data.neString->string);
      break;
    case NE_COLLECTION:
      sprintf(type, "Collection (%d)", value->type);
      sprintf(string, "%p", value->data.collection);
      break;
    case NE_MAPNODE:
      sprintf(type, "Map Node (%d)", value->type);
      sprintf(string, "%p", value->data.mapNode);
      break;
    case NE_MAP:
      sprintf(type, "Map (%d)", value->type);
      sprintf(string, "%p", value->data.map);
      break;
  }
  string[255] = '\0';

  printf("  address: %p type: %s value: %s\n", value, type, string);
}

NEBool filterForStrings(KeyValue *value, NEULong index) {
  return value->type == NE_STRING;
}

NECollectionMapResult mapToInteger(KeyValue *value, NEULong index) {
  NECollectionMapResult result;

  result.value.type = NE_INTEGER;
  result.value.data.integer = 0;
  result.decision = NE_TRANSFORM;

  switch (value->type) {
    case NE_STRING:
      result.value.data.integer = ne_hash_keyvalue(*value);
      break;
    case NE_BYTE:
      result.value.data.integer = value->data.byte;
      break;
    case NE_INTEGER:
      result.value.data.integer = value->data.integer;
      break;
    case NE_DECIMAL:
      result.value.data.integer = (NEULong)value->data.decimal;
      break;
    case NE_POINTER:
      result.value.data.integer = (NEULong)value->data.pointer;
      break;
    case NE_COLLECTION:
      result.value.data.integer = (NEULong)value->data.collection;
      break;
    case NE_MAPNODE:
      result.value.data.integer = (NEULong)value->data.mapNode;
      break;
    case NE_MAP:
      result.value.data.integer = (NEULong)value->data.map;
      break;
    default:
      break;
  }

  return result;
}
