#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* Daniel Zhou - MP9
 * This file includes code to help recursively solve a maze puzzle
    It contains functions to first generate/allocate the maze structure by reading from
    a file and building the maze from the file data. Then, using that maze,
    it loops through and recursively solves it using a DFS floodfill algorithim
    this algo looks at the maze elements above below and to the left and right
    returning false if they are wall or out of bounds structures and true if it is the 
    end structure. It makes sure to mark the current path as visited so as to ensure that
    it traces a clear path towards the end. Once it hits the end it resets the start char
    in case it was marked as visited by the algorithim

 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    FILE *fp;
    char ** o_cells;
    int o_width;
    int o_height;

    // Allocates a file pointer, opens a file and errors out if that allocaiton fails
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Maze allocation failed");
        return NULL;
    }
    // Allocates a maze structure and errors out if allocation fails
    maze_t * o_maze = (maze_t*)malloc(sizeof(maze_t));
    if (o_maze == NULL) {
        printf("Maze allocation failed");
        return NULL;
    }

    fscanf(fp, "%d %d \n", &o_width, &o_height);
    // Creates 2d array to store maze // allocates one dimension of the maze
    o_cells = (char**)malloc(o_height * sizeof(char *));

    // Since maze is a 2d structure we have to allocate a 1d array in each slot of the 
    // base structure 
    for(int i=0; i<o_height; i++) o_cells[i] = (char*)malloc(o_width * sizeof(char));

    for(int i=0; i<o_height; i++){
        for(int j=0; j<o_width; j++){
            // Loops through the entire 2d array, allocating each position of the maze
            // with its associated char 
            fscanf(fp, "%c", &o_cells[i][j]);
            // Checks if the allocated char is a special char, if it is set appropriate 
            // start/end variables 
            if(o_cells[i][j] == START){
                o_maze->startColumn=j;
                o_maze->startRow=i;
            }
            else if (o_cells[i][j] == END){
                o_maze->endColumn=j;
                o_maze->endRow=i;
            }
        }
        char discard;
        fscanf(fp, "%c", &discard);
    }
    // Associate cells arrray with created maze sctructure
    o_maze->cells=o_cells;
    o_maze->width=o_width;
    o_maze->height=o_height;
    // Close file to prevent hanging pointers
    fclose(fp);

    return o_maze;
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
    // Frees maze structure by first freeing the individual arrays
    for(int i=0; i<maze->height; i++){
        free(maze->cells[i]);
    }
    // After freeing the individual arrays free the larger array
    free(maze->cells);
    // Finally free the maze structure 
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
    // Loops through every position in the array and prints out the associated
    // Character
    for(int i=0; i<maze->height; i++){
        for(int j=0; j<maze->width; j++){
            printf("%c", maze->cells[i][j]);
        }
        printf("\n");

    }
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
         
    int width = maze->width;
    int height = maze->height;
    char maze_obj = maze->cells[row][col];

    // If out of bounds, make sure to return false
    if(col>=width || col<0 || row<0 || row>=height) return 0;
    // If wall make sure to return false
    if(maze_obj == WALL || maze_obj == PATH) return 0;
    if(maze_obj == END){
        // Make sure to reset start position before exiting
       maze->cells[maze->startRow][maze->startColumn] = START;
       return 1;
    }
    maze->cells[row][col] = PATH;   
    // Floods the nearby cells, searching left right up and down
    if(solveMazeManhattanDFS(maze, col-1, row) == 1) return 1;
    if(solveMazeManhattanDFS(maze, col+1, row) == 1) return 1;
    if(solveMazeManhattanDFS(maze, col, row-1) == 1) return 1;
    if(solveMazeManhattanDFS(maze, col, row+1) == 1) return 1;
    // Make sure to mark the current cell as visited
    maze->cells[row][col] = VISITED;                                     
    return 0;                                                  
}
