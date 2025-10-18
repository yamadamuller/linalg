#include <stdbool.h>
#include "linalg.h"

#ifndef RPN_STACK_H
#define RPN_STACK_H
#define STACK_SIZE 10
#define NUM_RPNOPS 8

struct RPNStack{
    struct MatrixData stack[STACK_SIZE]; //array that functions as the stack
    int top; //stack size
};

void push(struct RPNStack *stack_struct, struct MatrixData input); //function that pushes into the stack
struct MatrixData pop(struct RPNStack *stack_struct); //function that pops from the stack
bool isempty(struct RPNStack *stack_struct); //function to check if the stack is empty or not
bool isin_sorted(char target, char A[], int len); //function that checks if a char exist in the available ops array (sorted)
void compute_by_rpn(struct RPNStack *stack_struct); //function that triggers the linalg operation
void switch_operator(struct RPNStack *stack_struct, char oprtr, bool rep_flag); //switch logic to define with operation will be computed

#endif