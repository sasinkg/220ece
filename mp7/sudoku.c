#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

/*
*dhruvv2, sasinkg2, akshay5
*In this mp the first couple of function were quite easy to solve
*They were essentially searching for a value in a given row or column
*The 3x3 function was the same except I had to use a nested for loop to search for the value
*I had some problem with the is_val_valid function because I was using nested if statements instead of individual ones
*After I figured that out that I actually finished the mp because that was the last problem that I had
*With the solve_sudoku function I was initially confused about the if statement at the beginning because I didn't know what conditional could go in there
*That's when I decided to use another function that would check if the sudoku array was complete and return a boolean value to fit in that if statement
*For the else I also didn't know how to get the i and j values out of the nested loop because the loop would inevitably run to the end only giving me the i and j of the final 0
*That's where I found goto and I used that to allow me to break out of the nested loop
*After that I followed the psuedocode given to us and that was it
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  for(int j = 0; j<9; j++){ // for all cols, b/c to search through the entire row you need to increment j
    if(sudoku[i][j] == val){ // if you find val
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO

  for(int i = 0; i<9; i++){ // for all rows, b/c to search through the entire col you need to increment  i
    if(sudoku[i][j] == val){ // if you find val
      return 1; 
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  assert(j>=0 && j<9);

  int row = i;
  int col = j;
  if(i==1||i==2){ // setting row to the start of the corresponding 3x3 zone
    row = 0;
  }
  if(i==4||i==5){
    row = 3;
  }
  if(i==7||i==8){
    row = 6;
  }
  
  if(j==1||j==2){ // setting col to the start of the 3x3 zone
    col = 0;
  }
  if(j==4||j==5){
    col = 3;
  }
  if(j==7||j==8){
    col = 6;
  } 

  for(int o = row; o<=row+2; o++){ // for all the rows in the 3x3 zone
    for(int p = col; p<=col+2; p++){ // for all the cols in the 3x3 zone
      if(sudoku[o][p] == val){ // if you find val
        return 1; 
      }
    }
  }  
  
  return 0; // if val can be put in the 3x3 zone
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val, i, sudoku) == 1){ // function returns 1 if val isn't valid in row
    return 0; // b/c we want to return true only when val is valid at i,j
  }
  if(is_val_in_col(val, j, sudoku) == 1){
    return 0;
  }
  if(is_val_in_3x3_zone(val, i, j, sudoku) == 1){
    return 0;
  }
  return 1; // reaches this step only after it is valid at row, col, and 3x3 zone
  // END TODO
}

bool is_complete(int sudoku[9][9]){ // new function to return a boolean value if the sudoku is filled 
  for(int i = 0; i<9; i++){
    for(int j = 0; j<9; j++){
      if(sudoku[i][j] == 0){ // if you find any element that's empty
        return false; // return false if sudoku isn't full
      }
    }
  }
  return true; // return true if the sudoku has all elements filled
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j;
  if(is_complete(sudoku)){ // if the sudoku is already complete
    return 1;
  }
  else{
    for(int o = 0; o<9; o++){
      for(int p = 0; p<9; p++){
        if(sudoku[o][p] == 0){ // if empty
          i = o; 
          j = p;
          goto nextstep; // break out of loops
        }
      }
    }
  }
  nextstep:
  printf("%d and %d\n", i,j);

  for(int num = 1; num<=9; num++){ // shuffling through all valid numbers in sudoku 1--9
    if(is_val_valid(num, i, j, sudoku)){ // if num can even go in (i,j)
      sudoku[i][j] = num; // fill num in (i,j)
      if(solve_sudoku(sudoku)){ // recursive call to try and fill the entire sudoku with num in (i,j)
        return 1;
      }
      sudoku[i][j] = 0; // if filling num in (i,j) doesn't reach the solution set it back to 0 and move to the next num
    }
  }

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
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






