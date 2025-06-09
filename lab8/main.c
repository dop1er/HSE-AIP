#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "list.h"

void polynomialTask() {
    int sizeL1, sizeL2;
    printf("\n");

    printf("(L1) ");
    Node* L1 = inputPoly(&sizeL1);
    printf("(L2) ");
    Node* L2 = inputPoly(&sizeL2);

    printf("\nL1: ");
    printPoly(L1);
    printf("L2: ");
    printPoly(L2);

    Node* result = polynomial(L1, L2);
    printf("\nResult (polynomial): ");
    printPoly(result);


    free(L1);
    free(L2);
    free(result);
}

void listTask() {
    printf("\n");
    WordNode* list = createListFromInput();

    printf("Original list:\n");
    printList(list);

    int N;
    char newWord[256];
    printf("\nEnter position N to insert new word before: ");
    scanf("%d", &N);
    printf("Enter new word to insert: ");
    scanf("%s", newWord);

    insertBeforeNList(&list, N, newWord);

    printf("\nModified list:\n");
    printList(list);

    freeList(list);
}

int main() {
    int choice;

    while (1) {
        printf("\nChoose task to run:\n");
        printf("1 - Polynomial task\n");
        printf("2 - String task\n");
        printf("0 - Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            polynomialTask();
        } else if (choice == 2) {
            listTask();
        } else if (choice == 0) {
            break;
        } else {
            printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
