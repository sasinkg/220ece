#include <stdio.h>
#include <stdlib.h>
/*  partners: dhruvv2, akshay5 

    this lab wasn't too hard because we just had to implement the equation that we received in the instructions. */

int main()
{
    int row;
    
    printf("Enter a row index: "); /* output to user */
    scanf("%d", &row); /* input number */
    unsigned long coeff; /* define coeff which determins the contents of the row */
    int n = row; /* define row */
    int k = 0; /* row counter */
    while(k<n+1) 
    {
            coeff = 1;
            printf("%ld ", coeff);
            k++;
            
            for(int i = 1; i<n+1; i++)
            {
	      coeff *=(n+1-k); /* equation for coeff */
                coeff /=k;
                printf("%ld ", coeff);
                k++;
            }
            
    }

    return 0;
}


