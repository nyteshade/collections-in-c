#ifndef NE_STRING_H
#define NE_STRING_H

#include <stdlib.h>
#include <string.h>

#include "Types.h"

typedef struct NEString NEString;
typedef struct PascalString PascalString;
typedef struct NECollection NECollection;

typedef struct NEString {
  char *string;
  NEULong length;

  PascalString (*toPascalString)(NEString *self);

  char (*charAt)(NEString *self, NEULong index);
  int (*compare)(NEString *self, NEString *other);
  NEString *(*concat)(NEString *self, NEString *other);
  NEString *(*substring)(NEString *self, NEULong start, NEULong length);
  NEString *(*splice)(NEString *self, NEULong start, NEULong end);
  NEString *(*reverse)(NEString *self);
  NEString *(*toLower)(NEString *self);
  NEString *(*toUpper)(NEString *self);
  NEString *(*trim)(NEString *self);
  NEString *(*trimLeft)(NEString *self);
  NEString *(*trimRight)(NEString *self);
  NECollection *(*split)(NEString *s, char delimiter);

  void (*free)(NEString *self);
} NEString;

typedef struct PascalString {
  char string[256];
} PascalString;

NEString *NEStringCreate(const char *string);
NEString *NEDuplicateNEString(NEString *string);
NEString *NEStringCreateFromPascalString(const char string[256]);
void NEStringFree(NEString *s);

char NEStringCharAt(NEString *s, unsigned long index);
int NEStringCompare(NEString *s, NEString *s2);
NEString *NEStringConcat(NEString *s, NEString *s2);
NEString *NEStringReverse(NEString *s);
NEString *NEStringSplice(NEString *s, unsigned long start, unsigned long end);
NEString *NEStringSubstring(NEString *s, unsigned long start, unsigned long length);
NEString *NEStringToLower(NEString *s);
NEString *NEStringToUpper(NEString *s);
NEString *NEStringTrim(NEString *s);
NEString *NEStringTrimLeft(NEString *s);
NEString *NEStringTrimRight(NEString *s);
NECollection *NEStringSplit(NEString *s, char delimiter);
PascalString NEStringToPascalString(NEString *s);

#endif