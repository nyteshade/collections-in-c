#ifndef NE_BITSET_H
#define NE_BITSET_H

/* Prototype declarations */
typedef struct NEBitConversion NEBitConversion;

/* Struct definitions */
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

typedef struct NEBitConversion {
	unsigned char string[1024];
	unsigned long integer;
} NEBitConversion;

/* Function prototypes */
NEBitSet *NEBitSetCreate(int nbits);
void NEBitSetDestroy(NEBitSet *bs);

void NEBitSetSet(struct NEBitSet *bs, int bit);
void NEBitSetClear(struct NEBitSet *bs, int bit);
void NEBitSetClearAll(struct NEBitSet *bs);
void NEBitSetInvert(struct NEBitSet *bs);
int NEBitSetTest(struct NEBitSet *bs, int bit);
void NEBitSetPrint(struct NEBitSet *bs);
void NEBitSetPrintWithSpacing(struct NEBitSet *bs, char everyFour, char everyEight);
unsigned long NEBitSetToDecimal(struct NEBitSet *bs);
NEBitConversion NEBitSetConvert(struct NEBitSet *bs);
void NEBitSetCalculateFromBinary(struct NEBitSet *bs, const char *fromBinaryString);
void NEBitSetCalculateFromNumber(struct NEBitSet *bs, long fromNumber);

#endif