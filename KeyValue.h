#ifndef NE_KEYVALUE_H
#define NE_KEYVALUE_H

#include "Types.h"

typedef struct NECollection NECollection;
typedef struct NEMapNode NEMapNode;
typedef struct NEMap NEMap;

typedef enum KeyValueType {
  NE_BYTE = 0,
  NE_INTEGER,
  NE_DECIMAL,
  NE_STRING,
  NE_POINTER,
  NE_COLLECTION,
  NE_MAPNODE,
  NE_MAP
} KeyValueType;

typedef union {
  NEByte byte;
  NEInteger integer;
  NEDecimal decimal;
  NEStrPtr string;
  NEPointer pointer;
  NECollection *collection;
  NEMapNode *mapNode;
  NEMap *map;
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
KeyValue CreateKeyValueMapNode(NEMapNode *mapNode);
KeyValue CreateKeyValueMap(NEMap *map);

NEByte KeyValueGetByte(KeyValue *keyValue);
NEInteger KeyValueGetInteger(KeyValue *keyValue);
NEDecimal KeyValueGetDecimal(KeyValue *keyValue);
NEStrPtr KeyValueGetString(KeyValue *keyValue);
NEPointer KeyValueGetPointer(KeyValue *keyValue);
NECollection *KeyValueGetCollection(KeyValue *keyValue);
NEMapNode *KeyValueGetMapNode(KeyValue *keyValue);
NEMap *KeyValueGetMap(KeyValue *keyValue);

NEBool CompareKeyValues(KeyValue *left, KeyValue *right);

void PrintKeyValueStruct(const NEStrPtr title, KeyValue kv);
void SPrintKeyValueStruct(char *buffer, const NEStrPtr title, KeyValue kv);

#endif
