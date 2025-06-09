#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

#define SAMPLE_SIZE 15

static const Record sample_data[SAMPLE_SIZE] = {
    {"Ivanov Ivan Ivanovich",       "War and Peace",             "AST",        1869, 1225},
    {"Petrov Petr Petrovich",       "Crime and Punishment",      "Azbuka",     1866,  671},
    {"Sidorov Sergei Sergeevich",   "The Master and Margarita",  "Eksmo",      1967,  384},
    {"Kuznetsova Anna Vladimirovna", "1984",                      "AST",        1949,  328},
    {"Fedorov Dmitrii Sergeevich",  "Ulysses",                   "Azbuka",     1922,  730},
    {"Tolkien J. R. R.",            "The Hobbit",                "Mir",        1937,  310},
    {"Orwell George",               "Animal Farm",               "ACT",        1945,  112},
    {"Hemingway Ernest",            "The Old Man and the Sea",   "Prosveshchenie",1952,127},
    {"Dostoevsky Fyodor Mikhailovich","The Idiot",                "Petrarka",   1869,  640},
    {"Tolstoy Leo Nikolaevich",     "Anna Karenina",             "AST",        1878,  864},
    {"Bulgakov Mikhail Afanasyevich","Heart of a Dog",            "Eksmo",      1925,  192},
    {"Shackle Robert",              "Planet for Pioneers",       "Eksmo",      1966,  224},
    {"Bradbury Ray",                "Fahrenheit 451",            "ACT",        1953,  194},
    {"King Stephen",                "The Green Mile",            "ACT",        1996,  528},
    {"Markov Alexander Sergeevich", "Mathematics: A Textbook",   "Nauka",      2010,  512}
};


Record* clone_array(Record* src, size_t n) {
    Record* dst = malloc(n * sizeof(Record));
    if (!dst) {
        perror("malloc failed while cloning array");
        return NULL;
    }
    memcpy(dst, src, n * sizeof(Record));
    return dst;
}


