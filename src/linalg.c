#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** dinamic_array(double** A, int m, int n){
    /*
        :param A: pointer to the array/matrix in memory
        :param m: number of rows
        :param n: number of columns
        :return the dinamic array generated with the runtime specs
    */

    //Allocate memory for the dinamic array
    A = (double**) malloc(m * sizeof *A); //row-based allocation (size of a double)
    for(int i=0; i<m; i++){
        A[i] = (double*) malloc(n * sizeof *A); //column-based allocation
    }

    //Fill the array from the user's input
    for (int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\n"); //break the line once done filling

    return A;
}

void print(struct MatrixData A){
    /*
        :param A: array/matrix struct in memory
    */
    printf("[ \n"); //add brackets 
    for (int i=0; i<A.m; i++){
        printf("["); //add brackets
        for(int j=0; j<A.n; j++){
            printf("%lf", *(&A.mtx[i][j]));

            //Handle display style
            if(j==A.n-1){
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

void free_alloc_memory(struct MatrixData A){
    /*
        :param A: array/matrix struct in memory
        :param m: number of rows
    */

    //Free the memory allocated for A
    for (int i=0; i<A.m; ++i) {
        free(A.mtx[i]); //free the blocks allocated per-row
    }
    free(A.mtx); //free the whole allocated block
    A.mtx = NULL; //set the pointer to null
}

double** matsum(struct MatrixData A, struct MatrixData B){
    /*
        :param A: pointer to the first array/matrix in memory
        :param B: pointer to the second array/matrix in memory
        :return C=A+B
    */
    if ((A.m==B.m)&(A.n==B.n)){ //A and B must have the same dimensions to sum
        //Allocate memory for the dinamic array
        double **C; //output matrix
        C = (double**) malloc(A.m * sizeof *C); //row-based allocation (size of a double)
        for(int i=0; i<A.m; i++){
            C[i] = (double*) malloc(B.n * sizeof *C); //column-based allocation
        }
        
        //Compute the sum
        for(int i=0; i<A.m; i++){
            for(int j=0; j<A.n; j++){
                C[i][j] = *(&A.mtx[i][j]) + *(&B.mtx[i][j]); //C[i,j]=A[i,j]+B[i,j]
            }
        }

        return C;
    } 
    else{
        printf("[linalg.matsum] A and B must have the same dimensions!");
        double** C = NULL;
        return C;
    }
}

double** matsub(struct MatrixData A, struct MatrixData B){
    /*
        :param A: pointer to the first array/matrix in memory
        :param B: pointer to the second array/matrix in memory
        :return C=A-B
    */
    if ((A.m==B.m)&(A.n==B.n)){ //A and B must have the same dimensions to sum
        //Allocate memory for the dinamic array
        double **C; //output matrix
        C = (double**) malloc(A.m * sizeof *C); //row-based allocation (size of a double)
        for(int i=0; i<A.m; i++){
            C[i] = (double*) malloc(B.n * sizeof *C); //column-based allocation
        }
        
        //Compute the sum
        for(int i=0; i<A.m; i++){
            for(int j=0; j<A.n; j++){
                C[i][j] = *(&A.mtx[i][j]) - *(&B.mtx[i][j]); //C[i,j]=A[i,j]-B[i,j]
            }
        }

        return C;
    } 
    else{
        printf("[linalg.matsub] A and B must have the same dimensions!");
        double** C = NULL;
        return C;
    }
}