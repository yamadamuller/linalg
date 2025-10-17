#include "../src/rpn_stack.h"
#include "../src/linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){
    struct RPNStack op_stack; //initialize the stack struct
    compute_by_rpn(&op_stack); //run the toolbox
}
