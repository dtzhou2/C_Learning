/* Eric Roch - MP9
 * This program solves a maze recursively.  Given an imput file,
 * the program reads in the size of the maze from the first line
 * of the file, then dynamically allocates memory for a maze structure
 * to save the maze as defined by walls (%), start (S), end (E), path (.)
 * and visited (~) cells.  The program then uses a depth first search
 * to find a path through the maze recursively.  If the solver cannot
 * continue in a particular direction, it tries another. When it cannot
 * move any more, it backtracks until it finds another direction to move.
 * This recursion and backtracking continues until the solver finds the
 * end cell.  All cells that were visited during the solve are marked
 * by a '~', and cells that were part of the solution path are marked
 * with a '.'.
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // indexing variables for loops
    int i, j;

    // local variables for generating struct values
    // will be copied into struct at the end
    int _width;
    int _height;
    int _startColumn;
    int _startRow;
    int _endColumn;
    int _endRow;
    char ** _cells;

    // pointer that we will return
    maze_t * maze_ptr = (maze_t*)malloc(sizeof(maze_t));

    // make sure the allocation worked
    if (maze_ptr == NULL) {
        printf("Maze allocation failed");
        return NULL;
    }

    // open the file and make sure it exists
    FILE * fptr = fopen(fileName, "r");
    if (fptr == NULL) {
        printf("Error: %s not found", fileName);
        return NULL;
    }

    // scan in the width and height from line one
    fscanf(fptr, "%d %d\n", &_width, &_height);

    // allocate char pointers for each row of the array
    _cells = (char **)malloc(_height * sizeof(char *));

    // for each row, allocate an array of chars
    for (i = 0; i < _height; i ++) {
        _cells[i] = (char *)malloc(_width * sizeof(char));
    }

    for (i = 0; i < _height; i ++) {
        // loop through each column of this row
        for (j = 0; j < _width; j ++) {
            // put the character from the file into the array
            fscanf(fptr, "%c", &_cells[i][j]);

            // if the cell is the start or end, store the location
            if (_cells[i][j] == START) {
                _startRow = i;
                _startColumn = j;
            }
            if (_cells[i][j] == END) {
                _endRow = i;
                _endColumn = j;
            }
        }
        // scan the newline into a dummy variable
        char discard;
        fscanf(fptr, "%c", &discard);
    }

    // fill the struct with the local variables
    maze_ptr->width = _width;
    maze_ptr->height = _height;
    maze_ptr->startColumn = _startColumn;
    maze_ptr->startRow = _startRow;
    maze_ptr->endColumn = _endColumn;
    maze_ptr->endRow = _endRow;
    maze_ptr->cells = _cells;

    fclose(fptr);
    return maze_ptr;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{

    // start with the deepest memory: the row arrays of cells
    int i;
    for (i = 0; i < maze->height; i++) {
        free(maze->cells[i]);
    }

    // now we can free the cell array
    free(maze->cells);

    // and finally release the struct itself
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    char ** array = maze->cells;

    int i;
    for (i = 0; i < maze->height; i ++) {
        printf("%s\n", array[i]);
    }

    // printf("Start at (%d,%d)\n", maze->startColumn, maze->startRow);
    // printf("End at (%d,%d)\n", maze->endColumn, maze->endRow);
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    if (col < 0 || col >= maze->width || row < 0 || row >= maze->height) {      // check if out of bounds
        return 0;
    }
    if (maze->cells[row][col] == WALL || maze->cells[row][col] == PATH) {       // check if wall or part of path
        return 0;
    }
    if (maze->cells[row][col] == END) {                                         // check if at the end
        return 1;
    }
    if (maze->cells[row][col] != START) {                                       // set the cell to PATH, only if
        maze->cells[row][col] = PATH;                                           // it is not the start
    }
    if (solveMazeManhattanDFS(maze, col - 1, row)) {                            // try solving to the left
        return 1;
    }
    if (solveMazeManhattanDFS(maze, col + 1, row)) {                            // try solving to the right
        return 1;
    }
    if (solveMazeManhattanDFS(maze, col, row - 1)) {                            // try solving to the top
        return 1;
    }
    if (solveMazeManhattanDFS(maze, col, row + 1)) {                            // try solving to the bottom
        return 1;
    }
    if (maze->cells[row][col] != START) {                                       // if none of those worked, mark
        maze->cells[row][col] = VISITED;                                        // cell as visited, if it is not the start
    }

    return 0;                                                                   // return false if not successful
}
