#ifndef RBTREE_H
#define RBTREE_H

#include "record.h"

typedef enum {
    RED,
    BLACK
} Color;

typedef struct RBNode {
    Record data;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

void rbInsert(RBNode **root, Record data);

RBNode* rbSearch(RBNode *root, const char *key);

#endif