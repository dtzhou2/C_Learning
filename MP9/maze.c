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
    FILE *fp;
    int o_width;
    int o_height;
    char ** o_cells;

    fp = fopen(fileName, "r");
    maze_t * o_maze = (maze_t*)malloc(sizeof(maze_t));

    if (o_maze == NULL) {
        printf("Maze allocation failed");
        return NULL;
    }

    fscanf(fp, "%d %d \n", &o_width, &o_height);

    o_cells = (char**)malloc(o_height * sizeof(char *));

    for(int i=0; i<o_height; i++) o_cells[i] = (char*)malloc(o_width * sizeof(char));

    for(int i=0; i<o_height; i++){
        for(int j=0; j<o_width; j++){
            fscanf(fp, "%c", &o_cells[i][j]);
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

    o_maze->width=o_width;
    o_maze->height=o_height;
    o_maze->cells=o_cells;

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
    for(int i=0; i<maze->height; i++){
        free(maze->cells[i]);
    }

    free(maze->cells);
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

    if(col>=width || col<0 || row<0 || row>=height) return 0;
    if(maze_obj == WALL || maze_obj == PATH) return 0;
    if(maze_obj == END){
       maze->cells[maze->startRow][maze->startColumn] = START;
       return 1;
    }
    maze->cells[row][col] = PATH;   
    if(solveMazeManhattanDFS(maze, col-1, row) == 1) return 1;
    if(solveMazeManhattanDFS(maze, col+1, row) == 1) return 1;
    if(solveMazeManhattanDFS(maze, col, row-1) == 1) return 1;
    if(solveMazeManhattanDFS(maze, col, row+1) == 1) return 1;
    maze->cells[row][col] = VISITED;                                     
    return 0;                                                  
}
