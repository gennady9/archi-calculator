# Big numbers calculator implemented in C and x86 assembly

# Computer Architecture, Homework 1 specification
## Lecturer: Mayer Goldberg

## Contents

1 Overview 1

2 The format of the input 2

3 What shall be done in C 2

4 What shall be done in assembly language 3

## 1 Overview

In this assignment you shall write a postx-based calculator for integer arith-
metic, somewhat similar to thedcprogram on Unix/Linux (read over the
manpage fordc). The program will be written in a combination of C and
x86/64-bit assembly language.

- The C code shall be compiled to an object les usinggcc.
- The assembly code shall be assembled into an object le usingnasm.
- The object les shall be linked usinggccto produce an executable by
    the name ofcalc.

- This version works
    with arbitrary-precision integers, providing functionality similar to that
    ofbignumsin Scheme,intin Python, orLargeIntegerin Java. You
    might want to use a structure similar to the following:

```
typedef struct bignum {
long number_of_digits;
char *digit;
} bignum;
```
This is the only difference between the two versions. In terms of func-
tionality and interface, the two versions are identical.
Your calculator will implement the following functionality:

- Addition
- Subtraction
- Multiplication
- Division

## 2 The format of the input

The calculator will usepostxnotation for input, and will use apushdown
stackin the implementation.This stack is not the same as the builtin
x86 stack, but a separate data structure that is used only for stor-
ing numbers during a calculation. We suggest you implement this stack
as an array of some reasonable side, no less than 1024. An expression such
as 2 3+4 5 will be entered as2 3 * 4 5 * +. The result (which is 26 in
this case), shall be pushed onto the stack.

## 3 What shall be done in C

- Implement the stack
- Implement the text-based user-interface, supporting the following pos-
    sibilities:

```
a signed integerto be pushed on the stack
∗Positive numbers in base 10 are entered as usual: 1234 , etc.
```

```
∗ Negative numbers inbase 10 are entered with the sign de-
noted by the underscore character (so as not to be confused
with the operation of subtraction:_1234,_1, etc.
 + for addition
 - for subtraction
 * for multiplication
 / for division
 p for printing the result
 c to clear the stack
 q to quit the program and return to the underlying shell
```
- The user-interface will then call routines written in assembly code to
    perform the various arithmetic functions.

## 4 What shall be done in assembly language

The four operations shall be implemented in x86/64-bit assembly language,
using the linux calling conventions. It will be easiest for you to implement
these functions to operate directly on thepushdown stack.
Example:To compute 2 * 3+ 4 * 5 , print the result, and quit, we input
2 3 * 4 5 * + p q:

- 2 will be pushed onto the stack
- 3 will be pushed onto the stack
- *will pop the top two elements on the stack, and push their product,
    6, back onto the stack
- 4 will be pushed onto the stack
- 5 will be pushed onto the stack
- *will pop the top two elements on the stack, and push their product,
    20, back onto the stack
- +will pop the top two elements on the stack, and push their sum, 26,
    onto the stack
- pwill print the result in base 10 (decimal)


- qwill quit the program and return to the underlying shell

Your program should treat allwhitespace(characters less than or equal to
ASCII 32) as delimiters, and use them to separatetokens. Space is optional
anywhere other than between two numbers. So2 3 * 4 5 * +could also
have been written as2 3*4 5*+.
