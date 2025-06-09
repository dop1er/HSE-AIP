#ifndef RECORD_H
#define RECORD_H

#define MAX_STR 100

typedef struct {
    char author[MAX_STR];
    char title[MAX_STR];
    char publisher[MAX_STR];
    int  year;
    int  pages;
} Record;

#endif