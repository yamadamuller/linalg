#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double A[5] = {11, 5, 12, 21, 7}; //array with random pre-assigned numbers
    int len = sizeof(A)/sizeof(A[0]);
    int idx_max = argmax(A, len);
    printf("Max = %f at idx = %d \n", A[idx_max], idx_max);
}