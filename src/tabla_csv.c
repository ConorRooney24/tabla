#include "../include/tabla/tabla_csv.h"
#include <stdlib.h>
#include <stdio.h>

tb_csv tb_csv_load(FILE *file)
{
    tb_csv csv;

    if (file == NULL)
    {
        free(csv.rows);
        csv.rows = NULL;
        csv.num_rows = 0;
        csv.cap = 0;

        return csv;
    }

    csv.rows = (tb_row*)malloc(sizeof(tb_row) * 2);
    csv.num_rows = 0;
    csv.cap = 2;

    char *line = NULL;
    size_t cap = 0;
    while (getline(&line, &cap, file) != -1)
    {
        tb_row row = tb_row_parse(line);
        if (row.cells == NULL) continue; // If the line is blank, we skip to the next one

        tb_csv_insert_row(&csv, row);
    }

    return csv;
}

void tb_csv_write(tb_csv csv, FILE *file)
{
    if (csv.rows == NULL || file == NULL) return;

    for (size_t row = 0; row < csv.num_rows; row++)
    {
        for (size_t cell = 0; cell < csv.rows[row].num_cells; cell++)
        {
            fprintf(file, "%s", csv.rows[row].cells[cell]);

            if (cell != csv.rows[row].num_cells - 1) // If not the last cell in the row
            {
                fprintf(file, ",");
            }
            else if (row != csv.num_rows - 1) // If not on the last row
            {
                fprintf(file, "\n");
            }
        }
    }
}

void tb_csv_destroy(tb_csv *csv)
{
    if (csv == NULL) return;

    for (size_t i = 0; i < csv->num_rows; i++)
    {
        tb_row_destroy(&csv->rows[i]);
    }

    free(csv->rows);
    csv->rows = NULL;

    csv->num_rows = 0;
    csv->cap = 0;
}

void tb_csv_insert_row(tb_csv *csv, tb_row row)
{
    if (csv == NULL || csv->rows == NULL || row.cells == NULL) return;

    if (csv->num_rows >= csv->cap)
    {
        size_t new_cap = csv->cap * 2;

        tb_row *temp = (tb_row*)realloc(csv->rows, new_cap * sizeof(tb_row));
        if (!temp) return; // TODO handle this properly

        csv->rows = temp;
        csv->cap = new_cap;
    }

    csv->rows[csv->num_rows] = row;
    csv->num_rows++;
}