#ifndef POLY_H
#define POLY_H

typedef struct Node {
    int coeff;
    int power;
    struct Node* next;
} Node;

void printPoly(Node* poly);
int findMinPower(Node* poly);

Node* polynomial(Node* L1, Node* L2);
void insertBeforeN(Node** poly, int N, int coeff, int power);
Node* inputPoly(int* size);

#endif
