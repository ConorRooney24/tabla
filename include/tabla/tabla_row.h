#ifndef TABLA_ROW_H
#define TABLA_ROW_H

#include <stdlib.h>

typedef struct tb_row
{
    size_t num_cells;
    char **cells;
} tb_row;

void tb_row_destroy(tb_row *row);

tb_row tb_row_parse(const char* row);

#endif