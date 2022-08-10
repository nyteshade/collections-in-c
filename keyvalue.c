#include <stdio.h>
#include <string.h>

#include "keyvalue.h"

KeyValue CreateKeyValueByte(NEByte byte) {
  KeyValue result;

  result.type = NE_BYTE;
  result.data.byte = byte;
  result.length = sizeof(NEByte);

  return result;
}

KeyValue CreateKeyValueInteger(NEInteger integer) {
  return (KeyValue) {
    NE_INTEGER,
    { .integer = integer },
    sizeof(NEInteger)
  };
}

KeyValue CreateKeyValueDecimal(double decimal) {
  return (KeyValue) {
    NE_DECIMAL,
    { .decimal = decimal },
    sizeof(double)
  };
}

KeyValue CreateKeyValueString(const NEStrPtr fromString) {
  KeyValue result = {
    NE_STRING,
    { .string = 0L },
    strlen(fromString) * sizeof(char)
  };

  result.data.string = strdup(fromString);

  return result;
}

KeyValue CreateKeyValuePointer(void *pointer) {
  return (KeyValue) {
    NE_POINTER,
    { .pointer = pointer },
    sizeof(pointer)
  };
}

NEBool CompareKeyValues(KeyValue *left, KeyValue *right) {
  if (left->type != right->type) return 0;

  switch (left->type) {
    case NE_STRING: return strcmp(left->data.string, right->data.string) == 0 ? 1 : 0;
    case NE_INTEGER: return left->data.integer == right->data.integer;
    case NE_DECIMAL: return left->data.decimal == right->data.decimal;
    case NE_POINTER: return left->data.pointer == right->data.pointer;
    case NE_BYTE: return left->data.byte == right->data.byte;
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
  }
  printf("Size: %ld)\n", kv.length);
}
