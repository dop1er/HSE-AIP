#include "sort.h"

void shaker_sort(Record* arr, size_t n, SortOrder order) {
    if (n < 2) return;
    int (*cmp)(Record*, Record*) =
        (order == ASCENDING) ? compare_asc : compare_desc;

    size_t left = 0;
    size_t right = n - 1;

    while (left < right) {
        for (size_t i = left; i < right; i++) {
            if (cmp(&arr[i], &arr[i + 1]) > 0) {
                Record tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
        }
        if (right == 0) break;
        right--;

        for (size_t i = right; i > left; i--) {
            if (cmp(&arr[i - 1], &arr[i]) > 0) {
                Record tmp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = tmp;
            }
        }
        left++;
    }
}
