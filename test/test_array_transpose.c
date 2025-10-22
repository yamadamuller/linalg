#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int rows, cols;
    double **A, **A_t; //pre-defined pointers that will be assigned to matrices/arrays

    //Define matrices' parameters in runtime
    printf("Number of rows of A: ");
    scanf("%d", &rows); 
    printf("Number of columns of A: ");
    scanf("%d", &cols); 
    A = dinamic_array(A, rows, cols); //update the matrix given the dinamic array from runtime
    struct MatrixData A_data = {A, rows, cols, 0}; //matrix data struct

    //Compute the transpose
    A_t = transpose(A_data);
    struct MatrixData At_data = {A_t, cols, rows, 0}; //transpose data struct
    print(At_data);

    free_alloc_memory(A_data); //free allocated memory
    free_alloc_memory(At_data); //free allocated memory
}