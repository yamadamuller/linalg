#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows, cols;
    double **A, **L, **U, **B; //pre-defined pointers that will be assigned to matrices/arrays

    //Define matrices' parameters in runtime
    printf("Number of rows of A: ");
    scanf("%d", &rows); 
    printf("Number of columns of A: ");
    scanf("%d", &cols); 
    A = dinamic_array(A, rows, cols); //update the matrix given the dinamic array from runtime
    struct MatrixData A_data = {A, rows, cols, 0}; //matrix data struct
    printf("A = \n");
    print(A_data);

    //Compute L and U
    struct MatrixData *lu_data = sqr_lu(A_data, 1e-6); //square LU factorization without row exchange
    if(lu_data!=NULL){
        printf("\n");
        printf("L = \n");
        print(lu_data[0]);
        printf("\n");
        printf("U = \n");
        print(lu_data[1]);
        printf("\n");

        //Compute LU = A
        B = matmul(lu_data[0], lu_data[1]);
        struct MatrixData B_data = {B, lu_data[0].m, lu_data[1].n, 0}; //matrix data struct
        printf("\n");
        printf("LU = \n");
        print(B_data); //print the dinamic array

        free_alloc_memory(A_data); //free allocated memory
        free_alloc_memory(lu_data[0]); //free allocated memory
        free_alloc_memory(lu_data[1]); //free allocated memory
        free(lu_data); //free allocated memory
        free_alloc_memory(B_data); //free allocated memory
    }
}