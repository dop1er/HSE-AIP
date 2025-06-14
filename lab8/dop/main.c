#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "input.h"

int main() {
    int L = inputPositiveNumber("Enter tree depth L: ");
    
    printf("\nTree depth: L = %d\n", L);
    printf("Note: You need to enter more than %d numbers\n\n", L);
    
    int maxNumbers = 1000;
    int N;
    int* numbers = inputNumbers(maxNumbers, &N);
    
    if (numbers == NULL) {
        return 1;
    }
    
    if (N <= L) {
        printf("Error: Number of entered values (%d) must be greater than L (%d)\n", N, L);
        free(numbers);
        return 1;
    }
    
    int index;
    TreeNode* root = buildTree(numbers, N, L, &index);
    
    if (root == NULL) {
        printf("Error creating tree\n");
        free(numbers);
        return 1;
    }
    
    printf("Tree root pointer: %p\n", (void*)root);
    
    if (askYesNo("\nDo you want to see additional information?")) {
        printf("\n=== Additional Information ===\n");
        printf("Parameters: L = %d, N = %d\n", L, N);
        printNumbers(numbers, N);
        printf("Root value: %d\n", root->value);
        printf("Numbers used: %d out of %d\n", index, N);
        
        if (index < N) {
            printf("Remaining unused numbers: ");
            for (int i = index; i < N; i++) {
                printf("%d ", numbers[i]);
            }
            printf("\n");
        }
        
        if (askYesNo("\nDo you want to see the tree structure?")) {
            printf("\n=== Tree Structure ===\n");
            printTree(root, 0);
        }
    }
    
    freeTree(root);
    free(numbers);
    
    return 0;
}