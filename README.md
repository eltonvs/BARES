# BARES
[![Build Status](https://travis-ci.org/eltonvs/BARES.svg?branch=master)](https://travis-ci.org/eltonvs/BARES)


## About
BARES is an acronym to **B**asic **AR**ithmetic **E**xpression **E**valuator based on **S**tacks.
He receives a set of expressions from a input file (one by line) and computes all of them, when the expression is valid, returns your result, otherwise returns the error who turned him into a invalid expression with the column where he is (if is applicable).

Is a valid expression when all your terms are `short int` numbers (between -32768 and 32767), binary operators, parenthesis and the unary minus. Which are described on the following table.

### Supported Operators
| Symbol | Operation                         | Precedence Index        |
| :----: | --------------------------------- | :---------------------: |
| __-__  | Minus (Unary and Binary)          | 2 (unary) or 5 (binary) |
| __+__  | Addition                          | 5                       |
| __*__  | Multiplication                    | 4                       |
| __/__  | Division                          | 4                       |
| __%__  | Modulo (Remainder after division) | 4                       |
| __^__  | Exponentiation                    | 3                       |
| __()__ | Parentheses (Break of precedence) | 1                       |


## How it works?
To generate the expression result, this program needs to tokenize all elements, generating a queue with your terms.

After that, this queue of terms (in infix notation) needs to be converted to postfix notation (Reverse Polish Notation - RPN) to eliminate all parentheses (to avoid ambiguity), turning into a computable expression.

With the queue of terms in a postfix notation, a stack is used to make all calculations in right order (pushing and popping elements).


## Supported Errors
**C** is the column where the error was found at first time
 - Numeric constant out of range: column **C**
 - Ill-formed expression or missing term detected: column **C**
 - Invalid operand: column **C**
 - Extraneous symbol: column **C**
 - Mismatch ')': column **C**
 - Lost operator: column **C**
 - Missing closing ')' to match opening '(' at: column **C**
 - Division by zero!
 - Numeric overflow error!


## Compilation and Execution
To compile you just need to run the following commands:
```shell
make clean
make
```

This version will generate a output file with only the error ID. If you wanna see the fully error message, you need to declare the `SHOW_ERROR_MESSAGE` flag as `true`. Like:

```shell
make clean
make SHOW_ERROR_MESSAGE=true
```

Now, to execute:
```shell
./bin/bares input_file [output_file]
```

Where the `input_file` and `output_file` are a plain text file located on `data` folder.

The `output_file` is a optional parameter, so if wasn't specified, the program will print the output on terminal screen.


## Author
This program was fully developed by **Elton de Souza Vieira**
 - [GitHub](https://github.com/eltonvs)
 - [Webpage](http://www.eltonviana.com)


## Contribute
The source files of BARES project are available on [GitHub](https://github.com/marcielleal/BARES).
