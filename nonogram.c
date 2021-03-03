#include "nonogram.h"

void get_restriction_table(int table[][RESTRICT_MAX + 1], int len){
    int i, j, restriction_len, restriction_num;
    for (i = 0; i< len; i++){
        scanf("%d", &restriction_len);
        table[i][0] = restriction_len;
        for (j = 0; j < restriction_len; j++) {
            scanf("%d", &restriction_num);
            table[i][j + 1] = restriction_num;
        }
    }
}

void print_restriction_table(int table[][RESTRICT_MAX + 1], int len){
    int i, j, restriction_len;
    for (i = 0; i< len; i++){
        restriction_len = table[i][0];

        printf("%d ", restriction_len);
        for (j = 0; j < restriction_len; j++) {
            printf("%d ", table[i][j+1]);
        }
        printf("\n");
    }
    printf("\n");
}

void init_filling_table(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len){
    int i, j;
    for (i = 0; i < ROW_MAX; i++){
        for (j = 0; j<COL_MAX; j++) {
            filling_table[i][j] = -2;
        }
    }
    for (i = 0; i < row_len; i++){
        for (j = 0; j<col_len; j++) {
            filling_table[i][j] = -1;
        }
    }
}

void print_filling_table(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len){
    int i, j;
    for (i = 0; i < row_len; i++){
        for (j = 0; j<col_len; j++) {
            printf("%d ",filling_table[i][j]);

        }
        printf("\n");
    }
    printf("\n");
}

void print_filling_table_official(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len){
    int i, j;
    char x;
    for (i = 0; i < row_len; i++){
        for (j = 0; j<col_len; j++) {
            if (filling_table[i][j] == 1) x = 'o';
            else if (filling_table[i][j] == 0) x = '_';
            else x = '?';
            printf("%c",x);
        }
        printf("\n");
    }
    printf("\n");
}

int check_filling_table_filled(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len){
    int i, j;
    int filled_flag = 1;
    for (i = 0; i < row_len; i++){
        for (j = 0; j<col_len; j++) {
            if (filling_table[i][j] == -1){
                filled_flag = 0;
                break;
            }
        }
    }
    return filled_flag;
}

