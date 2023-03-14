#include "sudoku.h"

/* Daniel Zhou - MP7
 * This file includes code to help recursively solve a sudoku puzzle
    The first 3 functions contain code to check the validity of a sudoku solution,
    ensuring that the number entered is valid in a row, col and 3x3 grid,
    then the next function uses that information to check if a value is valid in the whole grid
    Last function then solves sudoku recursively by using that function to generate empty sudoku cells,
    then finding the right number to input into that empty cell
 */

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
    // Loops along the row and returns 1 if the value is found
    for (int col=0; col<9; col++) if(sudoku[i][col] == val) return 1;
    // Returns 0 as default
    return  0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
    // Loops along the column and returns 1 if the value is found
    for (int row=0; row<9; row++) if(sudoku[row][j] == val) return 1;
    // Returns 0 as a default  
    return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
    // Divides the number by 3 truncating the remainderm meaning that multiplying by three gives the
    // Starting row value
    for (short z_i = (i/3) * 3; z_i < ((i/3 + 1)*3); z_i++){
        // Does the same thing for the column value to get the starting column value
        for (short z_j = (j/3) * 3; z_j < ((j/3 + 1)*3); z_j++){
            // Returns 1 if the value is found, otherwise returns 0 
            if ( val == sudoku[z_i][z_j]) return 1;
        }
    }

    return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
    // Checks if the value meets alll three conditions, not in col row or 3x3)
    // If meets all requirements return 1 else return 0
    if (is_val_in_3x3_zone(val, i, j, sudoku) || is_val_in_col(val, j, sudoku) 
        || is_val_in_row(val, i, sudoku)) return 0;
    
    return 1;
}

// Finds an empty cell by looking fro cells with value of 0
int find_empty(int *i, int *j, const int sudoku[9][9]){
    for (int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            // Loops through sudoku board and checks for an empty cell
            if(sudoku[row][col] == 0 ){
                *i = row;
                *j = col;
                return 1;
            }
        }
    }
    // Returns 1 if there is an empty cell, otherwise returns 0 
    return 0;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
    
    int i, j;
    // Solves sudoku recursively
    // First checks if sudoku is solved e.g there are no empty values left
    if (!find_empty(&i, &j, sudoku)) return 1;
    // If there are empty values left, solves sudoku by testing which number 1-9 can be fit into current row/col
    // Places whicever valid number can be fit into row/col and then calls solve_sudoku again with incremented row/col
    // This works because find empty will set values of i and j into next empty sudoku cell
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