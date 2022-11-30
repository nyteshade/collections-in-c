#ifndef NE_KEYVALUE_H
#define NE_KEYVALUE_H

#include <NECollections/NETypes.h>

#ifndef NE_COLLECTION_H
struct NECollection;
#endif

#ifndef NE_MAPNODE_H
struct NEMapNode;
#endif

#ifndef NE_MAP_H
struct NEMap;
#endif

#ifndef NE_STRING_H
struct NEString;
#endif

typedef enum KeyValueType {
  NE_BYTE = 0,
  NE_INTEGER,
  NE_DECIMAL,
  NE_STRING,
  NE_NESTRING,
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
  struct NEString *neString;
  NEPointer pointer;
  struct NECollection *collection;
  struct NEMapNode *mapNode;
  struct NEMap *map;
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
KeyValue CreateKeyValueNEString(struct NEString *fromString);
KeyValue CreateKeyValuePointer(NEPointer pointer);
KeyValue CreateKeyValueCollection(struct NECollection *collection);
KeyValue CreateKeyValueMapNode(struct NEMapNode *mapNode);
KeyValue CreateKeyValueMap(struct NEMap *map);

NEByte KeyValueGetByte(KeyValue *keyValue);
NEInteger KeyValueGetInteger(KeyValue *keyValue);
NEDecimal KeyValueGetDecimal(KeyValue *keyValue);
NEStrPtr KeyValueGetString(KeyValue *keyValue);
struct NEString *KeyValueGetNEString(KeyValue *keyValue);
NEPointer KeyValueGetPointer(KeyValue *keyValue);
struct NECollection *KeyValueGetCollection(KeyValue *keyValue);
struct NEMapNode *KeyValueGetMapNode(KeyValue *keyValue);
struct NEMap *KeyValueGetMap(KeyValue *keyValue);

NEBool CompareKeyValues(KeyValue *left, KeyValue *right);

void PrintKeyValueStruct(const NEStrPtr title, KeyValue kv);
void SPrintKeyValueStruct(char *buffer, const NEStrPtr title, KeyValue kv);

#endif
