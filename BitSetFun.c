#include <stdio.h>
#include "BitSet.h"

enum BitFlags {
	FL_DOOR_OPEN = 0,
  FR_DOOR_OPEN,
  LOVES_CATS,
  HATES_ONIONS
};

int main() {
	NEBitSet *b = NEBitSetCreate(32);

	b->set(b, FL_DOOR_OPEN);
	b->set(b, FR_DOOR_OPEN);
	b->set(b, HATES_ONIONS);
	b->printWithSpacing(b, 0, 1);

	b->invert(b);
	b->printWithSpacing(b, 0, 1);

	b->clearAll(b);
	b->printWithSpacing(b, 0, 1);


	NEBitSetDestroy(b);

	return 0;
}
