#include <stdio.h>
#include "filesf.h"

#define ARRAY_INPUT 1

int main() {
    FILE* file = fopen("library.bin", "w+b");
    int choice;

    #ifdef ARRAY_INPUT
    add_records_from_array(file);
    #endif

    while (1) {
        printf("       Menu\n");
        printf("-------------------\n");
        printf("1. Add record\n");
        printf("2. Delete record\n");
        printf("3. Find record\n");
        printf("4. Change record\n");
        printf("5. Show all records\n");
        printf("0. Exit\n\n");
        printf("Your choice: ");
        
        choice = get_valid_int();
        
        printf("\n");

        switch (choice) {
            case 1: {
                add_record(file);
                break;
            }
            case 2: {
                printf("Input index of record: ");
                int index = get_valid_int();
                delete_record(file, index-1);
                break;
            }
            case 3: {
                get_records(file);
                break;
            }
            case 4: {
                printf("Input index of record: ");
                int index = get_valid_int();
                change_record(file, index-1);
                break;
            }
            case 5: {
                display_records(file);
                break;
            }
            case 0: {
                fclose(file);
                printf("Exiting...\n");
                return 0;
            }
            default:
                printf("Wrong command\n");
        }
    }

    return 0;
}