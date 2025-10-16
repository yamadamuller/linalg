#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

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
    for(int i=0; i<m; i++){
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
    for(int i=0; i<A.m; i++){
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
    for(int i=0; i<A.m; ++i) {
        free(A.mtx[i]); //free the blocks allocated per-row
    }
    free(A.mtx); //free the whole allocated block
    A.mtx = NULL; //set the pointer to null
}

int argmax(double A[], int len){
    /*
        :param A: array with all the candidate values 
        :param len: the lenght of the array
        :return the index of the maximun value in the array (first occurance)
    */
    
    double max_value = -DBL_MAX; //variable to store the maximum value through the iterations
    int idx_max = 0; //variable to store the index of the maximum value through the iterations
    for(int i=0; i<len; i++){
        if(A[i]>max_value){
            max_value = A[i]; //commute variables
            idx_max = i; //update the argmax
        }
    }

    return idx_max;
}

double inner(struct MatrixData A, struct MatrixData B){
    /*
        :param A: pointer to the first array/matrix in memory
        :param B: pointer to the second array/matrix in memory
        :return A.B
    */

    double vw; //variable that stores the inner product output

    //Check first if both A and B are vectors of the same shape
    if((A.m==B.m)&(A.n==B.n)){ 
        
        //Check if both inputs are vectors and not matrices
        if(!(A.m==1)&&!(A.n==1)){
            fprintf(stderr, "[linalg.inner] A must be a vector mx1 or 1xm! \n");
            vw = -1; //placeholder value for incomplete operation
            return vw;
        }
        else if(!(B.m==1)&&!(B.n==1))
        {
            fprintf(stderr, "[linalg.inner] B must be a vector mx1 or 1xm! \n");
            vw = -1; //placeholder value for incomplete operation
            return vw;
        }
        else{
            //Compute the inner product
            double shape[2] = {(double) A.m, (double) A.n}; //array to help in detecting if the array is a row or column vector
            int max_dim = argmax(shape, 2); //find which dimension will be iterated over

            //TODO: add the transpose once it is implemented, as inner product for 1xm arrays do not work yet!

            for(int i=0; i<(int)shape[max_dim]; i++){
                vw += (*(A.mtx[i])) * (*(B.mtx[i])); //vw = sum_{i}^{0, n-1} v_{i}.w_{i} 
            }

            return vw;
        }
    } 
    else{
        fprintf(stderr, "[linalg.inner] A and B must have the same dimensions! \n");
        vw = -1; //placeholder value for incomplete operation
        return vw;
    }
}

double** matsum(struct MatrixData A, struct MatrixData B){
    /*
        :param A: pointer to the first array/matrix in memory
        :param B: pointer to the second array/matrix in memory
        :return C=A+B
    */

    //Check first if both A and B are vectors of the same shape
    if((A.m==B.m)&(A.n==B.n)){
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
        fprintf(stderr, "[linalg.matsum] A and B must have the same dimensions! \n");
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

    if((A.m==B.m)&(A.n==B.n)){ //A and B must have the same dimensions to sum
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
        fprintf(stderr, "[linalg.matsub] A and B must have the same dimensions! \n");
        double** C = NULL;
        return C;
    }
}

double** matcmul(struct MatrixData A, double c){
    /*
    :param A: pointer to the first array/matrix in memory
    :param c: the constant that will multiply every element of the array/matrix
    :return B = c.A
    */

    //Allocate memory for the dinamic output array
    double** B; //output array
    B = (double**) malloc(A.m * sizeof *B); //row-based allocation (size of a double array)
    for(int i=0; i<A.m; i++){
        B[i] = (double*) malloc(A.n * sizeof *B); //column based allocation 
    }

    //Compute the multiplication by a constant
    for(int i=0; i<A.m; i++){
        for(int j=0; j<A.n; j++){
            B[i][j] = c * *(&A.mtx[i][j]); //B[i,j] = c.A[i,j]
        }
    }

    return B;
}
