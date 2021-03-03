#include <stdio.h>
#include "nonogram.h"

int main(){

    int row_len, col_len;
    int row_restriction_table[ROW_MAX][RESTRICT_MAX + 1];
    int col_restriction_table[COL_MAX][RESTRICT_MAX + 1];
    int filling_table[ROW_MAX][COL_MAX];
    
    scanf("%d", &row_len);
    scanf("%d", &col_len);

    get_restriction_table(row_restriction_table, row_len);
    get_restriction_table(col_restriction_table, col_len);
    init_filling_table(filling_table, row_len, col_len);
    
    //print_restriction_table(row_restriction_table, row_len);
    //print_restriction_table(col_restriction_table, col_len);

    recursive_filling(0, -1, filling_table, row_len, col_len, row_restriction_table, col_restriction_table);

    return 0;
}