#include "sudoku.h"

/* Eric Roch - MP7
 *
 * This program solves a sudoku puzzle using recursion.  Given an intial
 * puzzle board, it will attempt to fill each cell with a value.  If a cell
 * can not be filled with a valid value, the program returns to the previous
 * recursive call and tries a different value in the previous cell.  The
 * recursion allows the program to go back and adjust previous cells easily when
 * it hits a dead end.  The main function, solve_sudoku() utilizes several other
 * functions to verify that the test value can legally be placed in the current cell.
 */

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

    for (int col=0; col<9; col++) if(sudoku[i][col] == val) return 1;

    return  0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
    
    for (int row=0; row<9; row++) if(sudoku[row][j] == val) return 1;

    return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

    for (short z_i = (i/3) * 3; z_i < ((i/3 + 1)*3); z_i++){
        for (short z_j = (j/3) * 3; z_j < ((j/3 + 1)*3); z_j++){
            if ( val == sudoku [z_i][z_j]) return 1;
        }
    }

    return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

    if (is_val_in_3x3_zone(val, i, j, sudoku) || is_val_in_col(val, j, sudoku) 
        || is_val_in_row(val, i, sudoku)) return 0;
    
    return 1;
}

int find_empty(int *i, int *j, const int sudoku[9][9]){
    for (int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            if(sudoku[row][col] == 0 ){
                *i = row;
                *j = col;
                return 1;
            }
        }
    }

    return 0;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
    
    int i, j;

    if (!find_empty(&i, &j, sudoku)) return 1;

    for (int num = 1; num <=9; num++) {
        if(is_val_valid(num, i, j, sudoku)){
            sudoku[i][j] = num;
            if (solve_sudoku(sudoku)) return 1;
            sudoku[i][j] = 0;
        }
    }

    return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9]) {
    int i, j;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            printf("%2d", sudoku[i][j]);
        }
        printf("\n");
    }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
    FILE *reader = fopen(fpath, "r");
    assert(reader != NULL);
    int i, j;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            fscanf(reader, "%d", &sudoku[i][j]);
        }
    }
    fclose(reader);
}