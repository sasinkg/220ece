#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* this is late because of internet issues - my wifi at home went out for a few hours and 
it ended up being something wrong with our internet plan. 
I know its not an excuseable circumstance but because the midterm was on Thursday I didnt 
get an opportunity to start this MP until after, and when we did finish, I lost connection while
working on it so I wasn't able to submit it on time */ 

/* we allocated memory for the board by reading the file and creating a new array.
 * then we create destroy and print functions so that the board prints and then destroys
 * at the very end. we then use recursive calls to check each move (up, down, left, right)
 * to find the correct move and then we make that move. we had trouble with the solve
 * function because we kept having segmentation faults since part of our logic was wrong
 * and it was accessing memory that didn't exist.
 * group memmbers: sasinkg2, dhruvv2, akshay5
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
    int rows;
    int cols;
    int i;
    int j;
    FILE *fptr = fopen(fileName, "r"); //open file for read
    if(fptr == NULL){
        return NULL;
    }
    fscanf(fptr, "%d %d", &rows, &cols); //scan for row and col size
    maze_t *maze = (maze_t *)malloc(sizeof(maze_t)); //create space for maze structure
    maze->cells=(char**)malloc((rows)*sizeof(char*)); //create space for lookup
    maze->height = rows;
    maze->width = cols; //initialize maze structure 
    for(i=0;i<rows;i++){
      maze->cells[i]=(char*)malloc(sizeof(char)*(cols)); //fill for columns
    }
    char temp;
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            temp = fgetc(fptr); //read character
            if(i==10) printf("%c ", temp);
            if(temp=='\n'){
                j--;
            }else{
                maze->cells[i][j] = temp; //save read character into structure
            }
            if(temp=='S'){
                maze->startRow = i;
                maze->startColumn = j;
                
            }
            if(temp=='E'){
                maze->endRow = i;
                maze->endColumn = j;
                
            }
        }
    }
    fclose(fptr);
    return maze; 
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
    int i;
    for (i=0; i<maze->height; i++){ //loop through all of structure
        free(maze->cells[i]);
    }
    free(maze->cells); 
    free(maze); //free structure
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
    int i;
    int j;
    for(i=0; i<maze->height; i++){
        for (j=0; j<maze->width; j++){ //loop through board and print
            
            printf("%c", maze->cells[i][j]);
        }
        printf("\n"); //print newlines to make board look nice
        
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
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if(col<0 || row<0 || col>=maze->width || row>=maze->height){ //check boundary conditions
        return 0;
    }
    if(maze->cells[row][col] == 'E'){ //check if end has been reached
        maze->cells[maze->startRow][maze->startColumn] = 'S'; //set back to start
        return 1;
    } 
    if(maze->cells[row][col]==' ' || maze->cells[row][col] == 'S'){ //if not valid character
        maze->cells[row][col] = '*'; //correct solution if empty conditions are met
        if(solveMazeDFS(maze, col, row+1) == 1) return 1;
        if(solveMazeDFS(maze, col, row-1) == 1) return 1;
        if(solveMazeDFS(maze, col+1, row) == 1) return 1;
        if(solveMazeDFS(maze, col-1, row) == 1) return 1; //check down, up, right, left for a correct move through a recursive call
        maze->cells[row][col]='%'; //mark currently found path as wall so as to not go backwards
    }
    return 0;
}


