/* sasinkg2 akshay5 dhruvv2 */ 
/* intro paragraph: 

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

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int liveneighbors = 0; // initializing liveneighbors
for(int i = row-1; i <=row+1; i++){ // checking neighboring rows
    if(i>=0 && i<boardRowSize){ // within bounds
        for(int j = col-1; j<=col+1; j++){ // checking neighboring columns
            if(j>=0 && j<boardColSize){ // within bounds
                if(i!=row || j!=col){ // if it's not the cell (row,col)
                    if(board[i*boardColSize+j] == 1){ // is alive
                        liveneighbors+=1; // increment liveneighbors
                    }
                }
            }
        }
    }
}
    return liveneighbors;
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
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int temp[boardRowSize*boardColSize]; // initializing temp array
    for(int k = 0; k<boardRowSize; k++){
       for(int l = 0; l<boardColSize; l++){
        temp[k*boardColSize+l] = board[k*boardColSize+l]; // copying all values from board into temp
    }}
    for(int i = 0; i<boardRowSize; i++){ // changing values in temp if necessary
        for(int j = 0; j<boardColSize; j++){
            if(board[i*boardColSize+j] == 1){
                if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j)<2 || countLiveNeighbor(board, boardRowSize, boardColSize, i, j)>3){
                    temp[i*boardColSize+j] = 0;
                }
            }
            if(board[i*boardColSize+j] == 0){ // changing values in temp
                if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 3){
                    temp[i*boardColSize+j] = 1;
                }
            }
        }
    }
    for(int k = 0; k<boardRowSize; k++){ 
       for(int l = 0; l<boardColSize; l++){
        board[k*boardColSize+l] = temp[k*boardColSize+l]; // copying temp to board
    }}}

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
int temp[boardRowSize*boardColSize]; 
for(int k = 0; k<boardRowSize; k++){ // copying board to temp
    for(int l = 0; l<boardColSize; l++){
        temp[k*boardColSize+l] = board[k*boardColSize+l];
    }
}
for(int i = 0; i<boardRowSize; i++){ // changing values in temp as necessary
    for(int j = 0; j<boardColSize; j++){
        if(board[i*boardColSize+j] == 1){
            if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j)<2 || countLiveNeighbor(board, boardRowSize, boardColSize, i, j)>3){
                temp[i*boardColSize+j] = 0;
            }
         }
            if(board[i*boardColSize+j] == 0){ // changing values in temp
                if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 3){
                    temp[i*boardColSize+j] = 1;
                }
            }
    }
}
for(int k = 0; k<boardRowSize; k++){ // comparing if there are changes in the new board (temp) and the original board
    for(int l = 0; l<boardColSize; l++){
        if(board[k*boardColSize+l] != temp[k*boardColSize+l]){
            return 0;
        }
    }
}
    return 1;
}
                
                
            


