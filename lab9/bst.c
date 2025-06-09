#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

static BSTNode* createBSTNode(Record data) {
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode* bstInsert(BSTNode* root, Record data) {
    if (root == NULL) {
        return createBSTNode(data);
    }
    int cmp = strcmp(data.author, root->data.author);
    if (cmp < 0) {
        root->left = bstInsert(root->left, data);
    } else {
        root->right = bstInsert(root->right, data);
    }
    return root;
}

BSTNode* bstSearch(BSTNode* root, const char *key) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strcmp(key, root->data.author);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return bstSearch(root->left, key);
    } else {
        return bstSearch(root->right, key);
    }
}