double measure_sort_time(void (*sort_func)(Record*, size_t, SortOrder),
                                Record* arr, size_t n, SortOrder order) {
    Record* temp = clone_array(arr, n);
    if (!temp) return -1.0;

    clock_t start = clock();
    sort_func(temp, n, order);
    clock_t end = clock();

    free(temp);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void print_records(const Record* arr, size_t n) {
    printf("\nSorted list (%zu records):\n", n);
    printf("--------------------------------------------------------------------------------------------\n");
    printf("| N  |         Author           |          Title         |    Publisher    | Year | Pages |\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < n; i++) {
        printf("| %-2zu | %-24s | %-22s | %-15s | %-4d | %-5d |\n",
               i + 1,
               arr[i].author,
               arr[i].title,
               arr[i].publisher,
               arr[i].year,
               arr[i].pages);
    }
    printf("--------------------------------------------------------------------------------------------\n\n");
}

int main() {
    char surnames[SAMPLE_SIZE][MAX_STR];
    char names_arr[SAMPLE_SIZE][MAX_STR];
    char patr[SAMPLE_SIZE][MAX_STR];

    for (size_t i = 0; i < SAMPLE_SIZE; i++) {
        char temp[MAX_STR];
        strncpy(temp, sample_data[i].author, MAX_STR);
        temp[MAX_STR - 1] = '\0';
        char* token = strtok(temp, " ");
        if (token) {
            strncpy(surnames[i], token, MAX_STR);
            surnames[i][MAX_STR - 1] = '\0';
            token = strtok(NULL, " ");
        }
        if (token) {
            strncpy(names_arr[i], token, MAX_STR);
            names_arr[i][MAX_STR - 1] = '\0';
            token = strtok(NULL, " ");
        }
        if (token) {
            strncpy(patr[i], token, MAX_STR);
            patr[i][MAX_STR - 1] = '\0';
        }
    }

    size_t n = 0;
    printf("How many records to generate (n > 0)? ");
    if (scanf("%zu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid value for n. Exiting.\n");
        return EXIT_FAILURE;
    }

    Record* arr = malloc(n * sizeof(Record));

    srand(time(NULL)); //seed генерации

    for (size_t i = 0; i < n; i++) {
        size_t idx_title = (size_t)(rand() % SAMPLE_SIZE);
        arr[i].year      = sample_data[idx_title].year;
        arr[i].pages     = sample_data[idx_title].pages;
        strncpy(arr[i].title, sample_data[idx_title].title, MAX_STR);
        arr[i].title[MAX_STR - 1] = '\0';
        strncpy(arr[i].publisher, sample_data[idx_title].publisher, MAX_STR);
        arr[i].publisher[MAX_STR - 1] = '\0';

        size_t idx_s = (size_t)(rand() % SAMPLE_SIZE);
        size_t idx_n = (size_t)(rand() % SAMPLE_SIZE);
        size_t idx_p = (size_t)(rand() % SAMPLE_SIZE);

        strncpy(arr[i].author, surnames[idx_s], MAX_STR);
        arr[i].author[MAX_STR - 1] = '\0';

        size_t len = strnlen(arr[i].author, MAX_STR);
        if (len + 1 < MAX_STR) {
            arr[i].author[len] = ' ';
            arr[i].author[len + 1] = '\0';
            len++;
        }

        size_t avail = MAX_STR - len;
        strncat(arr[i].author, names_arr[idx_n], avail - 1);
        arr[i].author[MAX_STR - 1] = '\0';
        len = strnlen(arr[i].author, MAX_STR);

        if (len + 1 < MAX_STR) {
            arr[i].author[len] = ' ';
            arr[i].author[len + 1] = '\0';
            len++;
        }

        avail = MAX_STR - len;
        strncat(arr[i].author, patr[idx_p], avail - 1);
        arr[i].author[MAX_STR - 1] = '\0';
    }


    int choice_algo = 0;
    printf("\nChoose sorting algorithm (enter number):\n");
    printf("1. Insertion Sort\n");
    printf("2. Shaker Sort\n");
    printf("3. Quick Sort\n");
    printf("Your choice: ");
    if (scanf("%d", &choice_algo) != 1 || choice_algo < 1 || choice_algo > 3) {
        fprintf(stderr, "Invalid algorithm choice.\n");
        free(arr);
        return EXIT_FAILURE;
    }


    int choice_order = 0;
    printf("Choose sort order (1 - ascending, 2 - descending): ");
    if (scanf("%d", &choice_order) != 1 || (choice_order != 1 && choice_order != 2)) {
        fprintf(stderr, "Invalid order choice.\n");
        free(arr);
        return EXIT_FAILURE;
    }
    SortOrder order = (choice_order == 1) ? ASCENDING : DESCENDING;


    double elapsed = 0.0;
    switch (choice_algo) {
        case 1:
            elapsed = measure_sort_time(insertion_sort, arr, n, order);
            break;
        case 2:
            elapsed = measure_sort_time(shaker_sort, arr, n, order);
            break;
        case 3: {
            Record* temp = clone_array(arr, n);
            if (!temp) {
                free(arr);
                return EXIT_FAILURE;
            }
            clock_t start = clock();
            quick_sort(temp, 0, (int)n - 1, order);
            clock_t end = clock();
            elapsed = (double)(end - start) / CLOCKS_PER_SEC;
            free(temp);
            break;
        }
        default:
            fprintf(stderr, "Unexpected algorithm choice.\n");
            free(arr);
            return EXIT_FAILURE;
    }

    printf("\nSorting completed. Time taken: %.6f seconds.\n", elapsed);

    char print_choice;
    printf("Display sorted list on screen? (y/n): ");
    scanf(" %c", &print_choice);
    if (print_choice == 'y' || print_choice == 'Y') {
        switch (choice_algo) {
            case 1:
                insertion_sort(arr, n, order);
                break;
            case 2:
                shaker_sort(arr, n, order);
                break;
            case 3:
                quick_sort(arr, 0, (int)n - 1, order);
                break;
        }
        print_records(arr, n);
    }

    free(arr);
    return EXIT_SUCCESS;
}
