#ifndef LINALG_H
#define LINALG_H
#define MAX_MTX_AVAILABLE 5

struct MatrixData
{
    double** mtx; //the array/matrix dinamically generated
    int m; //the number of rows
    int n; //the number of columns
    double c; //placeholder constant
};


double** dinamic_array(double** A, int m, int n); //function to create a random array dinamically in runtime
void print(struct MatrixData A); //function to print the computed arrays/matrices
void free_alloc_memory(struct MatrixData A); //function to free the allocated memory to the dinamic array
int argmax(double A[], int len); //function to return the index of the maximum value in an array
double inner(struct MatrixData A, struct MatrixData B); //function to compute the inner product between two vectors
double norm(struct MatrixData A); //function to compute the norm of a vector
double** matsum(struct MatrixData A, struct MatrixData B); //function to sum two matrices
double** matsub(struct MatrixData A, struct MatrixData B); //function to subtract two matrices
double** matcmul(struct MatrixData A, double c); //function to multiply a matrix by a constant

#endif