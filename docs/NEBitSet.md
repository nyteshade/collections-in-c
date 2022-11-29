# NEBitSet

## Description
The `NEBitSet` entity is a collection of bits that can be set and cleared. It is an easy way to store many of the boolean flags in the least amount of space. To use it, one specifies the number of bits, or boolean states, that your desired bitset will use. These are broken up internally as bytes. One byte holds 8 bits. If you need 15 bits, 2 bytes will still be used.

## API

### API Usage Note
The NEBitSet struct will have several function pointers within to approximate an object oriented use of the structure. These function pointers will be initialized upon usage to point the standalone versions which can alternatively also be called directly. As an example:

```c
// Manage 8 bits or one byte
NEBitSet *bs = NEBitSetCreate(8);

bs->set(bs, 0);     // This toggles the first or 0th bit to a 1 position
NEBitSetSet(bs, 0); // This is identical to calling the internal function pointer
                    // as seen in the line above. bs->set == NEBitSetSet
```

### Structures
```c
typedef struct NEBitSet {
  unsigned char *bits;
  int nbits;

  void (*set)(struct NEBitSet *bs, int bit);
  void (*clear)(struct NEBitSet *bs, int bit);
  void (*clearAll)(struct NEBitSet *bs);
  void (*invert)(struct NEBitSet *bs);
  int (*test)(struct NEBitSet *bs, int bit);
  void (*print)(struct NEBitSet *bs);
  void (*printWithSpacing)(struct NEBitSet *bs, char everyFour, char everyEight);
  void (*destroy)(struct NEBitSet *bs);
  unsigned long (*toDecimal)(struct NEBitSet *bs);
  NEBitConversion (*convert)(struct NEBitSet *bs);
  void (*calculateFromBinary)(struct NEBitSet *bs, const char *fromBinaryString);
  void (*calculateFromNumber)(struct NEBitSet *bs, long fromNumber);
} NEBitSet;
```
This structure is the primary instance of a NEBitSet entity. It contains the properties required for storing the bits and the function pointers to manage the bits' state.

```c
typedef struct NEBitConversion {
  unsigned char string[1024];
  unsigned long integer;
} NEBitConversion;
```
This structure is primary a return type from the `NEBitSetConvert` function. It contains an array of characters allowing it to store a return string without the need to worry about memory allocation or deallocation. It will dissapear once out of scope, though it does incur a 1Kb memory storage while in scope.

The `.string` property will contain a binary string representation of the NEBitSet. A value of 7 would be represented by the string "0111" for example.
The `.integer` property will contain the numeric integer value of the NEBitSet. This can sometimes be useful.

### Functions

```c
NEBitSet *NEBitSetCreate(int nbits);
```
The `NEBitSetCreate` function is the expected way to initialize a new `NEBitSet` instance. It automatically allocates the correct amount of memory for a given instance and assigns all the internal function pointers appropriately. Struct instances not created in this manner run the risk of being severly broken.


```c
void NEBitSetDestroy(NEBitSet *bs);
```
The `NEBitSetDestroy` function is the expected way to destroy a `NEBitSet` instance. It frees the associate memory that had been allocated.


```c
void NEBitSetSet(struct NEBitSet *bs, int bit);
```
The `NEBitSetSet` function is the expected way to set a bit in a `NEBitSet` instance. The bit parameter indicates the numeric distance from the lowest value (0) to the highest value (number of bits - 1). When invoked the bit at that location is set to 1. If invoked repeatedly on an already set bit, it is essentially a non-op function; though the work will still be performed.


```c
void NEBitSetClear(struct NEBitSet *bs, int bit);
```
The `NEBitSetClear` function is the expected way to clear a bit in a `NEBitSet` instance. The bit at the numeric location is set to 0. This being the opposite of `NEBitSetSet` (see above).


```c
void NEBitSetClearAll(struct NEBitSet *bs);
```
The `NEBitSetClearAll` function is the expected way to clear all bits in a `NEBitSet` instance. All bits are set to 0.


```c
void NEBitSetInvert(struct NEBitSet *bs);
```
The `NEBitSetInvert` function is the expected way to invert all bits in a `NEBitSet` instance. All bits are flipped from 0 to 1 and vice versa.


```c
int NEBitSetTest(struct NEBitSet *bs, int bit);
```
The `NEBitSetTest` function is the expected way to test a bit in a `NEBitSet` instance. The bit at the numeric location is returned as a 1 or 0. This is useful for checking the state of a bit without changing it.


```c
void NEBitSetPrint(struct NEBitSet *bs);
```
The `NEBitSetPrint` function is the expected way to print a `NEBitSet` instance. The bitset is printed as a binary string. For example, a bitset with 8 bits would print as "00000000".


```c
void NEBitSetPrintWithSpacing(struct NEBitSet *bs, char everyFour, char everyEight);
```
The `NEBitSetPrintWithSpacing` function is the expected way to print a `NEBitSet` instance. The bitset is printed as a binary string with optional spacing. For example, a bitset with 8 bits would print as "00000000" with the default spacing. The `everyFour` and `everyEight` parameters are boolean values. If they are set to 1, then the spacing will occur. If they are set to 0, then the spacing will not occur. A 32 bit NEBitSet printed with all possible options would appear as follows.

```c
00000000000000000000000000000000            // everyFour: false, everyEight: false
0000 0000 0000 0000 0000 0000 0000 0000     // everyFour: true, everyEight: false
0000 0000  0000 0000  0000 0000  0000 0000  // everyFour: true, everyEight: true
00000000 00000000 00000000 00000000         // everyFour: false, everyEight: true
```

```c
unsigned long NEBitSetToDecimal(struct NEBitSet *bs);
```
The `NEBitSetToDecimal` function is the expected way to convert a `NEBitSet` instance to a decimal number. The bitset is converted to a decimal number and returned as an unsigned long. This is useful for converting a bitset to a number for use in other calculations.


```c
NEBitConversion NEBitSetConvert(struct NEBitSet *bs);
```
The `NEBitSetConvert` function is the expected way to convert a `NEBitSet` instance to a string and a decimal number. The bitset is converted to a decimal number and returned as an unsigned long. This is useful for converting a bitset to a number for use in other calculations. The bitset is also converted to a string and returned as a `NEBitConversion` struct. This is useful for converting a bitset to a string for use in other calculations.


```c
void NEBitSetCalculateFromBinary(struct NEBitSet *bs, const char *fromBinaryString);
```
The `NEBitSetCalculateFromBinary` function is the expected way to set a binary string as the set bits on a `NEBitSet` instance.


```c
void NEBitSetCalculateFromNumber(struct NEBitSet *bs, long fromNumber);
```
The `NEBitSetCalculateFromNumber` function is the expected way to set a decimal number as the set bits on a `NEBitSet` instance.
