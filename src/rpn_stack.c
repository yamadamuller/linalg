#include "rpn_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void push(struct RPNStack *stack_struct, char input){
    /*
        :param stack_struct: struct with the stack data (stack+top)
        :param input: char input that will perform RPN operations
    */

    //Check stack occupation
    if(stack_struct->top==STACK_SIZE){
        fprintf(stderr, "[rpn_stack.push] Stack is full!");
    }

    //Push operation
    stack_struct->stack[stack_struct->top] = input; //add the input at "top"
    stack_struct->top++; //increase the "top" counter
}

char pop(struct RPNStack *stack_struct){
    /*
        :param stack_struct: struct with the stack data (stack+top)
    */

    //Check stack occupation
    if(stack_struct->top==0){
        fprintf(stderr, "[rpn_stack.pop] Stack is empty!");
    }

    //Push operation
    char top_value = stack_struct->stack[stack_struct->top-1]; //pop the value at the top
    stack_struct->top--; //decrease the "top" counter

    return top_value;
}