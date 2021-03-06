/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/* partners: sasinkg2 akshay5 dhruvv2
in this project, our logic was basically to set up 3 different loops that check the following:
1 - if the guess is valid 
2 - if the guess is a perfect match
3 - if the guess is misplaced match
and then taking the bits we get (1 is true, 0 is false) and multiplying it by 1000 for perfect and 100 for misplaced and 
adding it together. 

It wasn't that hard to do this MP, however, i think figuring out which data types to use when initializing the 
integers/characters and how to format the arrays in a way that it doesnt print out the wrong index or it doesnt 
take the wrong input in were the hardest part of this MP. Once you get the logic, it made sense, but figuring out 
how to implement it using integers or characters makes it a little harder */

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      // your code here
      printf("set_seed: invalid seed\n");  //random seed
      return 0;
    } else {
        srand(seed);
        return 1;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    guess_number = 1; // initialize guess & max score
    max_score = -1;
    for (int i = 0; i < 4; i++) {
        int random = (rand()%8); // give random seed 
        strcpy(solutions[i],pool[random]);
    }

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
    
    /* Initializing integers*/ 
    int perfectmatch = 0;   
    int misplacedmatch = 0;
    
    /* Check invalid */ 
    char guesses1[10], guesses2[10], guesses3[10], guesses4[10]; // 4 inputs
    if (sscanf (guess_str, "%s%s%s%s", guesses1, guesses2, guesses3, guesses4) !=4) {
        printf("make_guess: invalid guess\n"); // if invalid print this
        return 0;
    } 
    char *guess[4]; //intialize guess variables
    guess[0] = guesses1; // match string to input
    guess[1] = guesses2; 
    guess[2] = guesses3;
    guess[3] = guesses4;
    sscanf(guess_str, "%s %s %s %s", guess[0], guess[1], guess[2], guess[3]);
    int guesscheck[5] = {0,0,0,0,0}; // create array with null value at the end
    int solutioncheck[5] = {0,0,0,0,0};  // one more array to check solutions

    /* Check for Valid Guess */
    for (int i = 0; i < 4; i++) {
        if (is_valid(guess[i]) != 1) {
            printf("make_guess: invalid guess\n"); 
            return 0;
        }
    } 

    /* Check for Perfect Match */
    for (int j = 0; j < 4; j++) {
         if (strcmp(guess[j], solutions[j]) == 0) {
            perfectmatch++; //if true increment score by 1
            guesscheck[j]=1; 
            solutioncheck[j]=1;
        }
    }

    /* Check for Misplaced Match */
    for (int k = 0; k < 4; k++) { // loop 1-4  for  4 guesses
        for (int l = 0; l < 4; l++) { // compare to all 4 diff solutions
            if ((strcmp(guess[k], solutions[l]) == 0 && guesscheck[k] == 0 && solutioncheck[l] == 0)) {
                misplacedmatch++;
                guesscheck[k] = 1;
                solutioncheck[l] = 1; 
            }
        }
    }

    /* score tally code below */ 
    int score = 0;
    score = (perfectmatch*1000 + misplacedmatch*100); // point system: 1000 for perfect, and 100 for misplaced
    if (score > max_score) {
        max_score = score;
    }

    printf("With guess %d, you got %d perfect matches and %d misplaced matches. \n", guess_number, perfectmatch, misplacedmatch);
    printf("Your score is %d and cur max is %d. \n", score, max_score); 

    if (perfectmatch == 4) {
        return 2; // if all guess are correct return 2
    } else {
        guess_number++; // increment because they will have to guess again
        return 1;
    }
}
