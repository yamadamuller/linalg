#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int mtxs, rows, cols, i;
    double **A, **B, **C, **D, **E; //pre-defined pointers that will be assigned to matrices/arrays
    double **(ptrs)[MAX_MTX_AVAILABLE] = {A, B, C, D, E}; //array that will store the pointers
    char ids[MAX_MTX_AVAILABLE] = {'A', 'B', 'C', 'D', 'E'}; //array that will store the assigned ids

    //Define how many matrices must be created in runtime                                        
    printf("Number of arrays/matrices: ");
    scanf("%d", &mtxs);
    if(mtxs > MAX_MTX_AVAILABLE){
        printf("[linalg] Linalg only supports up to %d simultaneous matrices! \n", MAX_MTX_AVAILABLE);
        mtxs = -1; //sets mtxs to 0
    }
    else{
        int rem_ptrs = MAX_MTX_AVAILABLE - mtxs; //register how many pointers will be set to zero (max - input)
        for (int rem=MAX_MTX_AVAILABLE-rem_ptrs; rem<MAX_MTX_AVAILABLE; rem++){
            ptrs[rem] = NULL; //set the pointer to NULL
            printf("%d \n", rem);
        }
    }

    //Define matrices' parameters in runtime
    for (int i=0; i<mtxs; i++){
        printf("Number of rows of %c: ", ids[i]);
        scanf("%d", &rows); 
        printf("Number of columns of %c: ", ids[i]);
        scanf("%d", &cols); 
        ptrs[i] = dinamic_array(ptrs[i], rows, cols); //update the matrix given the dinamic array from runtime
        struct MatrixData curr_A_data = {ptrs[i], rows, cols}; //matrix data struct
        print(curr_A_data); //print the dinamic array
        free_alloc_memory(curr_A_data); //free allocated memory
    }
}
