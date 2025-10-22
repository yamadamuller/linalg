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
        :param A: array/matrix A struct in memory
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
        :param A: array/matrix A struct in memory
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
        :param A: array/matrix A struct in memory
        :param B: array/matrix B struct in memory
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

double norm(struct MatrixData A){
    /*
        :param A: array/matrix A struct in memory
        :return ||A||
    */

    double v_norm; //variable that stores the norm output
    
    //check if the input array is indeed a vector
    if(!(A.m==1)&&!(A.n==1)){
            fprintf(stderr, "[linalg.norm] A must be a vector mx1 or 1xm! \n");
            v_norm = -1; //placeholder value for incomplete operation
            return v_norm;
    }
    else{
        v_norm = 0;
        double shape[2] = {(double) A.m, (double) A.n}; //array to help in detecting if the array is a row or column vector
        int max_dim = argmax(shape, 2); //find which dimension will be iterated over
        
        //Compute the squared sum
        for(int i=0; i<(int)shape[max_dim]; i++){
            v_norm += pow(*(A.mtx[i]),2); 
        }

        v_norm = sqrt(v_norm); //||A|| = sqrt(A_{0}² + A_{1}² + ... + A_{n}²)

        return v_norm;
    }
}

double** matsum(struct MatrixData A, struct MatrixData B){
    /*
        :param A: array/matrix A struct in memory
        :param B: array/matrix B struct in memory
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
        :param A: array/matrix A struct in memory
        :param B: array/matrix B struct in memory
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
    :param A: array/matrix A struct in memory
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

double linear_comb(double** A, double** B, int i, int j, int len){
    /*
        :param A: pointer to the first array/matrix in memory
        :param B: pointer to the second array/matrix in memory
        :param i: index of the rows
        :param j: index of the columns
        :param len: length of the arrays
        :return linear combination between vector a and b 
    */
    if(!(A==NULL)&&!(B==NULL)){
        double l_comb = 0; //linear combination output
        for(int e=0; e<len; e++){
            l_comb += *(&A[i][e]) * *(&B[e][j]); //sum_{e=0}^{len-1} a_{i,e}*b_{e,j} 
        }

        return l_comb;
    }
    else{
        fprintf(stderr, "[linalg.linear_comb] At least one array is a NULL pointer! \n");
        return (double) 0;
    }
}

double** matmul(struct MatrixData A, struct MatrixData B){
    /*
        :param A: array/matrix A struct in memory
        :param B: array/matrix B struct in memory
        :return C=A@B
    */
    
    //Check if the operation is possible given the shapes of A and B
    if (!(A.n==B.m)){
        fprintf(stderr, "[linalg.matmul] Shape mismatch between A and B! \n");
        return NULL;
    }
    else{
        //Allocate memory for the dinamic output array/matrix
        double** C; //output array/matrix
        C = (double**) malloc(A.m * sizeof *C); //row-based allocation (size of a double array)
        for(int i=0; i<A.m; i++){
            C[i] = (double*) malloc(B.n * sizeof *C); //column based allocation 
        }

        //Compute the multiplication
        if((A.n!=1)&&(B.m!=1)){
            for(int i=0; i<A.m; i++){
                for(int j=0; j<B.n; j++){
                    C[i][j] = linear_comb(A.mtx, B.mtx, i, j, A.m); //(AB)_{ij} = A[i0:in] * A[0j:nj] 
                }
            }
        }

        //Account for nx1 @ 1xn special case where two vectors result in a nxn matrix
        else{ 
            for(int i=0; i<A.m; i++){
                for(int j=0; j<B.n; j++){
                    C[i][j] = *(&A.mtx[i][0]) * *(&B.mtx[0][j]); //(AB)_{ij} = A[i0:in] * A[0j:nj] 
                }
            }
        }

        return C;
    }
}

double** zeros(int m, int n){
    /*
        :param m: number of rows of the array/matrix filled with zeros
        :param n: number of columns of the array/matrix filled with zeros
        :return A mxn array filled with zeros
    */

    double** Z; //initialize the output pointer
    Z = (double**) malloc(m * sizeof *Z); //row-based allocation (size of a double array)
    for(int i=0; i<m; i++){
        Z[i] = (double*) calloc(n, sizeof *Z); //column based allocation elements filled with 0's
    }

    return Z;
}

struct MatrixData *sqr_lu(struct MatrixData A, double tol){
    /*
        :param A: array/matrix A struct in memory
        :param tol: tolerance of the algorithm
        :return an array with the MatrixData structs of both L (output[0]) and U (output[1])
    */

    if(A.m!=A.n){
        fprintf(stderr, "[linalg.sqr_lu] Input matrix A is not a square matrix! \n");
        return NULL;
    }
    else{
        //Allocate memory for the both L and U matrices and initialize them filled with zero
        double **L = zeros(A.m, A.n); //matrix filled with zeros sized mxn
        double **U = zeros(A.m, A.n); //matrix filled with zeros sized mxn        
        
        //square LU factorization algorithm
        for(int k=0; k<A.n; k++){
            if(*(&A.mtx[k][k])<tol){
                break; //cannot proceed factorization without a row exchange
            }

            //Handle L matrix first
            L[k][k] = 1; //L is a lower traingular matrix with 1's in the main diagonal
            for(int i=k+1; i<A.n; i++){
                L[i][k] = *(&A.mtx[i][k]) / *(&A.mtx[k][k]); //multipliers of column k
                for(int j=k+1; j<A.n; j++){
                    A.mtx[i][j] -= *(&L[i][k]) * *(&A.mtx[k][j]); //Elimination at (i,j) based on L(i,k) -> set A[i][j] to 0!
                } 
            }    

            //Update the pivots once the elimination is computed for each k row
            for(int l=k; l<A.n; l++){
                U[k][l] = *(&A.mtx[k][l]);
            }
        }

        //Generate MatrixData for both L and U
        struct MatrixData L_data = {L, A.m, A.n, 0};
        struct MatrixData U_data = {U, A.m, A.n, 0};
        struct MatrixData *lu_out = (struct MatrixData*) malloc(2 * sizeof(L_data)); //allocate the memory space for the output array
        lu_out[0] = L_data; //store the L matrix in the first element
        lu_out[1] = U_data; //store the U matrix in the second element
        
        return lu_out;
    }
}

double** transpose(struct MatrixData A){
    /*
        :param A: array/matrix A struct in memory
        :return A transpose 
    */

    //Allocate memory for the dinamic output array/matrix
    double** A_t; //output array/matrix
    //A -> mxn / A' -> nxm
    A_t = (double**) malloc(A.n * sizeof *A_t); //row-based allocation (size of a double array)
    for(int i=0; i<A.n; i++){
        A_t[i] = (double*) malloc(A.m * sizeof *A_t); //column based allocation 
    }

    //Compute a'(i,j) = a(j,i)
    if(A.m==1){
        for(int i=0; i<A.n; i++){
            A_t[i][0] = *(&A.mtx[0][i]);
        }
    }
    else if(A.n==1){
        for(int i=0; i<A.m; i++){
            A_t[0][i] = *(&A.mtx[i][0]);
        }
    }
    else{
        for(int i=0; i<A.n; i++){
            for(int j=0; j<A.m; j++){
                A_t[i][j] = *(&A.mtx[j][i]);
            }
        }
    }

    return A_t;
}