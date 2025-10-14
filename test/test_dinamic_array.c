#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int rows, cols, i;
    double **A;

    //Define matrix parameters in runtime
    printf("Number of rows of A: ");
    scanf("%d", &rows); 
    printf("Number of columns of A: ");
    scanf("%d", &cols); 
    A = dinamic_array(A, rows, cols); //update the matrix given the dinamic array from runtime
    print(A, rows, cols); //print the dinamic array
}
