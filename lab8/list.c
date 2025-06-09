#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

WordNode* createNode(const char* word) {
    WordNode* node = (WordNode*)malloc(sizeof(WordNode));
    node->word = strdup(word);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

WordNode* createListFromInput() {
    WordNode* head = NULL;
    WordNode* tail = NULL;

    char buffer[256];
    int pos = 0;
    char c;

    printf("Enter sentence (lowercase letters, words separated by spaces, end with '.'): \n");

    while (1) {
        c = getchar();
        if (c == '.') break;
        if (islower(c)) {
            buffer[pos++] = c;
        } else if (c == ' ') {
            if (pos > 0) {
                buffer[pos] = '\0';
                WordNode* newNode = createNode(buffer);
                if (!head) {
                    head = tail = newNode;
                } else {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
                pos = 0;
            }
        }
    }

    if (pos > 0) {
        buffer[pos] = '\0';
        WordNode* newNode = createNode(buffer);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    while ((c = getchar()) != '\n' && c != EOF) {}

    return head;
}

void printList(WordNode* head) {
    WordNode* cur = head;
    while (cur) {
        printf("%s", cur->word);
        if (cur->next) printf(" ");
        cur = cur->next;
    }
    printf("\n");
}

void insertBeforeNList(WordNode** head, int N, const char* newWord) {
    if (N <= 0) {
        printf("Invalid position\n");
        return;
    }

    WordNode* newNode = createNode(newWord);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    WordNode* cur = *head;
    int pos = 1;

    while (cur && pos < N) {
        cur = cur->next;
        pos++;
    }

    if (cur == NULL) {
        WordNode* tail = *head;
        while (tail->next) tail = tail->next;
        tail->next = newNode;
        newNode->prev = tail;
    } else if (cur == *head) {
        newNode->next = cur;
        cur->prev = newNode;
        *head = newNode;
    } else {
        WordNode* prev = cur->prev;
        prev->next = newNode;
        newNode->prev = prev;
        newNode->next = cur;
        cur->prev = newNode;
    }
}

void freeList(WordNode* head) {
    WordNode* cur = head;
    while (cur) {
        WordNode* next = cur->next;
        free(cur->word);
        free(cur);
        cur = next;
    }
}
