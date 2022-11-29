#include <NECollections/NEList.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NENode *NECreateNode(void) {
  NENode *node = (NENode *)calloc(1, sizeof(NENode));
  if (node != NULL) {
    node->NE_LISTS_NEXT_PARAM = NULL;
    node->NE_LISTS_PREV_PARAM = NULL;
  }
  return node;
}
NENode *NEDuplicateNode(NENode *node, NEULong size) {
  NENode *newNode = NULL;

  if (size > 0) {
    newNode = (NENode *)calloc(1, size);
    if (newNode != NULL) {
      memcpy(newNode, node, size);
      newNode->NE_LISTS_NEXT_PARAM = NULL;
      newNode->NE_LISTS_PREV_PARAM = NULL;
    }
  }
  else {
    newNode = (NENode *)calloc(1, sizeof(NENode));

    if (newNode != NULL) {
      newNode->NE_LISTS_NEXT_PARAM = node->NE_LISTS_NEXT_PARAM;
      newNode->NE_LISTS_PREV_PARAM = node->NE_LISTS_PREV_PARAM;
    }
  }

  return newNode;
}

void NEInitializeNode(NENode *node) {
  node->NE_LISTS_NEXT_PARAM = NULL;
  node->NE_LISTS_PREV_PARAM = NULL;
}

void NEDestroyNode(NENode *node) {
  if (node != NULL) {
    free(node);
  }
}

void NENodeAdd(NENode *node, NENode *newNode) {
  NENode *lastNode = NULL;

  if (node != NULL && newNode != NULL) {
    lastNode = node;
    while (lastNode->NE_LISTS_NEXT_PARAM != NULL) {
      lastNode = lastNode->NE_LISTS_NEXT_PARAM;
    }
    lastNode->NE_LISTS_NEXT_PARAM = newNode;
    newNode->NE_LISTS_PREV_PARAM = lastNode;
  }
}

NEList *NECreateList(void) {
  NEList *list = (NEList *)calloc(1, sizeof(NEList));
  if (list != NULL) {
    list->head = NULL;
    list->tail = NULL;

    list->addNode = NEListAdd;
    list->removeNode = NEListRemove;
    list->removeNodesFromList = NEListRemoveNodesFromList;
    list->size = NEListSize;
    list->iterate = NEListIterate;
  }
  return list;
}

void NEInitializeList(NEList *list) {
  if (!list) {
    return;
  }

  list->head = NULL;
  list->tail = NULL;
  list->addNode = NEListAdd;
  list->removeNode = NEListRemove;
  list->removeNodesFromList = NEListRemoveNodesFromList;
  list->size = NEListSize;
  list->iterate = NEListIterate;
}

void NEDestroyList(NEList *list) {
  NEDestroyListCustom(list, NULL);
}

void NEDestroyListCustom(NEList *list, NEDestroyListNode destroyNode) {
  if (list != NULL) {
    NENode *node = list->head;

    while (node != NULL) {
      NENode *next = node->NE_LISTS_NEXT_PARAM;
      if (destroyNode) {
        destroyNode(node);
      }
      NEDestroyNode(node);
      node = next;
    }

    free(list);
  }
}

void NEListAdd(NEList *list, NENode *node) {
  if (!list) {
    return;
  }

  if (!list->head) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->NE_LISTS_NEXT_PARAM = node;
    node->NE_LISTS_PREV_PARAM = list->tail;
    list->tail = node;
  }
}

void NEListRemove(NEList *list, NENode *node) {
  if (!node) {
    return;
  }

  if (list) {
    if (node == list->head) {
      list->head = node->NE_LISTS_NEXT_PARAM;
    }

    if (node == list->tail) {
      if (node->NE_LISTS_PREV_PARAM) {
        list->tail = node->NE_LISTS_PREV_PARAM;
      }
    }
  }

  if (node->NE_LISTS_PREV_PARAM) {
    node->NE_LISTS_PREV_PARAM->NE_LISTS_NEXT_PARAM = node->NE_LISTS_NEXT_PARAM;
  }

  if (node->NE_LISTS_NEXT_PARAM) {
    node->NE_LISTS_NEXT_PARAM->NE_LISTS_PREV_PARAM = node->NE_LISTS_PREV_PARAM;
  }
}

void NEListRemoveNodesFromList(NEList *list, NENodeFilter filter) {
  if (!list) {
    return;
  }

  NENode *node = list->head;

  while (node != NULL) {
    NENode *next = node->NE_LISTS_NEXT_PARAM;

    if (filter(node)) {
      NEListRemove(list, node);
      NEDestroyNode(node);
    }

    node = next;
  }
}

void NEListIterate(NEList *list, NENodeIterator iterator) {
  if (!list) {
    return;
  }

  NENode *node = list->head;

  while (node != NULL) {
    NENode *next = node->NE_LISTS_NEXT_PARAM;
    iterator(node);
    node = next;
  }
}

NEULong NEListSize(NEList *list) {
  NEULong size = 0;
  NENode *node = list->head;

  while (node != NULL) {
    size++;
    node = node->NE_LISTS_NEXT_PARAM;
  }

  return size;
}

NENode *NEListGetNodeAtIndex(NEList *list, NEULong index) {
  NENode *node = list->head;

  while (node != NULL && index > 0) {
    node = node->NE_LISTS_NEXT_PARAM;
    index--;
  }

  return node;
}

NEList *NEListFilterNodes(NEList *list, NEULong nodeSize, NENodeFilter filter) {
  NEList *newList = NECreateList();

  NENode *node = list->head;

  while (node != NULL) {
    if (filter(node)) {
      NEListAdd(newList, NEDuplicateNode(node, nodeSize));
    }

    node = node->NE_LISTS_NEXT_PARAM;
  }

  return newList;
}

void NEPrintList(NEList *list) {
  NEPrintListCustom(list, NULL);
}

void NEPrintListCustom(NEList *list, NENodePrinter printer) {
  NEStrPtr string = (NEStrPtr)NEListToString(list, printer);
  printf("%s\n", string);
  free(string);
}

NEUStrPtr NEListToString(NEList *list, NENodePrinter printer) {
  NEStrPtr string = NULL;
  NEULong size = 0;

  NENode *node = list->head;

  while (node != NULL) {
    size += 16;
    node = node->NE_LISTS_NEXT_PARAM;
  }

  size += 3;

  string = (NEStrPtr)calloc(size, sizeof(unsigned char));
  strcat(string, "[");

  node = list->head;

  while (node != NULL) {
    char buffer[256] = "";
    sprintf(buffer, "%p", node);
    if (printer) {
      NEUStrPtr printedNode = printer(node, (NEUStrPtr)buffer);
      void *newString = realloc(string, size + strlen((NEStrPtr)printedNode));
      if (newString) {
        string = newString;
        strcat(string, (NEStrPtr)printedNode);
        size += strlen((NEStrPtr)printedNode);
      }
      free(printedNode);
    }
    else {
      strcat(string, buffer);
    }

    if (node->NE_LISTS_NEXT_PARAM) {
      strcat(string, ", ");
    }
    node = node->NE_LISTS_NEXT_PARAM;
  }

  strcat(string, "]");

  return (NEUStrPtr)string;
}
