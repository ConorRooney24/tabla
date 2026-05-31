#include <ord/da.h>
#include <string.h>
#include "../include/tabla/tabla_row.h"

tb_row tb_row_parse(const char* row)
{
    tb_row new_row;
    new_row.num_cells = 0;

    if (row[0] == '\n' || row[0] == '\0' || row == NULL)
    {
        new_row.cells = NULL;
        new_row.num_cells = 0;
        return new_row;
    }

    da_s result = da_s_init(); // Dynamic array of strings where each string represents a cell
    da_c current_cell = da_c_init(); // The current cell we are parsing

    for (const char *p = row;; p++)
    {
        if (*p == ',' || *p == '\n' || *p == '\0') // If on a deliminator
        {
            new_row.num_cells++;

            da_c_push(&current_cell, '\0');
            da_s_push(&result, strdup(current_cell.data));

            current_cell.count = 0;

            if (*p == '\0' || *p == '\n') break; // We are finished with the line in this case
        }
        else
        {
            da_c_push(&current_cell, *p); // Push current character
        }
    }

    new_row.cells = result.data;
    return new_row;
}