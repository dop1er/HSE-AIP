#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

TreeNode* createNode(int value, TreeNode* parent) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    
    return node;
}

TreeNode* buildTreeRecursive(int* numbers, int N, int L, int* index, int currentDepth, TreeNode* parent) {
    if (currentDepth > L || *index >= N) {
        return NULL;
    }
    
    TreeNode* node = createNode(numbers[*index], parent);
    if (node == NULL) {
        return NULL;
    }
    
    (*index)++;
    
    if (currentDepth < L) {
        node->left = buildTreeRecursive(numbers, N, L, index, currentDepth + 1, node);
        
        node->right = buildTreeRecursive(numbers, N, L, index, currentDepth + 1, node);
    }
    
    return node;
}

TreeNode* buildTree(int* numbers, int N, int L, int* index) {
    *index = 0;
    return buildTreeRecursive(numbers, N, L, index, 1, NULL);
}

void printTree(TreeNode* root, int depth) {
    if (root == NULL) {
        return;
    }
    
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    printf("Node: %d", root->value);
    if (root->parent != NULL) {
        printf(" (parent: %d)", root->parent->value);
    } else {
        printf(" (root)");
    }
    printf("\n");
    
    if (root->left != NULL || root->right != NULL) {
        if (root->left != NULL) {
            for (int i = 0; i < depth + 1; i++) {
                printf("  ");
            }
            printf("Left subtree:\n");
            printTree(root->left, depth + 2);
        }
        
        if (root->right != NULL) {
            for (int i = 0; i < depth + 1; i++) {
                printf("  ");
            }
            printf("Right subtree:\n");
            printTree(root->right, depth + 2);
        }
    }
}

void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}