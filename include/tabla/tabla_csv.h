#ifndef TABLA_CSV_H
#define TABLA_CSV_H

#include <stdlib.h>
#include <stdio.h>
#include "tabla_row.h"

typedef struct tb_csv
{
    size_t num_rows;
    size_t cap;
    tb_row *rows;
} tb_csv;

tb_csv tb_csv_create(tb_row header);
tb_csv tb_csv_load(FILE *file);
void tb_csv_write(tb_csv csv, FILE *file);
void tb_csv_destroy(tb_csv *csv);

void tb_csv_insert_row(tb_csv *csv, tb_row row);

#endif