#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "record.h"

const char *firstNames[] = {
    "John", "Paul", "Michael", "Alexander", "Daniel",
    "Andrew", "Peter", "Thomas", "Samuel", "Max"
};
const int FIRST_NAMES_COUNT = sizeof(firstNames) / sizeof(firstNames[0]);

const char *lastNames[] = {
    "Smith", "Johnson", "Brown", "Williams", "Jones",
    "Davis", "Miller", "Wilson", "Taylor", "Anderson"
};
static const int LAST_NAMES_COUNT = sizeof(lastNames) / sizeof(lastNames[0]);

char *randString(char *str, size_t size) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < size - 1; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[size - 1] = '\0';
    return str;
}

void generateData(Record *arr, int n) {
    for (int i = 0; i < n; i++) {
        char buffer[MAX_STR];
        const char *fn = firstNames[rand() % FIRST_NAMES_COUNT];
        const char *ln = lastNames[rand() % LAST_NAMES_COUNT];
        snprintf(buffer, sizeof(buffer), "%s %s", fn, ln);
        strncpy(arr[i].author, buffer, MAX_STR - 1);
        arr[i].author[MAX_STR - 1] = '\0';

        
        randString(arr[i].title, 12);
        randString(arr[i].publisher, 8);

        arr[i].year  = 1950 + rand() % 90;
        arr[i].pages = 50 + rand() % 950;
    }
}