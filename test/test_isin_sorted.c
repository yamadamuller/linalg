#include "../src/rpn_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

int main(){
    extern char available_ops[NUM_RPNOPS]; //external operations array
    int len = sizeof(available_ops)/sizeof(available_ops[0]); //length of the array
    char target_op = '@'; //operation to find
    bool target_isin = isin_sorted(target_op, available_ops, len); //check if target is among the available operations
    printf("%d \n", target_isin);
} 