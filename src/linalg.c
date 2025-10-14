#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** dinamic_array(double** A, int m, int n){
    /*
        :param A: pointer to the array/matrix in memory
        :param m: number of rows
        :param n: number of columns
    */

    //Allocate memory for the dinamic array
    A = (double**) malloc(m * sizeof *A); //row-based allocation (size of a double)
    for(int i=0; i<m; i++){
        A[i] = (double*) malloc(n * sizeof *A); //column-based allocation
    }

    //Fill the array from the user's input
    for (int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
        
        printf("\n"); //breaks at the end of each row
    }

    return A;
}

void print(double** A, int m, int n){
    /*
        :param A: pointer to the array/matrix in memory
        :param m: number of rows
        :param n: number of columns
    */

    printf("[ \n"); //add brackets 
    for (int i=0; i<m; i++){
        printf("["); //add brackets
        for(int j=0; j<n; j++){
            printf("%lf", *(&A[i][j]));

            //Handle display style
            if(j==n-1){
                printf("]");
            }
            else{
                printf(" ");
            }
        }

        printf("\n"); 
    }

    printf("] \n");
}
