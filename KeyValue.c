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

NEByte KeyValueGetByte(KeyValue *keyValue) {
  return keyValue->data.byte;
}

NEInteger KeyValueGetInteger(KeyValue *keyValue) {
  return keyValue->data.integer;
}

NEDecimal KeyValueGetDecimal(KeyValue *keyValue) {
  return keyValue->data.decimal;
}

NEStrPtr KeyValueGetString(KeyValue *keyValue) {
  return keyValue->data.string;
}

NEPointer KeyValueGetPointer(KeyValue *keyValue) {
  return keyValue->data.pointer;
}

NECollection *KeyValueGetCollection(KeyValue *keyValue) {
  return keyValue->data.collection;
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
    case NE_MAPNODE: return left->data.mapNode == right->data.mapNode;
  }
}

void SPrintKeyValueStruct(char *buffer, const NEStrPtr title, KeyValue kv) {
  sprintf(buffer, "KeyValue Struct for %s (", title);
  switch (kv.type) {
    case NE_BYTE: sprintf(buffer, "%sType: Byte  Data: '%c'  ", buffer, kv.data.byte); break;
    case NE_INTEGER: sprintf(buffer, "%sType: Integer  Data: %ld  ", buffer, kv.data.integer); break;
    case NE_DECIMAL: sprintf(buffer, "%sType: Decimal  Data: %f  ", buffer, kv.data.decimal); break;
    case NE_STRING: sprintf(buffer, "%sType: String  Data: '%s'  ", buffer, kv.data.string); break;
    case NE_POINTER: sprintf(buffer, "%sType: Pointer  Data: %lx  ", buffer, (NEULong)kv.data.pointer); break;
    case NE_COLLECTION: sprintf(buffer, "%sType: Collection  Data: %lx  ", buffer, (NEULong)kv.data.collection); break;
    case NE_MAPNODE: sprintf(buffer, "%sType: MapNode  Data: %lx  ", buffer, (NEULong)kv.data.mapNode); break;
  }  
  sprintf(buffer, "%sSize: %ld)\n", buffer, kv.length);
}

void PrintKeyValueStruct(const NEStrPtr title, KeyValue kv) {
  char buffer[256];
  SPrintKeyValueStruct(buffer, title, kv);
  printf("%s", buffer);
}