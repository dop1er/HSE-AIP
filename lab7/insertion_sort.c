#include "sort.h"

void insertion_sort(Record* arr, size_t n, SortOrder order) {
    int (*cmp)(const Record*, const Record*) =
        (order == ASCENDING) ? compare_asc : compare_desc;

    for (size_t i = 1; i < n; i++) {
        Record key = arr[i];
        int j = i - 1;
        while (j >= 0 && cmp(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
