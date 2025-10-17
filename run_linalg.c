#include "./src/rpn_stack.h"
#include "./src/linalg.h"
#include "./src/visuals.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    generate_header(); //generate header
    struct RPNStack op_stack; //initialize the stack struct
    compute_by_rpn(&op_stack); //run the toolbox
}