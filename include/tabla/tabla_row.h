#ifndef TABLA_ROW_H
#define TABLA_ROW_H

#include <stdlib.h>

typedef struct tb_row
{
    size_t num_cells;
    size_t cap;
    char **cells;
} tb_row;

tb_row tb_row_init();
void tb_row_destroy(tb_row *row);

tb_row tb_row_parse(const char* row);

void tb_row_add_cell(tb_row *row, const char* cell);

#endif
