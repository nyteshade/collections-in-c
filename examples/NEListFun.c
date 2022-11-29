#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <NECollections/NEList.h>

typedef struct NamedNode {
  NENode node;
  unsigned char name[64];
} NamedNode;

/*-----------------------------------------------------------------------------*/

unsigned char filterForYuki(NamedNode *node, NamedNode *target) {
  NamedNode *n = (NamedNode *)node;
  return strcmp((const NEStrPtr )&n->name[0], "Yuki") == 0;
}

NEUStrPtr namedNodePrinter(NENode *namedNode, const NEUStrPtr defaultContents) {
  NamedNode *n = (NamedNode *)namedNode;
  NEStrPtr string = (NEStrPtr)calloc(strlen((NEStrPtr )defaultContents) + strlen((NEStrPtr )n->name) + 3, sizeof(unsigned char));
  if (string) {
    sprintf(string, "%s (%s)", n->name, defaultContents);
    return (NEUStrPtr )string;
  }
  else {
    return defaultContents;
  }
}

NEBool findSandy(NENode *node) {
  NamedNode *n = (NamedNode *)node;
  return strcmp((const NEStrPtr)&n->name[0], "Sandy") == 0;
}

int main(int argc, NEStrPtr argv[]) {
  NEList *list2 = NECreateList();

  NamedNode a = { {0L, 0L}, "Brielle" };
  NamedNode b = { {0L, 0L}, "Sandy" };
  NamedNode c = { {0L, 0L}, "Yuki" };
  NamedNode d = { {0L, 0L}, "Katie" };
  NamedNode e = { {0L, 0L}, "Sasha" };
  NamedNode g = { {0L, 0L}, "Jura" };
  NamedNode *f = NULL;
  NamedNode *h = NULL;

  printf("\n------- Node Fun --------------\n\n");

  a.node.next = (NENode*)&b;
  b.node.next = (NENode*)&c;
  c.node.next = (NENode*)&d;
  d.node.next = (NENode*)&e;
  e.node.prev = (NENode*)&d;
  d.node.prev = (NENode*)&c;
  c.node.prev = (NENode*)&b;
  b.node.prev = (NENode*)&a;

  NELastNode(NamedNode*, &a, f);
  printf("The last node's name is: %s\n", f->name);

  NEFirstNode(NamedNode*, &e, f);
  printf("The first node's name is: %s\n", f->name);

  NEAddNode(NamedNode, &a, &g);
  printf("Added %s to the list of nodes\n", g.name);

  printf("\nNodes:\n");
  NEForEachNodeDo(NamedNode*, &a, f) {
    printf("  Name: %s (%p)\n", f->name, f);
  }

  // Fails on first item, probably on last item ; fix it
  NERemoveNode(NamedNode*, &a, &b);
  printf("\nRemoved Sandy node from the list of nodes\n");

  printf("\nNodes:\n");
  NEForEachNodeDo(NamedNode*, &a, f) {
    printf("  Name: %s (%p)\n", f->name, f);
  }

  printf("\nSearching for Yuki...");
  NEFindNode(NamedNode*, &a, f, h, filterForYuki);
  printf("%s\n", f != NULL ? "found" : "cannot find her");

  printf("\n------- List Fun --------------\n\n");

  list2->addNode(list2, NEDuplicateNode((NENode*)&a, sizeof(NamedNode)));
  list2->addNode(list2, NEDuplicateNode((NENode*)&b, sizeof(NamedNode)));
  list2->addNode(list2, NEDuplicateNode((NENode*)&c, sizeof(NamedNode)));
  list2->addNode(list2, NEDuplicateNode((NENode*)&d, sizeof(NamedNode)));
  list2->addNode(list2, NEDuplicateNode((NENode*)&e, sizeof(NamedNode)));
  list2->addNode(list2, NEDuplicateNode((NENode*)&g, sizeof(NamedNode)));

  list2->removeNodesFromList(list2, findSandy);

  NEPrintListCustom(list2, namedNodePrinter);
  NEDestroyList(list2);

  return 0;
}
