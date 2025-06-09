#include "sort.h"

int partition(Record* arr, int left, int right, int (*cmp)(const Record*, const Record*)) {
    Record pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (cmp(&arr[i], &pivot) < 0) i++;
        while (cmp(&arr[j], &pivot) > 0) j--;
        if (i <= j) {
            Record tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    return i;
}

void quick_sort(Record* arr, int left, int right, SortOrder order) {
    if (left >= right) return;
    int (*cmp)(const Record*, const Record*) =
        (order == ASCENDING) ? compare_asc : compare_desc;

    int index = partition(arr, left, right, cmp);
    if (left < index - 1) {
        quick_sort(arr, left, index - 1, order);
    }
    if (index < right) {
        quick_sort(arr, index, right, order);
    }
}
