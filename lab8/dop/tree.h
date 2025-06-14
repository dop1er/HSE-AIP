#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

TreeNode* createNode(int value, TreeNode* parent);
TreeNode* buildTree(int* numbers, int N, int L, int* index);
void printTree(TreeNode* root, int depth);
void freeTree(TreeNode* root);

#endif