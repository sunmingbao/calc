# calc
    calc is a very simple calculator that is somewhat similar with the famous program expr.

## SYNOPSIS
       calc  OPu  operand1
       calc  operand1  OPb  operand2

## DESCRIPTION
    calc is a very simple calculator, it calculates the 
result of expressions and output the result to the 
standard output.

    In the above synopsis, the OPu indicates an unary 
operator that only needs one operand(e.g. ++, --, ~, !), 
the OPb indicates an binary operator that needs two 
operands(e.g. +, -, *, /, %).

    calc supports only the simplest expressions.
    Expressions passed to calc must meets the 
following restrictions.

* has only one operator
* has only one operand when the operator is an unary operator(OPu)
* has only two operands when the operator is an binary operator(OPb)
* with no brackets

    The following are examples of valid usage.
    To avoid expanding mechanism from shell, some operators are surrounded with '' or "".

        calc 1 + 2
        calc 1 - 3
        calc -3 '*' 8
        calc 0x1234 '*' 0X5678
        calc 0123 - 8
        calc 0B10100101 % 0b1100
        calc 2 "<<" 10
        calc "++" 1023
        calc "~" 0xF
        calc 5 '>' 6

## OPERAND
PREFIX    BASE
0b/0B     2 (bin)
0         8 (octal)
0x/0X    16 (hex)
+/-      10 (decimal)

    if an operand does not starts with any of the 
above prefix, then calc would determine its base 
with the following logic.
        if (operand contains char in [a-f] or [A-F])
                base=16
        else
                base=10

## OPERATOR
SYNTAX          TYPE    DESCRIPTION
+  -  *  /  %   unary   normal arithmetical operators
++ -- ~  !  !!  unary   !  means operand==0?1:0
                        !! means operand==0?0:1
& | ^           binary  normal bitwise operators
<<  >>          binary  normal shift operators

## OPTIONS
--output-2
--output-bin
    output result in binary format.

--output-8
--output-oct
    output result in octal format.

--output-16
--output-hex
    output result in hex format.

--no-prefix
    output result without prefix such as 0/0x/0X/0b/0B.