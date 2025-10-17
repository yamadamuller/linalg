#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int rows, cols;
    double **A; //pre-defined pointers that will be assigned to matrices/arrays
    double vn; //variable to store the inner product output

    //Define matrices' parameters in runtime
    printf("Number of rows of A: ");
    scanf("%d", &rows); 
    printf("Number of columns of A: ");
    scanf("%d", &cols); 
    A = dinamic_array(A, rows, cols); //update the matrix given the dinamic array from runtime
    struct MatrixData A_data = {A, rows, cols, 0}; //matrix data struct

    //Compute the vn = sqrt(A_{0}² + A_{1}² + ... + A_{n}²)
    vn = norm(A_data);
    printf("%f \n", vn); //print the dinamic array
    
    free_alloc_memory(A_data); //free allocated memory
}