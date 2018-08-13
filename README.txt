        calc is a very simple calculator that is somewhat similar with the famous program expr.


[SYNOPSIS]

        calc  [options]  OPu  operand1
        calc  [options]  operand1  OPb  operand2


[DESCRIPTION]

        calc is a very simple calculator, it calculates the
    result of expressions and output the result to the standard output.

        In the above synopsis:
                OPu indicates an unary operator that only needs one operand.
                e.g. ++, --, ~, !

                OPb indicates an binary operator that needs two operands
                e.g. +, -, *, /, %

        calc supports only the simplest expressions.
        Expressions passed to calc must meets the following restrictions:

                * has only one operator
                * has only one operand when the operator is an unary operator(OPu)
                * has only two operands when the operator is an binary operator(OPb)
                * with no brackets


[EXAMPLES]

        The following are examples of valid usage.
        To avoid expanding mechanism from shell, some operators are surrounded with "".

                calc 1 + 2
                calc 1 - 3
                calc -3 "*" 8
                calc 0x1234 "*" 0X5678
                calc 0123 - 8
                calc 0B10100101 "%" 0b1100
                calc 1 "<<" 10
                calc "++" 1023
                calc "~" 0xF
                calc 5 ">" 6


[OPERAND]

        PREFIX              BASE
        0b/0B               2  (bin)
        0                   8  (octal)
        0x/0X               16 (hex)
        [+ or -]<1~9 >      10 (decimal)


[OPERATORS]

        SYNTAX            TYPE      DESCRIPTION
        +  -  *  /  %     unary     normal arithmetical operators
        ++ -- ~           unary     normal unary operators
        & | ^             binary    normal bitwise operators
        <<  >>            binary    normal shift operators
        > >= < <= !=      binary    normal relationship operators


[OPTIONS]

        The default output format is signed decimal. However, following options can be 
    used to customize the output.
    
        --output-base-2
        --output-bin
            output result in binary format.
        
        --output-base-8
        --output-oct
            output result in octal format.
        
        --output-base-16
        --output-hex
            output result in hex format.

        --output-unsigned-decimal
            output result in unsigned decimal format.

        --output-no-prefix
            output result without prefix such as 0/0x/0X/0b/0B.


[AUTHOR]

        SUN Mingbao <sunmingbao@126.com>
