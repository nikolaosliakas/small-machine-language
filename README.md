# small-machine-language (SML)
Small stack machine for interpreting an assembly-like instruction set.

## Program Design 

### Background

This program was first written in Java and this repository is an example of the same program in C++. 

### Execution

The program receives an `.sml` file as input. It reads and translates this to methods. Each method creates a _frame_. This is the basic unit of the stack machine. Each frame is used to store:
1. method arguments and local variables
2. operands of the instructions stored in the _operand stack_.
3. the value of the _program counter_ - indicating the next instruction to be executed within the method.

### Repo design

    /sml
        | -- main.cpp
        | -- Translator.h

## Test Inputs

In the `/tests` directory are two test input programs for the SML. They are two machine language programs for outputing the 
n-th number of the fibonacci sequence. `test1.sml` encodes this recursively; `test2.sml` encodes this iteratively.

<!-----links-here->

[0]:https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html