#ifndef NE_LISTS_H
#define NE_LISTS_H

#define NE_LISTS_NEXT_PARAM next
#define NE_LISTS_PREV_PARAM prev

#include "types.h"

/****************************************************************************
 Structure definitions and typedefs
 ****************************************************************************/

typedef struct NENode {
  struct NENode *NE_LISTS_NEXT_PARAM;
  struct NENode *NE_LISTS_PREV_PARAM;
} NENode;

typedef void (*NENodeIterator)(NENode *node);
typedef NEBool (*NENodeComparator)(NENode *left, NENode *right);
typedef NEBool (*NENodeFilter)(NENode *node);
typedef NEUStrPtr (*NENodePrinter)(NENode *node, const NEUStrPtr defaultContents);

typedef struct NEList {
  NENode *head;
  NENode *tail;

  void (*addNode)(struct NEList *list, NENode *node);
  void (*removeNode)(struct NEList *list, NENode *node);
  void (*removeNodesFromList)(struct NEList *list, NENodeFilter filter);

  NEULong (*size)(struct NEList *list);
  void (*iterate)(struct NEList *list, NENodeIterator iterator);
} NEList;

/****************************************************************************
 Function prototypes
 ****************************************************************************/

typedef void (*NEDestroyListNode)(NENode *node);

NENode *NECreateNode(void);
NENode *NEDuplicateNode(NENode *node, NEULong size);
void NEInitializeNode(NENode *node);
void NEDestroyNode(NENode *node);
void NENodeAdd(NENode *node, NENode *newNode);

NEList *NECreateList(void);
void NEInitializeList(NEList *list);
void NEDestroyList(NEList *list);
void NEDestroyListCustom(NEList *list, NEDestroyListNode destroyNode);

void NEListAdd(NEList *list, NENode *node);
void NEListRemove(NEList *list, NENode *node);
void NEListRemoveNodesFromList(NEList *list, NENodeFilter filter);
void NEListIterate(NEList *list, NENodeIterator iterator);

NEULong NEListSize(NEList *list);
NENode *NEListGetNodeAtIndex(NEList *list, NEULong index);
NEList *NEListFilterNodes(NEList *list, NEULong nodeSize, NENodeFilter filter);

void NEPrintList(NEList *list);
void NEPrintListCustom(NEList *list, NENodePrinter printer);
NEUStrPtr NEListToString(NEList *list, NENodePrinter printer);

/****************************************************************************
 MACROS
 ****************************************************************************/

#define NEFirstNode(type, node, result) ({ \
  for (NENode *cur = (NENode*)node; cur; cur = cur->NE_LISTS_PREV_PARAM) \
    result = (type)cur; \
})

#define NELastNode(type, node, result) ({ \
  for (NENode *cur = (NENode*)node; cur; cur = cur->NE_LISTS_NEXT_PARAM) \
    result = (type)cur; \
})

#define NEForEachNodeDo(type, list, node) \
  for (node = (type)list; node; node = (type)(((NENode *)node)->NE_LISTS_NEXT_PARAM))

#define NEIterateOnNodes(type, list, iterator) ({ \
  NENode *t = 0L; \
  NEForEachNodeDo(type,list,t) { \
    iterator(t); \
  } \
})

#define NEFindNode(type, list, node, target, comparator) ({ \
  type t = 0L; \
  node = 0L; \
  NEForEachNodeDo(type,list,t) { \
    if (comparator((type)t, (type)target)) { node = (type)t; break;} \
  } \
})

#define NEAddNode(type, list, newNode) ({ \
  NENode *temp = (NENode*)list; \
  NENode *next = NULL; \
  while (temp->NE_LISTS_NEXT_PARAM) temp = temp->NE_LISTS_NEXT_PARAM; \
  temp->NE_LISTS_NEXT_PARAM = calloc(1, sizeof(type)); \
  if (temp->NE_LISTS_NEXT_PARAM) { \
    memcpy(temp->NE_LISTS_NEXT_PARAM, newNode, sizeof(type)); \
    temp->NE_LISTS_NEXT_PARAM->NE_LISTS_PREV_PARAM = temp; \
    temp->NE_LISTS_NEXT_PARAM->NE_LISTS_NEXT_PARAM = NULL; \
  } \
})

#define NERemoveNode(type, list, node) ({ \
  type temp = list; \
  NEForEachNodeDo(type, list, temp) { \
    NENode *n = (NENode*)temp; \
    if (((NENode*)n) == ((NENode*)node)) { \
      if (n->NE_LISTS_PREV_PARAM) { \
        n->NE_LISTS_PREV_PARAM->NE_LISTS_NEXT_PARAM = n->NE_LISTS_NEXT_PARAM; \
      } \
      if (n->NE_LISTS_NEXT_PARAM) { \
        n->NE_LISTS_NEXT_PARAM->NE_LISTS_PREV_PARAM = n->NE_LISTS_PREV_PARAM; \
      } \
    } \
  } \
})

#endif
