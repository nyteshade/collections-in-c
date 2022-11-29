#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <NECollections/NEBitSet.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

NEBitSet *NEBitSetCreate(int nbits) {
	NEBitSet *bs = malloc(sizeof(NEBitSet));

	bs->nbits = nbits;
	bs->bits = calloc(BITNSLOTS(nbits), sizeof(unsigned char));

	bs->set = NEBitSetSet;
	bs->clear = NEBitSetClear;
	bs->clearAll = NEBitSetClearAll;
	bs->invert = NEBitSetInvert;
	bs->test = NEBitSetTest;
	bs->print = NEBitSetPrint;
	bs->printWithSpacing = NEBitSetPrintWithSpacing;
	bs->destroy = NEBitSetDestroy;
	bs->convert = NEBitSetConvert;
	bs->calculateFromBinary = NEBitSetCalculateFromBinary;
	bs->calculateFromNumber = NEBitSetCalculateFromNumber;

	return bs;
}

void NEBitSetDestroy(NEBitSet *bs) {
	free(bs->bits);
	free(bs);
}

void NEBitSetSet(struct NEBitSet *bs, int bit) {
	BITSET(bs->bits, bit);
}

void NEBitSetClear(struct NEBitSet *bs, int bit) {
	BITCLEAR(bs->bits, bit);
}

void NEBitSetClearAll(struct NEBitSet *bs) {
	memset(bs->bits, 0, BITNSLOTS(bs->nbits));
}

void NEBitSetInvert(struct NEBitSet *bs) {
	int i;
	for (i = 0; i < bs->nbits; i++) {
		bs->bits[i] = ~bs->bits[i];
	}
}

int NEBitSetTest(struct NEBitSet *bs, int bit) {
	return BITTEST(bs->bits, bit);
}

void NEBitSetCalculateFromBinary(struct NEBitSet *bs, const char *fromBinaryString) {
	int i;
	for (i = 0; i < bs->nbits; i++) {
		if (fromBinaryString[i] == '1') {
			BITSET(bs->bits, i);
		} else {
			BITCLEAR(bs->bits, i);
		}
	}
}

void NEBitSetCalculateFromNumber(struct NEBitSet *bs, long fromNumber) {
	int i;
	for (i = 0; i < bs->nbits; i++) {
		if (fromNumber & (1 << i)) {
			BITSET(bs->bits, i);
		} else {
			BITCLEAR(bs->bits, i);
		}
	}
}

unsigned long NEBitSetToNumber(struct NEBitSet *bs) {
	unsigned long number = 0;
	int i;
	for (i = 0; i < bs->nbits; i++) {
		if (BITTEST(bs->bits, i)) {
			number |= (1 << i);
		}
	}

	return number;
}

NEBitConversion NEBitSetConvert(struct NEBitSet *bs) {
	NEBitConversion bc;
	unsigned int i;

	memset(&bc, 0, sizeof(NEBitConversion));

	if (!bs) {
		return bc;
	}

	for (i = 0; i < bs->nbits; ++i) {
		if (BITTEST(bs->bits, i)) {
			bc.integer |= (1 << i);
			bc.string[bs->nbits - i - 1] = '1';
		} else {
			bc.string[bs->nbits - i - 1] = '0';
		}
	}

	return bc;
}

void NEBitSetPrint(struct NEBitSet *bs) {
	NEBitSetPrintWithSpacing(bs, 0, 0);
}

void NEBitSetPrintWithSpacing(struct NEBitSet *bs, char everyFour, char everyEight) {
	NEBitConversion bc = NEBitSetConvert(bs);
	unsigned long len = strlen((char *)&bc.string[0]);
	unsigned long i;
	unsigned long spacer = len % 8;

	for (i = 0; i < spacer; i++) {
		if (i % 4 == 0) {
			printf(" ");
		}
		printf("0");
	}

	for (i = 0; i < len; i++, spacer++) {
		if (everyFour && i > 0 && spacer % 4 == 0) printf(" ");
		if (everyEight && i > 0 && spacer % 8 == 0) printf(" ");
		printf("%c", bc.string[i]);
	}

	printf("\n");
}
