#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR 100

typedef struct {
    char author[MAX_STR];
    char title[MAX_STR];
    char publisher[MAX_STR];
    int  year;
    int  pages;
} Record;

typedef enum {
    ASCENDING,
    DESCENDING
} SortOrder;

int compare_records(const Record* a, const Record* b);

int compare_asc(const Record* a, const Record* b);
int compare_desc(const Record* a, const Record* b);

void insertion_sort(Record* arr, size_t n, SortOrder order);
void shaker_sort(Record* arr, size_t n, SortOrder order);
void quick_sort(Record* arr, int left, int right, SortOrder order);

#endif
