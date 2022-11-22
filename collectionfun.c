#include "collection.h"
#include "map.h"

#include <stdio.h>

void printTypesAndValues(KeyValue value, NEULong index);
NEBool filterForStrings(KeyValue value, NEULong index);
NECollectionMapResult mapToInteger(KeyValue value, NEULong index);

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

  printf("Collection Count: %ld\n", collection->count(collection));
  collection->forEach(collection, printTypesAndValues);

  printf("\nSearching for byte 65: %s\n", collection->findByte(collection, 65) ? found : notFound);
  printf("Searching for byte 64: %s\n", collection->findByte(collection, 64) ? found : notFound);
  printf("Searching for integer 365: %s\n", collection->findInteger(collection, 365) ? found : notFound);
  printf("Searching for integer 123: %s\n", collection->findInteger(collection, 123) ? found : notFound);
  printf("Searching for decimal 3.14159: %s\n", collection->findDecimal(collection, 3.14159) ? found : notFound);
  printf("Searching for decimal 1.53232: %s\n", collection->findDecimal(collection, 1.53232) ? found : notFound);
  printf("Searching for string Brielle Was Here (sensitive): %s\n", collection->findString(collection, "Brielle Was Here", NETrue) ? found : notFound);
  printf("Searching for string brielle was here (sensitive): %s\n", collection->findString(collection, "brielle was here", NETrue) ? found : notFound);
  printf("Searching for string Brielle Was Here (insensitive): %s\n", collection->findString(collection, "Brielle Was Here", NEFalse) ? found : notFound);
  printf("Searching for string brielle was here (insensitive): %s\n", collection->findString(collection, "brielle was here", NEFalse) ? found : notFound);
  printf("Searching for pointer %p: %s\n", collection, collection->findPointer(collection, collection) ? found : notFound);
  printf("Searching for pointer %p: %s\n\n", collection->list, collection->findPointer(collection, collection->list) ? found : notFound);

  printf("Item at index 2 should be: decimal 3.14159. It is %f\n", collection->at(collection, 2)->data.decimal);
  printf("Item at index 4 should be: pointer %p. It is %p\n", collection, collection->at(collection, 4)->data.pointer);

  printf("\nFiltering collection for Strings...\n");
  collection2 = collection->filter(collection, filterForStrings);
  printf("Collection Count: %ld\n", collection2->count(collection2));
  collection2->forEach(collection2, printTypesAndValues);
  NECollectionFree(collection2);

  printf("\nMapping collection to Integers...\n");
  collection2 = collection->map(collection, mapToInteger);
  printf("Collection Count: %ld\n", collection2->count(collection2));
  collection2->forEach(collection2, printTypesAndValues);
  NECollectionFree(collection2);

  printf("\nClearing Collection\n");
  collection->clear(collection);
  printf("Collection Count: %ld\n", collection->count(collection));
  collection->forEach(collection, printTypesAndValues);

  NECollectionFree(collection);

  return 0;
}

void printTypesAndValues(KeyValue value, NEULong index) {
  char type[32] = "";
  char string[256] = "";

  switch(value.type) {
    case NE_BYTE:
      sprintf(type, "Byte");
      sprintf(string, "%d", value.data.byte);
      break;
    case NE_INTEGER:
      sprintf(type, "Long");
      sprintf(string, "%ld", value.data.integer);
      break;
    case NE_DECIMAL:
      sprintf(type, "Floating Point");
      sprintf(string, "%f", value.data.decimal);
      break;
    case NE_POINTER:
      sprintf(type, "Pointer");
      sprintf(string, "%p", value.data.pointer);
      break;
    case NE_STRING:
      sprintf(type, "String");
      sprintf(string, "%s", value.data.string);
      break;
  }
  string[255] = '\0';

  printf("  type: %s value: %s\n", type, string);
}

NEBool filterForStrings(KeyValue value, NEULong index) {
  return value.type == NE_STRING;
}

NECollectionMapResult mapToInteger(KeyValue value, NEULong index) {
  NECollectionMapResult result;

  result.value.type = NE_INTEGER;
  result.value.data.integer = 0;
  result.decision = NE_TRANSFORM;

  if(value.type == NE_STRING) {
    result.value.data.integer = ne_hash_keyvalue(value);
  }
  else {
    switch (value.type) {
      case NE_BYTE:
        result.value.data.integer = value.data.byte;
        break;
      case NE_INTEGER:
        result.value.data.integer = value.data.integer;
        break;
      case NE_DECIMAL:
        result.value.data.integer = (NEULong)value.data.decimal;
        break;
      case NE_POINTER:
        result.value.data.integer = (NEULong)value.data.pointer;
        break;
      default:
        break;
    }
  }

  return result;
}
