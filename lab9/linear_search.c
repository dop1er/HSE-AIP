#include <string.h>
#include "record.h"

int linearSearch(Record *arr, int size, const char *key) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].author, key) == 0) {
            return i;
        }
    }
    return -1;
}