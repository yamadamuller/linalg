#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int rows, cols;
    double **A, **B, **C; //pre-defined pointers that will be assigned to matrices/arrays

    //Define matrices' parameters in runtime
    printf("Number of rows of A: ");
    scanf("%d", &rows); 
    printf("Number of columns of A: ");
    scanf("%d", &cols); 
    A = dinamic_array(A, rows, cols); //update the matrix given the dinamic array from runtime
    struct MatrixData A_data = {A, rows, cols, 0}; //matrix data struct

    printf("Number of rows of B: ");
    scanf("%d", &rows); 
    printf("Number of columns of B: ");
    scanf("%d", &cols); 
    B = dinamic_array(B, rows, cols); //update the matrix given the dinamic array from runtime
    struct MatrixData B_data = {B, rows, cols, 0}; //matrix data struct

    //Compute the sum A + B
    C = matmul(A_data, B_data);
    struct MatrixData C_data = {C, A_data.m, B_data.n, 0}; //matrix data struct
    print(C_data); //print the dinamic array
    
    free_alloc_memory(A_data); //free allocated memory
    free_alloc_memory(B_data); //free allocated memory
    free_alloc_memory(C_data); //free allocated memory
}