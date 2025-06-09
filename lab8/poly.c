#include <stdio.h>
#include <stdlib.h>
#include "poly.h"


Node* createPolyNode(int coeff, int power) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

void printPoly(Node* poly) {
    Node* current = poly;
    int first = 1;

    while (current) {
        if (current->coeff > 0 && !first) {
            printf("+");
        }
        if (current->power == 0)
            printf("%d", current->coeff);
        else if (current->power == 1)
            printf("%dx", current->coeff);
        else
            printf("%dx^%d", current->coeff, current->power);

        first = 0;
        current = current->next;
    }
    printf("\n");
}

int findMinPower(Node* poly) {
    if (!poly) return -1;
    int minPower = poly->power;
    Node* current = poly->next;
    while (current) {
        if (current->power < minPower) minPower = current->power;
        current = current->next;
    }
    return minPower;
}

Node* polynomial(Node* L1, Node* L2) {
    int minPowerL1 = findMinPower(L1);
    Node* result = NULL;
    Node* currentL2 = L2;

    while (currentL2) {
        if (currentL2->power <= minPowerL1) {
            Node* newNode = createPolyNode(currentL2->coeff, currentL2->power);
            if (!result) {
                result = newNode;
            } else {
                Node* temp = result;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        currentL2 = currentL2->next;
    }

    return result;
}

void insertBeforeN(Node** poly, int N, int coeff, int power) {
    if (N <= 0) {
        printf("Invalid position\n");
        return;
    }

    Node* newNode = createPolyNode(coeff, power);

    if (*poly == NULL || N == 1) {
        newNode->next = *poly;
        *poly = newNode;
        return;
    }

    Node* current = *poly;
    int pos = 1;
    while (current && pos < N - 1) {
        current = current->next;
        pos++;
    }

    if (current == NULL) {
        printf("Position exceeds the size of the list.\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

Node* inputPoly(int* size) {
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", size);

    Node* poly = NULL;
    printf("Enter the coefficient and power for each term separated by space:\n");

    for (int i = 0; i < *size; i++) {
        int coeff, power;
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);

        Node* newNode = createPolyNode(coeff, power);
        if (!poly) {
            poly = newNode;
        } else {
            Node* current = poly;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    return poly;
}
