#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"

static RBNode* createRBNode(Record data) {
    RBNode *node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

static void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

static void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

static void rbInsertFixUp(RBNode **root, RBNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void rbInsert(RBNode **root, Record data) {
    RBNode *newNode = createRBNode(data);
    RBNode *parent = NULL;
    RBNode *current = *root;

    while (current != NULL) {
        parent = current;
        int cmp = strcmp(data.author, current->data.author);
        if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    newNode->parent = parent;

    if (parent == NULL) {
        *root = newNode;
    } else if (strcmp(data.author, parent->data.author) < 0) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    rbInsertFixUp(root, newNode);
}

RBNode* rbSearch(RBNode *root, const char *key) {
    while (root != NULL) {
        int cmp = strcmp(key, root->data.author);
        if (cmp == 0) {
            return root;
        } else if (cmp < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}