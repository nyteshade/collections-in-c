#ifndef NE_TYPES_H
#define NE_TYPES_H

typedef unsigned char NEByte;
typedef unsigned char NEBool;
typedef unsigned long NEULong;
typedef unsigned char *NEUStrPtr;
typedef double NEDecimal;
typedef long NEInteger;
typedef long NELong;
typedef void *NEPointer;
typedef char *NEStrPtr;

extern const NEBool NETrue;
extern const NEBool NEFalse;

/**
 * @brief Used by collection map() style methods where data transforms occur
 * to collection items. When items should be kept without any change to the
 * data, use NE_IGNORE. When items should be removed from the resulting
 * collection, use NE_DROP. Lastly, when changes were made, return
 * NE_TRANSFORM.
 */
typedef enum NEDataMapDecision {
  NE_IGNORE,
  NE_DROP,
  NE_TRANSFORM
} NEDataMapDecision;

#endif