int check_filling_table_vaild(int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len, int row_restriction_table[][RESTRICT_MAX + 1], int col_restriction_table[][RESTRICT_MAX + 1]){
    int i, j, k;
    int valid_flag = 1;
    int sum_of_vector = 0, sum_of_restriction = 0;
    int restriction_len = 0;
    int restriction_num;
    int start_point = 0;
    int empty_flag = 1;

    // check rows
    for (i = 0; i < row_len; i++){
        sum_of_vector = 0;
        sum_of_restriction = 0;
        restriction_len = row_restriction_table[i][0];
        
        // if no restriction; continue
        if (restriction_len == 0){
            continue;
        }
        
        // if sum are not equal, directly return
        for (j = 0; j < col_len; j++){
            sum_of_vector += filling_table[i][j];
        }
        for (j = 0; j < restriction_len; j++){
            sum_of_restriction += row_restriction_table[i][j+1];
        }

        if (sum_of_restriction != sum_of_vector){
            valid_flag = 0;
            //printf("Wrong row sum!\n");
            return valid_flag;
        }

        // check every restricion in detail
        start_point = 0;
        empty_flag = 1;
        for (j=0; j<restriction_len;j++){
            restriction_num = row_restriction_table[i][j+1];
            sum_of_vector = 0;
            
            // jump empty and set the empty_flag = 1
            while ((filling_table[i][start_point] == 0) && (start_point < col_len)){
                start_point++;
                empty_flag = 1;
            }

            // check if any white in the middle 
            if (empty_flag != 1){
                valid_flag = 0;
                //printf("Wrong cont. row at restriction %d %d with %d\n", i, k+1, restriction_num);
                return valid_flag;
            }

            // start counting
            for (k = 0; k < restriction_num; k++){
                if (filling_table[i][start_point] != 1) {
                    valid_flag = 0;
                    //printf("Wrong row at restriction %d %d with %d\n", i, k+1, restriction_num);
                    return valid_flag;
                }
                start_point++;
                empty_flag = 0;
            }
        }
    }

    // check col
    for (i = 0; i < col_len; i++){
        sum_of_vector = 0;
        sum_of_restriction = 0;
        restriction_len = col_restriction_table[i][0];
        
        // if no restriction; continue
        if (restriction_len == 0){
            continue;
        }
        
        // if sum are not equal, directly return
        for (j = 0; j < row_len; j++){
            sum_of_vector += filling_table[j][i];
        }
        for (j = 0; j < restriction_len; j++){
            sum_of_restriction += col_restriction_table[i][j+1];
        }

        if (sum_of_restriction != sum_of_vector){
            valid_flag = 0;
            //printf("Wrong column sum!\n");
            return valid_flag;
        }

        // check every restricion in detail
        start_point = 0;
        empty_flag = 1;
        for (j=0; j<restriction_len;j++){
            restriction_num = col_restriction_table[i][j+1];
            
            // jump empty and set the empty_flag = 1
            while ((filling_table[start_point][i] == 0) && (start_point < row_len)){
                start_point++;
                empty_flag = 1;
            }

            // check if any white in the middle 
            if (empty_flag != 1){
                valid_flag = 0;
                //printf("Wrong cont. col at restriction %d %d with %d\n", i, k+1, restriction_num);
                return valid_flag;
            }

            // start counting
            for (k = 0; k < restriction_num; k++){
                if (filling_table[start_point][i] != 1) {
                    valid_flag = 0;
                    //printf("Wrong col at restriction %d %d with %d\n", i, k+1, restriction_num);
                    return valid_flag;
                }
                start_point++;
                empty_flag = 0;
            }
        }
    }
    return valid_flag;
}

void get_next_position(int row_now, int col_now, int pos_next[2], int col_len){
    // first should be 0, -1
    int extend_now, extend_next, extend_all;
    extend_now = row_now * col_len + col_now;
    extend_next = extend_now + 1;
    if (row_now == 0 && col_now == -1){
        pos_next[0] = 0;
        pos_next[1] = 0;
        return;
    }
    pos_next[0] = extend_next / col_len;
    pos_next[1] = extend_next % col_len;
}

void matriscopy(void * destmat, void * srcmat){
    memcpy(destmat,srcmat, ROW_MAX*COL_MAX*sizeof(int));
}

int recursive_filling(int row_now, int col_now, int filling_table[ROW_MAX][COL_MAX], int row_len, int col_len, int row_restriction_table[][RESTRICT_MAX + 1], int col_restriction_table[][RESTRICT_MAX + 1]){
    int flag = 0, success=0;
    int pos_next[2];
    int filling_table_temp[ROW_MAX][COL_MAX];

    matriscopy(filling_table_temp, filling_table);

    //print_filling_table(filling_table_temp, row_len, col_len);

    if (check_filling_table_filled(filling_table_temp, row_len, col_len)) {
        if (check_filling_table_vaild(filling_table_temp, row_len, col_len, row_restriction_table, col_restriction_table)) {
            print_filling_table_official(filling_table_temp, row_len, col_len);
            flag = 1;
            return flag;
        } else {
            return flag;
        }
    } else {
        get_next_position(row_now, col_now, pos_next, col_len);
        row_now = pos_next[0];
        col_now = pos_next[1];

        // fill black
        filling_table_temp[row_now][col_now] = 1; 
        success = recursive_filling(row_now, col_now, filling_table_temp, row_len, col_len, row_restriction_table, col_restriction_table);

        if (success){
            flag = 1;
            return flag;
        }

        // fill white
        filling_table_temp[row_now][col_now] = 0; 
        success = recursive_filling(row_now, col_now, filling_table_temp, row_len, col_len, row_restriction_table, col_restriction_table);

        if (success){
            flag = 1;
            return flag;
        }
    }
}