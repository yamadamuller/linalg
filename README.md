# linalg
A Linear Algebra Toolbox in C

# Compiling the code
In the terminal, access the directory of the operation type you wish to run:
```
cd <desired_directory>
```

Then, compile the algorithm file based on the directory you're working with:

## Main file
```
g++ -o <executable_name> run_linalg.c ./src/rpn_stack.c ./src/linalg.c ./src/visuals.c
```

## Test files
```
g++ -o <executable_name> <test_call_file>.c <utils_file>.c
```
where **<utils_files>.c** can be **../src/linalg.c** and/or **../src/rpn_stack.c**.

Lastly, run the executable file:
```
./<executable_name>
```

# Runtime operations
The toolbox is designed to run in the terminal. Upon executing the compiled file, you'll be greated by the linalg's "pseudo-UI":

[Screencast from 21-10-2025 23:34:18.webm](https://github.com/user-attachments/assets/773ba1c3-8282-45a1-9e6b-a041289c162d)

Then, type a matrix operation you would like to compute. The toolbox implements a stack-based routine, more specifically, the RPN notation. 

Then, type a matrix operation you would like to compute. The toolbox implements a stack-based routine, more specifically, the RPN notation. For example, the sum of two matrices "A+B" should be defined as "AB+". The available operations are as follows:

- '*' : multiplication of a matrix by a constant;
- '+' : sum of two matrices;
- '-' : subtraction of two matrices;
- '.' : inner product of two vectors;
- '@' : multiplication of two matrices;
- 'T' : transpose of a vector/matrix;
- '^' : inverse of a matrix;
- '|' : norm of a vector.

**Note**: Uppercase letters are interpreted as arrays/matrices, whereas lowercase ones are interpreted as constants!
 
