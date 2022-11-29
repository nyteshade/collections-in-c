#include <NECollections/NEString.h>
#include <NECollections/NECollection.h>
#include <NECollections/NEList.h>

#include <ctype.h>

NEString *NEStringCreate(const char *string) {
  NEString *s = (NEString *)calloc(1, sizeof(NEString));
  s->string = strdup(string);
  s->length = strlen(string);

  s->concat = NEStringConcat;
  s->charAt = NEStringCharAt;
  s->compare = NEStringCompare;
  s->compareInsensitive = NEStringCompareInsensitive;
  s->duplicate = NEDuplicateNEString;
  s->reverse = NEStringReverse;
  s->splice = NEStringSplice;
  s->substring = NEStringSubstring;
  s->toPascalString = NEStringToPascalString;
  s->toLower = NEStringToLower;
  s->toUpper = NEStringToUpper;
  s->trim = NEStringTrim;
  s->trimLeft = NEStringTrimLeft;
  s->trimRight = NEStringTrimRight;
  s->split = NEStringSplit;
  s->free = NEStringFree;

  return s;
}

NEString *NEDuplicateNEString(const NEString *string) {
  return NEStringCreate(string->string);
}

NEString *NEStringCreateFromPascalString(const char string[256]) {
  NEString *s = NEStringCreate("");
  if (!s) {
    return NULL;
  }

  if (s->string) {
    free(s->string);
  }

  s->string = calloc(1, 256);
  if (!s->string) {
    free(s);
    return NULL;
  }

  memcpy(s->string, &string[1], 255);
  s->string[255] = '\0';
  s->length = strlen(s->string);

  return s;
}

char NEStringCharAt(NEString *s, unsigned long index) {
  return (char)s->string[index];
}

int NEStringCompare(const NEString *left, const NEString *right) {
  return NEStringCompareInternals(left, right, NEFalse);
}

int NEStringCompareInsensitive(const NEString *left, const NEString *right) {
  return NEStringCompareInternals(left, right, NETrue);
}

int NEStringCompareInternals(const NEString *left, const NEString *right, NEBool caseInsensitive) {
  if (left->length != right->length) {
    return left->length - right->length;
  }

  if (caseInsensitive) {
    return strcasecmp(left->string, right->string);
  } else {
    return strcmp(left->string, right->string);
  }
}

PascalString NEStringToPascalString(NEString *s) {
  PascalString pascalString;
  pascalString.string[0] = (char)s->length;
  strcpy(&pascalString.string[1], s->string);
  return pascalString;
}

NEString *NEStringConcat(NEString *s, NEString *s2) {
  NEString *s3 = NEStringCreate(s->string);
  s3->string = (char *)realloc(s3->string, s3->length + s2->length + 1);
  strcat(s3->string, s2->string);
  s3->length = s3->length + s2->length;

  return s3;
}

NEString *NEStringReverse(NEString *s) {
  unsigned long i = 0;
  unsigned long j = s->length - 1;
  char *string = strdup(s->string);

  while (i < j) {
    char temp = string[i];
    string[i] = string[j];
    string[j] = temp;
    i++;
    j--;
  }

  return NEStringCreate(string);
}

NEString *NEStringSplice(NEString *s, unsigned long start, unsigned long end) {
  unsigned long length = end - start;
  char *string = (char *)calloc(length + 1, sizeof(char));
  strncpy(string, &s->string[start], length);
  return NEStringCreate(string);
}

NEString *NEStringSubstring(NEString *s, unsigned long start, unsigned long length) {
  char *string = (char *)calloc(length + 1, sizeof(char));
  strncpy(string, &s->string[start], length);
  return NEStringCreate(string);
}

NEString *NEStringToLower(NEString *s) {
  char *string = strdup(s->string);
  for (unsigned long i = 0; i < s->length; i++) {
    string[i] = tolower(string[i]);
  }
  return NEStringCreate(string);
}

NEString *NEStringToUpper(NEString *s) {
  char *string = strdup(s->string);
  for (unsigned long i = 0; i < s->length; i++) {
    string[i] = toupper(string[i]);
  }
  return NEStringCreate(string);
}

NEString *NEStringTrim(NEString *s) {
  char *string = strdup(s->string);
  char *start = string;
  char *end = &string[s->length - 1];

  while (isspace(*start)) {
    start++;
  }

  while (isspace(*end)) {
    end--;
  }

  *(end + 1) = '\0';

  return NEStringCreate(start);
}

NEString *NEStringTrimLeft(NEString *s) {
  char *string = strdup(s->string);
  char *start = string;

  while (isspace(*start)) {
    start++;
  }

  return NEStringCreate(start);
}

NEString *NEStringTrimRight(NEString *s) {
  char *string = strdup(s->string);
  char *end = &string[s->length - 1];

  while (isspace(*end)) {
    end--;
  }

  *(end + 1) = '\0';

  return NEStringCreate(string);
}

NECollection *NEStringSplit(NEString *s, char delimiter) {
  NECollection *array = NECollectionCreate();
  char *string = strdup(s->string);
  char *token = strtok(string, &delimiter);

  while (token != NULL) {
    array->addString(array, token);
    token = strtok(NULL, &delimiter);
  }

  return array;
}

void NEStringFree(NEString *s) {
  if (s && s->string) free(s->string);
  if (s) free(s);
}

