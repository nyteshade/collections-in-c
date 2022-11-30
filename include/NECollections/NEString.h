#ifndef NE_STRING_H
#define NE_STRING_H

#include <stdlib.h>
#include <string.h>

#include <NECollections/NETypes.h>

struct NEString;
struct NECollection;
struct PascalString;

typedef struct NEString {
  char *string;
  NEULong length;

  struct PascalString (*toPascalString)(struct NEString *self);

  char (*charAt)(struct NEString *self, NEULong index);
  int (*compare)(const struct NEString *self, const struct NEString *other);
  int (*compareInsensitive)(const struct NEString *self, const struct NEString *other);
  struct NEString *(*duplicate)(const struct NEString *self);
  struct NEString *(*concat)(struct NEString *self, struct NEString *other);
  struct NEString *(*substring)(struct NEString *self, NEULong start, NEULong length);
  struct NEString *(*splice)(struct NEString *self, NEULong start, NEULong end);
  struct NEString *(*reverse)(struct NEString *self);
  struct NEString *(*toLower)(struct NEString *self);
  struct NEString *(*toUpper)(struct NEString *self);
  struct NEString *(*trim)(struct NEString *self);
  struct NEString *(*trimLeft)(struct NEString *self);
  struct NEString *(*trimRight)(struct NEString *self);
  struct NECollection *(*split)(struct NEString *s, char delimiter);

  void (*free)(struct NEString *self);
} NEString;

typedef struct PascalString {
  char string[256];
} PascalString;

NEString *NEStringCreate(const char *string);
NEString *NEDuplicateNEString(const NEString *string);
NEString *NEStringCreateFromPascalString(const char string[256]);
void NEStringFree(NEString *s);

char NEStringCharAt(NEString *s, unsigned long index);
int NEStringCompare(const NEString *left, const NEString *right);
int NEStringCompareInsensitive(const NEString *left, const NEString *right);
int NEStringCompareInternals(const NEString *left, const NEString *right, NEBool caseInsensitive);
NEString *NEStringConcat(NEString *s, NEString *s2);
NEString *NEStringSubstring(NEString *s, NEULong start, NEULong length);
NEString *NEStringSplice(NEString *s, NEULong start, NEULong end);
NEString *NEStringReverse(NEString *s);
NEString *NEStringSplice(NEString *s, unsigned long start, unsigned long end);
NEString *NEStringSubstring(NEString *s, unsigned long start, unsigned long length);
NEString *NEStringToLower(NEString *s);
NEString *NEStringToUpper(NEString *s);
NEString *NEStringTrim(NEString *s);
NEString *NEStringTrimLeft(NEString *s);
NEString *NEStringTrimRight(NEString *s);
struct NECollection *NEStringSplit(NEString *s, char delimiter);
PascalString NEStringToPascalString(NEString *s);

#endif
