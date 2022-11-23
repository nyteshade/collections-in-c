#ifndef NE_KEYVALUE_H
#define NE_KEYVALUE_H

#include "types.h"

typedef struct NECollection NECollection;

typedef enum KeyValueType {
  NE_BYTE = 0,
  NE_INTEGER,
  NE_DECIMAL,
  NE_STRING,
  NE_POINTER,
  NE_COLLECTION
} KeyValueType;

typedef union {
  NEByte byte;
  NEInteger integer;
  NEDecimal decimal;
  NEStrPtr string;
  NEPointer pointer;
  NECollection *collection;
} KeyValueUnion;

typedef struct KeyValue {
  KeyValueType type;
  KeyValueUnion data;
  NEULong length;
} KeyValue;

KeyValue CreateKeyValueByte(NEByte byte);
KeyValue CreateKeyValueInteger(NEInteger integer);
KeyValue CreateKeyValueDecimal(NEDecimal decimal);
KeyValue CreateKeyValueString(const NEStrPtr fromString);
KeyValue CreateKeyValuePointer(NEPointer pointer);
KeyValue CreateKeyValueCollection(NECollection *collection);

NEBool CompareKeyValues(KeyValue *left, KeyValue *right);

void PrintKeyValueStruct(const NEStrPtr title, KeyValue kv);

#endif
