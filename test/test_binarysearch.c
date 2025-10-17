#include "../src/rpn_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int main(){
    int available_ops[101] = {0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,
                              13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
                              26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,
                              39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,
                              52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,
                              65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,
                              78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,
                              91,  92,  93,  94,  95,  96,  97,  98,  99, 100};
    int len = sizeof(available_ops)/sizeof(available_ops[0]);
    int target_op = 21; //operation to find
    
    //brute force search
    clock_t start = clock();
    for(int i=0; i<len; i++){
        if(target_op==available_ops[i]){
            printf("%d found at [%d] \n", target_op, i);
            break;
        }
    }
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("%f \n", seconds);

    //binary search
    int lower = 0; //lower bound of the search
    int upper = len-1; //upper bound of the search
    start = clock();
    while(1){
        if(lower>upper){
            fprintf(stderr, "[rpn_stack.binary_search] Search failed!");
        }

        int mid = floor((lower+upper)/2); //find the middle of the array
        
        if(available_ops[mid]<target_op){
            lower = mid+1; //update lower limit
        }
        else if(available_ops[mid]>target_op){
            upper = mid-1; //update upper limit
        }
        else{
            printf("%d found at [%d] \n", target_op, mid);
            break;
        }
    }
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("%f \n", seconds);
} 