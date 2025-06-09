#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "record.h"
#include "bst.h"
#include "rbtree.h"

int linearSearch(Record *arr, int size, const char *key);

void generateData(Record *arr, int n);

#define MAX_OPTION 3

void addToArray(Record **arr, int *size, const Record *newRecord) {
    (*size)++;
    *arr = (Record*)realloc(*arr, (*size) * sizeof(Record));
    if (!(*arr)) {
        printf("Error: could not expand the array.\n");
        exit(1);
    }
    (*arr)[(*size)-1] = *newRecord;
}

void inputRecord(Record *rec) {
    printf("Enter the 'author' field (for example 'John Smith'): ");
    getchar();
    if (!fgets(rec->author, MAX_STR, stdin)) {
        printf("Input error.\n");
        exit(1);
    }
    size_t len = strlen(rec->author);
    if (len > 0 && rec->author[len - 1] == '\n') {
        rec->author[len - 1] = '\0';
    }

    printf("Enter the 'publisher' field: ");
    if (!fgets(rec->publisher, MAX_STR, stdin)) {
        printf("Input error.\n");
        exit(1);
    }
    len = strlen(rec->publisher);
    if (len > 0 && rec->publisher[len - 1] == '\n') {
        rec->publisher[len - 1] = '\0';
    }

    strcpy(rec->title, "fsughduvfji");
    rec->year  = 2023;
    rec->pages = 100;
}

void printAllRecords(const Record *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("Record %4d | %20s | %11s | %7s | %d | %d\n",
               i, arr[i].author, arr[i].title, arr[i].publisher, arr[i].year, arr[i].pages);
    }
}

double measureTime(void (*func)(void), void (*before)(void), void (*after)(void))
{
    if (before) before();

    struct timeval startVal, endVal;
    gettimeofday(&startVal, NULL);

    func();

    gettimeofday(&endVal, NULL);
    if (after) after();

    double startSec  = (double)startVal.tv_sec  + (double)startVal.tv_usec  / 1000000.0;
    double endSec    = (double)endVal.tv_sec    + (double)endVal.tv_usec    / 1000000.0;
    return endSec - startSec;
}

int main() {
    srand((unsigned)time(NULL));

    int n = 0;
    printf("Enter the number of elements to generate: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid value.\n");
        return 0;
    }

    Record *arr = (Record*)malloc(n * sizeof(Record));
    if (!arr) {
        printf("Error: memory allocation failed.\n");
        return 1;
    }

    generateData(arr, n);
    printf("Generated %d records.\n\n", n);

    int viewInitialData = 0;
    printf("Do you want to display the generated data?\n");
    printf(" 1 - Yes\n 0 - No\n");
    printf("Enter your choice: ");
    scanf("%d", &viewInitialData);
    if (viewInitialData == 1) {
        printAllRecords(arr, n);
    }

    BSTNode *bstRoot = NULL;
    for (int i = 0; i < n; i++) {
        bstRoot = bstInsert(bstRoot, arr[i]);
    }

    RBNode  *rbRoot = NULL;
    for (int i = 0; i < n; i++) {
        rbInsert(&rbRoot, arr[i]);
    }

    int addChoice = 0;
    printf("\nDo you want to add a new record?\n");
    printf(" 1 - Yes \n 0 - Skip adding\n");
    printf("Enter your choice: ");
    scanf("%d", &addChoice);

    if (addChoice >= 1 && addChoice <= MAX_OPTION) {
        Record newRec;
        printf("\n--- Adding a new record ---\n");
        inputRecord(&newRec);

        switch (addChoice) {
            case 1:
                addToArray(&arr, &n, &newRec);
                bstRoot = bstInsert(bstRoot, newRec);
                rbInsert(&rbRoot, newRec);
                printf("\nRecord added successfully!\n");
                break;
        }
    } else {
        printf("\nSkipping addition or invalid input.\n\n");
    }

    if (addChoice == 1) {
        viewInitialData = 0;
        printf("Do you want to display the updated data?\n");
        printf(" 1 - Yes\n 0 - No\n");
        printf("Enter your choice: ");
        scanf("%d", &viewInitialData);
        if (viewInitialData == 1) {
            printAllRecords(arr, n);
        }
    }
    

    int searchChoice = 0;
    printf("\nWhich structure would you like to search?\n");
    printf(" 1 - Linear search\n 2 - BST\n 3 - R-B tree\n");
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);
    if (searchChoice != 1 && searchChoice != 2 && searchChoice != 3) {
        printf("Invalid choice. Search not performed.\n");
        return 0;
    }

    char searchKey[MAX_STR];
    printf("Enter the author's name to search (for example 'John Smith'): ");
    getchar();
    if (!fgets(searchKey, sizeof(searchKey), stdin)) {
        printf("Input error.\n");
        free(arr);
        return 1;
    }
    size_t len = strlen(searchKey);
    if (len > 0 && searchKey[len - 1] == '\n') {
        searchKey[len - 1] = '\0';
    }

    double elapsed = 0.0;

    if (searchChoice == 1) {
        int foundIndex = -1;
        void linearSearchAction(void) {
            foundIndex = linearSearch(arr, n, searchKey);
        }
        elapsed = measureTime(linearSearchAction, NULL, NULL);

        if (foundIndex >= 0) {
            printf("[Linear Search] Found index: %d\n", foundIndex);
        } else {
            printf("[Linear Search] Not found.\n");
        }
        printf("Elapsed time: %.6f s\n", elapsed);

    } else if (searchChoice == 2) {
        BSTNode *bstResult = NULL;
        void bstSearchAction(void) {
            bstResult = bstSearch(bstRoot, searchKey);
        }
        elapsed = measureTime(bstSearchAction, NULL, NULL);

        if (bstResult) {
            printf("[BST] Found: %s\n", bstResult->data.author);
        } else {
            printf("[BST] Not found.\n");
        }
        printf("BST search time: %.6f s\n", elapsed);

    } else if (searchChoice == 3) {
        RBNode *rbResult = NULL;
        void rbSearchAction(void) {
            rbResult = rbSearch(rbRoot, searchKey);
        }
        elapsed = measureTime(rbSearchAction, NULL, NULL);

        if (rbResult) {
            printf("[R-B Tree] Found: %s\n", rbResult->data.author);
        } else {
            printf("[R-B Tree] Not found.\n");
        }
        printf("R-B Tree search time: %.6f s\n", elapsed);

    } else {
        printf("Invalid choice. Search not performed.\n");
    }

    free(arr);
    return 0;
}