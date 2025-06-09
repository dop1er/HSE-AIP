#ifndef LIBRARY_H
#define LIBRARY_H

struct library {
    char author[100];
    char title[100];
    char publisher[100];
    int  year;
    int  pages;
};

#endif