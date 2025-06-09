#include "sort.h"

int compare_records(const Record* a, const Record* b) {
    int res = strcmp(a->author, b->author);
    if (res != 0) return res;

    res = strcmp(a->title, b->title);
    if (res != 0) return res;

    res = strcmp(a->publisher, b->publisher);
    if (res != 0) return res;

    if (a->year != b->year) return (a->year < b->year) ? -1 : 1;
    if (a->pages != b->pages) return (a->pages < b->pages) ? -1 : 1;

    return 0;
}

int compare_asc(const Record* a, const Record* b) {
    return compare_records(a, b);
}

int compare_desc(const Record* a, const Record* b) {
    return -compare_records(a, b);
}
