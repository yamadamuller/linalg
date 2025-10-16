#include "../src/rpn_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    struct RPNStack op_stack; //initialize the stack struct
    op_stack.top = 0; //set the top index to zero
    
    //Push random characters to the stack
    push(&op_stack, '0');
    push(&op_stack, '2');
    push(&op_stack, '4');
    push(&op_stack, 'Y');
    push(&op_stack, 'M');

    //iterate over the stack to print the characters in top-down order
    int iter_stack = op_stack.top; //store the stack top before pushing and reducing it
    for(int i=0; i<iter_stack; i++){
        printf("[p.%d] %c \n", i, pop(&op_stack));
    }
}
