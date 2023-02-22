#include <stdlib.h>

/* Eric Roch - MP6
 * This file includes functions to generate the next iteration of a board for
 * Conway's Game of Life.  updateBoard() will generate a new board based on the number
 * of live neighbors each cell has (using the countLiveNeighbor() method) and return
 * the new board.  aliveStable() indicates when the game has reached a steady state
 * and no longer needs to be updated.  This implimentation follows the B3/S23 ruleset.
 */

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

// Turns 2d Coordinate into 1d coordinate of array
int flatten(int boardColSize, int row, int col) {
    return (row*boardColSize + col);
}


int
countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
{
    
    int nCount = 0; // Counts Number of Neighbors

    if (row - 1 >= 0) {
        if(col - 1 >= 0){
            nCount += board[flatten(boardColSize, row-1, col-1)];
        }
        if(col + 1 < boardColSize){
            nCount += board[flatten(boardColSize,row-1, col+1)];
        }
        nCount += board[flatten(boardColSize, row-1, col)];
    }

    if (row + 1 < boardRowSize) {
        if(col - 1 >= 0){
            nCount += board[flatten(boardColSize, row+1, col-1)];
        }
        if(col + 1 < boardColSize){
            nCount += board[flatten(boardColSize, row+1, col+1)];
        }
        nCount += board[flatten(boardColSize, row+1, col)];
    }

    if(col - 1 >= 0){
            nCount += board[flatten(boardColSize, row, col-1)];
    }
        
    if(col + 1 < boardColSize){
            nCount += board[flatten(boardColSize, row, col+1)];
    }

    return nCount;
}
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void
updateBoard(int* board, int boardRowSize, int boardColSize)
{
    int next[boardRowSize*boardColSize];    

    for (int r=0; r < boardRowSize; r++){

        for (int c=0; c < boardColSize; c++){ 
            int count = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);
            short index = flatten(boardColSize, r, c);

            if(count > 3 || count < 2) next[index] = 0 ;
            else if(count == 3) next[index] = 1;
            else next[index] = board[index];

        }

    }

    for (int r=0; r<boardRowSize; r++){

        for (int c=0; c<boardColSize; c++){ 
            short index = flatten(boardColSize, r, c);

            board[index] = next[index];
        }

    }

    // free(board);

    // board = next;

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){

    int temp_board[boardRowSize*boardColSize]; 

    for (int r=0; r<boardRowSize; r++){

        for (int c=0; c<boardColSize; c++){ 
            int index = flatten(boardColSize, r, c);
            temp_board[index] = board[index];
        }

    }
    updateBoard(temp_board, boardRowSize, boardColSize);

    for (int r=0; r<boardRowSize; r++){

        for (int c=0; c<boardColSize; c++){ 
            int index = flatten(boardRowSize, r, c);
            if( temp_board[index] != board[index] ) {
                return 0;
            }
        }

    }

    return 1;

}
