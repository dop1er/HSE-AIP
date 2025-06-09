#ifndef FILES_FUNCS
#define FILES_FUNCS
#include <io.h>
#include "library.h"
#include "inputf.h"

struct library input_library();
void add_record(FILE *file);
void add_records_from_array(FILE *file);
void change_record(FILE *file, int index);
void display_records(FILE *file);
void delete_record(FILE *file, int index);
void search_by_author(FILE *file);
void search_by_title(FILE *file);
void search_by_publisher(FILE *file);
void search_by_year(FILE *file);
void search_by_pages(FILE *file);
void get_records(FILE *file);

#endif