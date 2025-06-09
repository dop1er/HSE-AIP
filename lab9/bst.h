#ifndef BST_H
#define BST_H

#include "record.h"

typedef struct BSTNode {
    Record data;
    struct BSTNode *left, *right;
} BSTNode;

BSTNode* bstInsert(BSTNode* root, Record data);

BSTNode* bstSearch(BSTNode* root, const char *key);

#endif