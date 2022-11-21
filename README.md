# Collections in C (WIP)
## Overview
I have often repeated code with every new project in C due to the fact that things like collections (maps, lists, etc...) are not well provided by various systems. So as a test with GitHub CoPilot, I have decided to try to whip up a basic hash map, list and keyvalue vector (coming) using the new AI copilot and see how it goes.

## Examples
For both lists and maps (unfinished), there is an associated xxxfun file that gets generated with the make.sh file.

## Types
In the current incarnation there are 3 different entity types introduced by this repo. Those are:
 1. Linked Lists
 1. Hashed Maps
 1. Collections

### Linked List
Lists in this library are known as `NEList` and contain `NENode` entries. Extending NENode is as simple as creating a new struct with a non pointer `NENode` struct as its first element. This allows the compiler to allow casts of your custom node to NENode for library usage.

Example:
```c
struct Person {
  /* First entry must be a non-pointer NENode struct */
  NENode node;
  
  /* Anything else is up to you */
  char name[100];
  unsigned char age;
  char gender[32];
};

NEList *people = NECreateList();
struct Person *p = calloc(1, sizeof(struct Person));
if (people && p) {
  people->addNode(people, (NENode*)p);
}
```

### Collections
The creation of individual nodes to store basic data like integers, floats, strings and booleans as well as something like a list of pointers, can be tedious. So `NECollection` was born. It makes this simple for the most part.

```c
NECollection *people = NECollectionCreate();
if (people) {
  people->addString(people, "Brielle");
  people->addString(people, "Sandra");
  people->addString(people, "Lacy");
}
```

While not strictly advised, mixing types is also allowed

```c
NECollection *mixed = NECollectionCreate();
if (mixed) {
  mixed->addString(mixed, "String");
  mixed->addByte(mixed, '\x1b');
  mixed->addInteger(mixed, 2345);
  mixed->addDecimal(mixed, 234.234f);
  mixed->addPointer(mixed, mixed);

  // The count of items also works
  mixed->count(mixed); // -> 5
  
  // Items can be referenced by their index
  mixed->at(mixed, 3); // -> (struct KeyValue *) { NE_DECIMAL, 234.234f }
  
  // Items can be sorted with a customer NECollectionSorter function
  mixed->sort(mixed, sorter);
  
  // The collection can be cleared as well, reducing its number to 0
  mixed->clear(mixed);
}
```

  
