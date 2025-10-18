#include "rpn_stack.h"
#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

char available_ops[NUM_RPNOPS] = {'*', '+', '-', '.', '@', 'T', '^', '|'}; //list of possible operations in the linalg framework

void push(struct RPNStack *stack_struct, struct MatrixData input){
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

struct MatrixData pop(struct RPNStack *stack_struct){
    /*
        :param stack_struct: struct with the stack data (stack+top)
    */

    //Check stack occupation
    bool stack_occ = isempty(stack_struct);
    if(stack_occ){
        fprintf(stderr, "[rpn_stack.pop] Stack is empty!");
    }

    //Pop operation
    struct MatrixData top_value = stack_struct->stack[stack_struct->top-1]; //pop the value at the top
    stack_struct->top--; //decrease the "top" counter

    return top_value;
}

bool isempty(struct RPNStack *stack_struct){
    /*
        :param stack_struct: struct with the stack data (stack+top)
    */
    
    //Check stack occupation
    if(stack_struct->top==0){
        return true;
    }
    else{
        return false;
    }
}

bool isin_sorted(char target, char A[], int len){
    /*
        :param target: the character to be defined if it exists in the array
        :param A: the array with the occurances to search from (assumed to be sorted)
        :param len: the length of the occurances array
    */

    //Binary search algorithm
    int lower = 0; //lower bound of the search
    int upper = len-1; //upper bound of the search
    while(1){
        if(lower>upper){
            return false; 
        }

        int mid = floor((lower+upper)/2); //find the middle of the array
        
        if(A[mid]<target){
            lower = mid+1; //update lower limit
        }
        else if(A[mid]>target){
            upper = mid-1; //update upper limit
        }
        else{
            break; //break the loop if target occurs
        }
    }

    return true; 
}

void compute_by_rpn(struct RPNStack *stack_struct){
    /*
        :param stack_struct: struct with the stack data (stack+top)
    */

    stack_struct->top = 0; //set the top index of the stack to zero

    //Declare the RPN operation in runtime
    char* mtx_op = (char*) malloc((int) STACK_SIZE * sizeof(char)); //alloc maximun accepted characters to the operation string 
    printf("\n");
    printf("Matrix operation (RPN): ");
    scanf("%[^\n]", mtx_op); //scan all digits (except white space)
    int len_input = strlen(mtx_op); //store the length of the input string

    //Stack-based computation 
    extern char available_ops[NUM_RPNOPS]; //available operations
    int len_ops = sizeof(available_ops)/sizeof(available_ops[0]); //length of the operations array
    char curr_char, last_char; //variable to monitor operation characters 
    int rows, cols; //variables to store the shape of each incoming operand
    double cnt; //constant multiplication variable (special case)
    bool op_or_mtx; //variable to check if incoming char is operation or operand
    bool repeated_flag = false; //flag to monitor if the arrays/matrices are repeated
    double **oprnd, **B, **C; //pre-defined pointers that will be assigned to matrices/arrays 
    for(int i=0; i<len_input; i++){
        curr_char = mtx_op[i]; //update the incoming character of the operation string
        op_or_mtx = isin_sorted(curr_char, available_ops, len_ops); //check if operation or operand given the array of possible operations
        if(!op_or_mtx){
            //incoming character is an operand
            //OBS: lower-case is interpreted as constants and upper-case as arrays/matrices
            if(isupper(curr_char)){
                if(curr_char!=last_char){
                    printf("Number of rows of %c: ", curr_char);
                    scanf("%d", &rows); 
                    printf("Number of columns of %c: ", curr_char);
                    scanf("%d", &cols);
                    oprnd = dinamic_array(oprnd, rows, cols); //update the matrix given the dinamic array from runtime 
                    struct MatrixData in_oprnd = {oprnd, rows, cols, 0}; //matrix data struct for the dinamic input
                    push(stack_struct, in_oprnd); //push the input matrix to the stack
                    last_char = curr_char; //commute variables to update last processed character
                }
                else{
                    struct MatrixData in_oprnd = {oprnd, rows, cols, 0}; //same matrix data struct for the dinamic input
                    push(stack_struct, in_oprnd); //push the last processed matrix to the stack again
                    repeated_flag = true; //update the flag to handle memory operations
                }
            }
            else{
                printf("%c = ", curr_char);
                scanf("%lf", &cnt);
                struct MatrixData in_oper = {NULL, 1, 1, cnt}; //matrix data data struct for the dinamic input with only the constant
                push(stack_struct, in_oper); //push the input matrix to the stack
            }
        }
        else{
            //incoming character is an operator
            switch_operator(stack_struct, curr_char, repeated_flag); 
        }
    }

    free(mtx_op); //free the memory space allocated to mtx_op
    oprnd = NULL;
    curr_char = '\0';
    last_char = '\0';
    stack_struct = NULL; //point the struct to NULL
}

void switch_operator(struct RPNStack *stack_struct, char oprtr, bool rep_flag){
    /*
        :param stack_struct: struct with the stack data (stack+top)
        :param oprtr: the character with the operator symbol
        :param rep_flag: flag to monitor if the arrays/matrices are repeated
    */

    struct MatrixData left_oper, right_oper; //operand structs
    double **B, **C; //pre-defined pointers that will be assigned to matrices/arrays 

    switch(oprtr){
        //B = c.A
        case('*'):{
            right_oper = pop(stack_struct); //the matrix A
            left_oper = pop(stack_struct); //the constant c
            B = matcmul(right_oper, left_oper.c); //compute the multiplication by a constant
            struct MatrixData output = {B, right_oper.m, right_oper.n, left_oper.c}; //output matrix data struct
            print(output); //print the output

            //free allocated memory
            free_alloc_memory(right_oper); 
            free_alloc_memory(output);
            C = NULL; //update unused **C pointer
            break;
        }

        //C = A+B
        case('+'):{
            right_oper = pop(stack_struct); //the matrix B
            left_oper = pop(stack_struct); //the matrix A
            C = matsum(left_oper, right_oper); //compute the sum of two matrices
            struct MatrixData output = {C, right_oper.m, right_oper.n, 0}; //output matrix data struct
            print(output); //print the output

            //free allocated memory
            if(!rep_flag){
                free_alloc_memory(left_oper);
            }
            free_alloc_memory(right_oper); 
            free_alloc_memory(output);
            break;
        }

        //C = A-B
        case('-'):{
            right_oper = pop(stack_struct); //the matrix B
            left_oper = pop(stack_struct); //the matrix A
            C = matsub(left_oper, right_oper); //compute the subraction of two matrices
            struct MatrixData output = {C, right_oper.m, right_oper.n, 0}; //output matrix data struct
            print(output); //print the output
            
            //free allocated memory
            if(!rep_flag){
                free_alloc_memory(left_oper);
            }
            free_alloc_memory(right_oper); 
            free_alloc_memory(output);
            break;
        }

        //ip = sum_{i}^{0, n-1} A_{i}.B_{i}
        case('.'): {
            right_oper = pop(stack_struct); //the vector B
            left_oper = pop(stack_struct); //the vector A
            double output = inner(left_oper, right_oper); //compute the inner product of two vectors
            printf("%f \n", output); //print the output

            //free allocated memory
            if(!rep_flag){
                free_alloc_memory(left_oper);
            }
            free_alloc_memory(right_oper); 
            B = NULL; //update unused **B pointer
            C = NULL; //update unused **C pointer
            break;
        }

        //C=A@B
        case('@'):{
            right_oper = pop(stack_struct); //the matrix B
            left_oper = pop(stack_struct); //the matrix A
            C = matmul(left_oper, right_oper); //compute the multiplication of two matrices
            struct MatrixData output = {C, left_oper.m, right_oper.n, 0}; //output matrix data struct
            print(output); //print the output
            
            //free allocated memory
            if(!rep_flag){
                free_alloc_memory(left_oper);
            }
            free_alloc_memory(right_oper); 
            free_alloc_memory(output);
            break;
        }

        //norm = sqrt(A_{0}² + A_{1}² + ... + A_{n}²)
        case('|'): {
            left_oper = pop(stack_struct); //the vector A
            double output = norm(left_oper); //compute the norm of a vector
            printf("%f \n", output); //print the output

            //free allocated memory
            free_alloc_memory(left_oper);
            B = NULL; //update unused **B pointer
            C = NULL; //update unused **C pointer
            break;
        }
    }
}