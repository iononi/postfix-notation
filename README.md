# Postfix notation
This program simulates a simple calculator. It receives an arithmetic expression given in infix notation
and processes it to get the equivalent postfix notation. After that, the expression is evaluated and the
result is shown. Currently, the program is able to perform operations with one-digit numbers and two-or-more-digit. 
The program is able of printing just the equivalent postfix notation or both postfix notation and the result, as users' choice.

## New feature
Add support for operations where two operands with two or more digits are involved, e.g. (123 * 2) + (6/3) -2. Also, expressions where a two-digit number is involved can now be solved. Expressions like
12 * 12 or (12 * 1) + (13 * 1).

## Float numbers are here!
Now you can make operations with float numbers too!

## Running the application
To run the program, make sure to follow the next steps:

1. In first place you have to compile the program using the `-lm` flag in this way: `gcc notacion_posfija.c -o name_you_wish.o -Wall -lm`
2. The following step depends on your operating system.
   - Windows: `.\name_you_wish [expressions]`
   - Linux: `./name_you_wish [expresions]`
