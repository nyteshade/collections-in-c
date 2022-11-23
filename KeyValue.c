#include <stdio.h>
#include <string.h>

#include "KeyValue.h"
#include "Collection.h"

KeyValue CreateKeyValueByte(NEByte byte) {
  KeyValue result;

  result.type = NE_BYTE;
  result.data.byte = byte;
  result.length = sizeof(NEByte);

  return result;
}

KeyValue CreateKeyValueInteger(NEInteger integer) {
  KeyValue result;

  result.type = NE_INTEGER;
  result.data.integer = integer;
  result.length = sizeof(NEInteger);

  return result;
}

KeyValue CreateKeyValueDecimal(double decimal) {
  KeyValue result;

  result.type = NE_DECIMAL;
  result.data.decimal = decimal;
  result.length = sizeof(double);

  return result;
}

KeyValue CreateKeyValueString(const NEStrPtr fromString) {
  KeyValue result;

  result.type = NE_STRING;
  result.data.string = strdup(fromString);
  result.length = strlen(fromString);

  return result;
}

KeyValue CreateKeyValuePointer(void *pointer) {
  KeyValue result;

  result.type = NE_POINTER;
  result.data.pointer = pointer;
  result.length = sizeof(void *);

  return result;
}

KeyValue CreateKeyValueCollection(NECollection *collection) {
  KeyValue result;

  result.type = NE_COLLECTION;
  result.data.collection = collection;
  result.length = sizeof(NECollection *);

  return result;
}

NEBool CompareKeyValues(KeyValue *left, KeyValue *right) {
  if (left->type != right->type) return 0;

  switch (left->type) {
    case NE_STRING: return strcmp(left->data.string, right->data.string) == 0 ? 1 : 0;
    case NE_INTEGER: return left->data.integer == right->data.integer;
    case NE_DECIMAL: return left->data.decimal == right->data.decimal;
    case NE_POINTER: return left->data.pointer == right->data.pointer;
    case NE_BYTE: return left->data.byte == right->data.byte;
    case NE_COLLECTION: return left->data.collection == right->data.collection;
  }
}

void PrintKeyValueStruct(const NEStrPtr title, KeyValue kv) {
  printf("KeyValue Struct for %s (", title);
  switch (kv.type) {
    case NE_BYTE: printf("Type: Byte  Data: '%c'  ", kv.data.byte); break;
    case NE_INTEGER: printf("Type: Integer  Data: %ld  ", kv.data.integer); break;
    case NE_DECIMAL: printf("Type: Decimal  Data: %f  ", kv.data.decimal); break;
    case NE_STRING: printf("Type: String  Data: '%s'  ", kv.data.string); break;
    case NE_POINTER: printf("Type: Pointer  Data: %lx  ", (NEULong)kv.data.pointer); break;
    case NE_COLLECTION: printf("Type: Collection  Data: %lx  ", (NEULong)kv.data.collection); break;
  }
  printf("Size: %ld)\n", kv.length);
}
