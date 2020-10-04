#include <stdlib.h>
#include <stdio.h>
#include "semiprime.h"
/* partners: sasinkg2 dhruvv2 akshay5 
the first error was in line 26 and line 29 where the return values needed
to be swapped so line 165 returns 0 and line 19 returns 1 so that is_prime
returns the correct value for Print_semiprimes to use. the second error was in
 print_semiprimes (line 47) where k should equal i/j not i%j so that 1 would 
always be returned from is_prime so that semiprimes prints out and not every
number */

/*
    Main function: checks for valid inputs and runs the print_semiprimes function.
    Inputs: none
    Outputs: if provided a,b are invalid, returns -1. If there were no
    semiprimes in the range, returns 0. If there were semiprimes, returns 1.
*/
int main(){
   int a, b, ret;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return -1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return -1;
   }

   ret = print_semiprimes(a, b);
   return ret;
}
