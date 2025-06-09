#include <io.h> //chsize
#include "library.h"
#include "inputf.h"


struct library input_library(){
    struct library library;

    printf("Input author's name: ");
    fgets(library.author, sizeof(library.author), stdin);
    library.author[strcspn(library.author, "\n")] = '\0';

    printf("Input book's title: ");
    fgets(library.title, sizeof(library.title), stdin);
    library.title[strcspn(library.title, "\n")] = '\0';

    printf("Input publisher: ");
    fgets(library.publisher, sizeof(library.publisher), stdin);
    library.publisher[strcspn(library.publisher, "\n")] = '\0';

    printf("Input year: ");
    library.year = get_valid_int();

    printf("Input pages' amount: ");
    library.pages = get_valid_int();

    return library;
}

void add_record(FILE *file){
    struct library record = input_library();
    int check = 0;
    check = fwrite(&record, sizeof(struct library), 1, file);
    if (check != 1)
    {
        printf("ERROR");
        exit(1);
    }
}

void add_records_from_array(FILE *file){
    struct library record;
    struct library records[] = {
        {"Ray Dalio", "Principles", "MIF. Business", 2021, 654},
        {"Paulo Coelho", "The Alchemist", "ACT", 1988, 450},
        {"J. R. R. Tolkien", "The Hobbit", "Test 123", 1987, 1247}
    };

    for (int i = 0; i < 3; i++)
    {
        record = records[i];
        fwrite(&record, sizeof(struct library), 1, file);
    }
}

void display_records(FILE *file){
    struct library record;
    rewind(file);

    printf("List of books:\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("| N  |         Author           |          Title         |    Publisher    | Year | Pages |\n");
    printf("--------------------------------------------------------------------------------------------\n");
    int index = 0;
    while (fread(&record, sizeof(struct library), 1, file)) {
        printf("| %-2ld | %-24s | %-22s | %-15s | %-4d | %-5d |\n",
               index + 1,
               record.author,
               record.title,
               record.publisher,
               record.year,
               record.pages);
        index++;
    }

    printf("--------------------------------------------------------------------------------------------\n\n");
}

void change_record(FILE *file, int index){
    int file_size;
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    if (index * sizeof(struct library) >= file_size)
    {
        printf("Invalid index\n\n");
        return;
    }
    struct library new_record = input_library();
    fseek(file, index * sizeof(struct library), SEEK_SET);
    fwrite(&new_record, sizeof(struct library), 1, file);
}

void delete_record(FILE *file, int index){
    int file_descriptor = fileno(file);
    int file_size;
    struct library record;
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    if (index * sizeof(struct library) >= file_size)
    {
        printf("Invalid index\n\n");
        return;
    }
    fseek(file, 0, SEEK_SET);

    for (int i = index+1; i*sizeof(struct library) < file_size; i++)
    {
        fseek(file, i * sizeof(struct library), SEEK_SET);
        fread(&record, sizeof(struct library), 1, file);
        fseek(file, (i-1) * sizeof(struct library), SEEK_SET);
        fwrite(&record, sizeof(struct library), 1, file);
    }
    chsize(file_descriptor, file_size - sizeof(struct library));
}

void search_by_author(FILE *file){
    char value[100];
    struct library record;
    rewind(file);

    printf("Input author's name: ");
    fgets(value, 100, stdin);
    value[strcspn(value, "\n")] = '\0';

    printf("--------------------------------------------------------------------------------------------\n");
    printf("|          Author           |          Title         |     Publisher     |  Year  |  Pages |\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (fread(&record, sizeof(struct library), 1, file))
    {
        if (strcmp(record.author, value) == 0)
        {
            printf("| %-25s | %-22s | %-17s | %-6d | %-6d |\n\n",
                record.author,
                record.title,
                record.publisher,
                record.year,
                record.pages);
        }
    }
}

void search_by_title(FILE *file){
    char value[100];
    struct library record;
    rewind(file);

    printf("Input title: ");
    fgets(value, 100, stdin);
    value[strcspn(value, "\n")] = '\0';

    printf("--------------------------------------------------------------------------------------------\n");
    printf("|          Author           |          Title         |     Publisher     |  Year  |  Pages |\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (fread(&record, sizeof(struct library), 1, file))
    {
        if (strcmp(record.title, value) == 0)
        {
            printf("| %-25s | %-22s | %-17s | %-6d | %-6d |\n\n",
                record.author,
                record.title,
                record.publisher,
                record.year,
                record.pages);
        }
    }
}

void search_by_publisher(FILE *file){
    char value[100];
    struct library record;
    rewind(file);

    printf("Input publisher: ");
    fgets(value, 100, stdin);
    value[strcspn(value, "\n")] = '\0';

    printf("--------------------------------------------------------------------------------------------\n");
    printf("|          Author           |          Title         |     Publisher     |  Year  |  Pages |\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (fread(&record, sizeof(struct library), 1, file))
    {
        if (strcmp(record.publisher, value) == 0)
        {
            printf("| %-25s | %-22s | %-17s | %-6d | %-6d |\n\n",
                record.author,
                record.title,
                record.publisher,
                record.year,
                record.pages);
        }
    }
}

void search_by_year(FILE *file){
    int value;
    struct library record;
    rewind(file);

    printf("Input year: ");
    value = get_valid_int();
    printf("\n");

    printf("--------------------------------------------------------------------------------------------\n");
    printf("|          Author           |          Title         |     Publisher     |  Year  |  Pages |\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (fread(&record, sizeof(struct library), 1, file))
    {
        if (record.year == value)
        {
            printf("| %-25s | %-22s | %-17s | %-6d | %-6d |\n\n",
                record.author,
                record.title,
                record.publisher,
                record.year,
                record.pages);
        }
    }
}

void search_by_pages(FILE *file){
    int value;
    struct library record;
    rewind(file);

    printf("Input pages: ");
    value = get_valid_int();
    printf("\n");

    printf("--------------------------------------------------------------------------------------------\n");
    printf("|          Author           |          Title         |     Publisher     |  Year  |  Pages |\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (fread(&record, sizeof(struct library), 1, file))
    {
        if (record.pages == value)
        {
            printf("| %-25s | %-22s | %-17s | %-6d | %-6d |\n\n",
                record.author,
                record.title,
                record.publisher,
                record.year,
                record.pages);
        }
    }
}


void get_records(FILE *file){
    struct library record;
    int choice;
    rewind(file);
    
    while (1)
    {
        printf("Choose a field to search by:\n");
        printf("1. Author\n");
        printf("2. Title\n");
        printf("3. Publisher\n");
        printf("4. Year\n");
        printf("5. Pages\n");
        printf("0. Back to Menu\n");
        printf("Enter your choice (1-5): ");
        choice = get_valid_int();
        printf("\n");

        switch (choice)
        {
        case 1: {
            search_by_author(file);
            break;
        }
        case 2: {
            search_by_title(file);
            break;
        }
        case 3: {
            search_by_publisher(file);
            break;
        }
        case 4: {
            search_by_year(file);
            break;
        }
        case 5: {
            search_by_pages(file);
            break;
        }
        case 0: {
            return;
        }
        default:
            printf("Wrong command\n");
        }
    }
}