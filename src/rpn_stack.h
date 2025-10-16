#ifndef RPN_STACK_H
#define RPN_STACK_H
#define STACK_SIZE 10

struct RPNStack{
    char stack[STACK_SIZE]; //array that functions as the stack
    int top; //stack size
};

void push(struct RPNStack *stack_struct, char input); //function that pushes into the stack
char pop(struct RPNStack *stack_struct); //function that pops form the stack

#endif