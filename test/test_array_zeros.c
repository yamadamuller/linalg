#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    double **Z;
    int rows = 3;
    int cols = 3;
    Z = zeros(rows, cols); //a rows x cols square matrix filled with zeros
    struct MatrixData Z_data = {Z, rows, cols, 0}; //Z data struct
    print(Z_data);
    free_alloc_memory(Z_data);
}