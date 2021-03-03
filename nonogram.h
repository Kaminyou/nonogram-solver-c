#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_MAX 20
#define COL_MAX 20
#define RESTRICT_MAX 10

void get_restriction_table(int table[][RESTRICT_MAX + 1], int len);
void print_restriction_table(int table[][RESTRICT_MAX + 1], int len);

void init_filling_table(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len);
void print_filling_table(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len);
void print_filling_table_official(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len);

int check_filling_table_filled(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len);
int check_filling_table_vaild(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len, int row_restriction_table[][RESTRICT_MAX + 1], int col_restriction_table[][RESTRICT_MAX + 1]);

void get_next_position(int row_now, int col_now, int pos_next[2], int col_len);
void matriscopy(void * destmat, void * srcmat);
int recursive_filling(int row_now, int col_now, int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len, int row_restriction_table[][RESTRICT_MAX + 1], int col_restriction_table[][RESTRICT_MAX + 1]);
