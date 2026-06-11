# small-machine-language (SML)
Small stack machine for interpreting an assembly-like instruction set.

## Program Design 

### Background

This program was first written in Java and this repository is an example of the same program in C++ totally re-written.

### Execution

The program receives an `.sml` file as input. It reads and translates this to methods. Each method creates a _Frame_. This is the basic unit of the stack machine. Each frame is used to store:
1. method arguments and local variables
2. operands of the instructions stored in the _operand stack_.
3. the value of the _program counter_ - indicating the next instruction to be executed within the method.

### Repo design

    /sml
        | -- main.cpp
        | ...
        /lib
            | -- Instructions.h
            | -- Interpreter.h
            | -- Method.h
            | -- SMLInterpreter.h

## Program Design
Here is the complete transcription and clean Markdown formatting of the SML Grammar Reference document from **image_1d021f.jpg**:

---

# SML Grammar Reference

### Legend

* **Keywords / Instructions**
* **Literals / Identifiers**
* **Metasyntax** (`()` = grouping, `|` = alternative, `*` = zero-or-more, `?` = optional)

---

## TOP-LEVEL STRUCTURE

```text
program             →  ( method-def )*

method-def          →  method-header instruction-line*

method-header       →  @name ( param )*
                       e.g., @fib: n  or  @gcd: a b  or  @main:

instruction-line    →  ( label )? : instruction

label               →  label_name
                       e.g., L1, L27, L_done — must appear alone on its line before the instruction

```

---

## INSTRUCTIONS — OPERAND STACK EFFECTS

| Instruction | Syntax            | Stack: before → after                                            |
| --- |-------------------|------------------------------------------------------------------|
| **push** | `push int`        | `... → ... int`                                                  |
| **pop** | `pop`             | `... a → ...`                                                    |
| **load** | `load v`          | `... → ... symtab(ident)`                                        |
| **store** | `store v`         | `... a → ...` *(writes a → SymbolTable(ident))*                  |
| **add** | `add`             | `... a b → ... (a+b)`                                            |
| **sub** | `sub`             | `... a b → ... (a-b)`                                            |
| **mul** | `mul`             | `... a b → ... (a×b)`                                            |
| **div** | `div`             | `... a b → ... (a/b)` *Integer division; throws on b=0*          |
| **print** `[i/o]` | `print`           | `... a → ...` *(pops and prints a to stdout)*                    |
| **if_cmpgt** `[cmp]` | `if_cmpgt label`  | `... a b → ...` *jump if a > b*                                  |
| **if_cmplt** `[cmp]` | `if_cmplt label`  | `... a b → ...` *jump if a < b*                                  |
| **if_cmpgte** `[cmp]` | `if_cmpgte label` | `... a b → ...` *jump if a ≥ b*                                  |
| **if_cmplte** `[cmp]` | `if_cmplte label` | `... a b → ...` *jump if a ≤ b*                                  |
| **goto** `[ctrl]` | `goto label`      | `... → ...` *unconditional jump; no stack effect*                |
| **invoke** `[ctrl]` | `invoke @name`    | `... argN ... arg1 →` *(new frame; params bound in order)*       |
| **return** `[ctrl]` | `return`          | `... v? →` *(caller gets v pushed if present; 0 if stack empty)* |

---

## OPERAND GRAMMAR

```text
int                 →  [-]? [0-9]+

ident               →  [a-zA-Z_][a-zA-Z0-9_]*
                       used for variable names, parameter names, and label targets

method-ref          →  @ident
                       the @ prefix is stripped by InvokeInstr before lookup

label               →  L[a-zA-Z0-9_]+
                       convention: L prefix; any alphanumeric suffix is valid

```

---

## ARGUMENTS ORDER ON INVOKE

> Arguments are pushed left-to-right before `invoke`, then popped and bound right-to-left so that the first parameter receives the first pushed value. For `@gcd: a b`, push `a` first then `b`; `InvokeInstr` pops `b` then `a` and stores them to match the parameter list in reverse.

---


### Test Inputs

In the `/tests` directory are test input programs for the SML Interpreter. 

1. `test1_fibRec.sml` - evaluates the n-th fibonacci number sequence via recursion.
2. `test2_fib.` - does the same as 1 with iteration.
3. `test3_factorial.sml` - evaluates the factorial of a given number.
4. `test4_collatz.sml` - evaluates how many steps needed following the Collatz sequence from one greater number to another.
5. `test5_isqrt` - evaluates the integer sqrt of a number.
6. `test6_gcd` - Euclidean algorithm to determine the greatest common denominator between two numbers.

<!-----links-here->

[0]:https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html