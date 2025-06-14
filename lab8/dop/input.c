#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

int inputPositiveNumber(const char* prompt) {
    int number;
    do {
        printf("%s", prompt);
        if (scanf("%d", &number) != 1) {
            printf("Error: enter a valid number\n");
            while (getchar() != '\n');
            number = -1;
        } else if (number <= 0) {
            printf("Error: number must be positive\n");
        }
    } while (number <= 0);
    
    return number;
}

int* inputNumbers(int maxN, int* actualN) {
    char line[1000];
    int* numbers = (int*)malloc(maxN * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    
    printf("Enter numbers separated by spaces (press Enter to finish):\n");
    
    while (getchar() != '\n');
    
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("Error reading input\n");
        free(numbers);
        return NULL;
    }
    
    *actualN = 0;
    char* token = strtok(line, " \t\n");
    
    while (token != NULL && *actualN < maxN) {
        int num = atoi(token);
        if (num != 0 || strcmp(token, "0") == 0) {
            numbers[*actualN] = num;
            (*actualN)++;
        } else {
            printf("Warning: '%s' is not a valid number, skipping\n", token);
        }
        token = strtok(NULL, " \t\n");
    }
    
    if (*actualN == 0) {
        printf("Error: no valid numbers entered\n");
        free(numbers);
        return NULL;
    }
    
    if (*actualN > maxN) {
        printf("Warning: only first %d numbers will be used\n", maxN);
        *actualN = maxN;
    }
    
    return numbers;
}

void printNumbers(int* numbers, int N) {
    printf("Numbers entered: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", numbers[i]);
    }
    printf("(total: %d)\n", N);
}

int askYesNo(const char* prompt) {
    char answer[10];
    
    while (1) {
        printf("%s (y/N): ", prompt);
        
        if (fgets(answer, sizeof(answer), stdin) == NULL) {
            printf("Error reading input\n");
            continue;
        }
        
        char first = tolower(answer[0]);
        
        if (first == 'y') {
            return 1;
        } else {
            return 0;
        }
    }
}