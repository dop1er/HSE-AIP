#ifndef LIST_H
#define LIST_H

typedef struct WordNode {
    char* word;
    struct WordNode* prev;
    struct WordNode* next;
} WordNode;

WordNode* createListFromInput();
void printList(WordNode* head);
void insertBeforeNList(WordNode** head, int N, const char* newWord);
void freeList(WordNode* head);

#endif
