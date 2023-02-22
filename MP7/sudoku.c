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
    return  0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
    return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
    return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
    return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
    return 0;
}
