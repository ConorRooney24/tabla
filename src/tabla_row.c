#include <ord/da.h>
#include <string.h>
#include "../include/tabla/tabla_row.h"

tb_row tb_row_init()
{
    tb_row row;
    row.cells = (char**)malloc(sizeof(char*) * 1);
    row.cap = 1;
    row.num_cells = 0;

    if (row.cells == NULL)
    {
        row.num_cells = 0;
        row.cap = 0;
        free(row.cells);
    }

    return row;
}

void tb_row_destroy(tb_row *row)
{
    if (row == NULL) return;

    for (size_t i = 0; i < row->num_cells; i++)
    {
        free(row->cells[i]);
        row->cells[i] = NULL;
    }

    free(row->cells);
    row->cells = NULL;

    row->num_cells = 0;
    row->cap = 0;
}

tb_row tb_row_parse(const char* row)
{
    tb_row new_row;
    new_row.cells = (char**)malloc(sizeof(char*) * 2);
    new_row.num_cells = 0;
    new_row.cap = 2;

    if (row[0] == '\n' || row[0] == '\0' || row == NULL || new_row.cells == NULL)
    {
        new_row.cells = NULL;
        new_row.num_cells = 0;
        new_row.cap = 0;
        return new_row;
    }

    da_c current_cell = da_c_init(); // The current cell we are parsing

    for (const char *p = row;; p++)
    {
        if (*p == ',' || *p == '\n' || *p == '\0') // If on a deliminator
        {
            da_c_push(&current_cell, '\0');
            tb_row_add_cell(&new_row, strdup(current_cell.data));

            current_cell.count = 0;

            if (*p == '\0' || *p == '\n') break; // We are finished with the line in this case
        }
        else
        {
            da_c_push(&current_cell, *p); // Push current character
        }
    }

    return new_row;
}

void tb_row_add_cell(tb_row *row, const char* cell)
{
    if (row == NULL || cell == NULL) return;

    if (row->num_cells >= row->cap)
    {
        size_t new_cap = row->cap * 2;

        char **temp = (char**)realloc(row->cells, new_cap * sizeof(char*));
        if (!temp) return; // TODO handle properly

        row->cells = temp;
        row->cap = new_cap;
    }

    row->cells[row->num_cells] = cell;
    row->num_cells++;
}