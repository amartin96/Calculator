#include <ctype.h>      // isalpha()
#include <math.h>       // pow()
#include <stdlib.h>     // strtod()
#include "calculator.h"


static CalcError calc_errno_val;
CalcError calc_errno() { return calc_errno_val; }


static double addExpr(const char** input);


static double lex(const char** input)
{
    // discard prepended whitespace
    while (**input == ' ')
        *input += 1;

    // parse a double
    char* endptr;
    double result = strtod(*input, &endptr);
    *input = endptr;

    // check for errors
    if (errno == ERANGE)
    {
        if (result == HUGE_VAL || result == -HUGE_VAL)
            calc_errno_val = CALC_ERROR_OVERFLOW;
        else
            calc_errno_val = CALC_ERROR_UNDERFLOW;
    }

    // discard appended whitespace
    while (**input == ' ')
        *input += 1;

    return result;
}


static double parenExpr(const char** input)
{
    double result;

    // discard prepended whitespace
    while (**input == ' ')
        *input += 1;

    // if an opening paren is found, parse accordingly
    if (**input == '(')
    {
        // discard the opening paren
        *input += 1;

        // parse the inside of the parenthetical
        result = addExpr(input);

        // match a closing paren
        if (**input != ')')
        {
            calc_errno_val = CALC_ERROR_PAREN_MISMATCH;
            return 0;
        }
        *input += 1;
    }

    // otherwise, match a number
    else
    {
        if (isalpha(**input))
        {
            calc_errno_val = CALC_ERROR_NUMBER_EXPECTED;
            return 0;
        }

        result = lex(input);
    }

    // discard appended whitespace
    while (**input == ' ')
        *input += 1;

    return result;
}


static double powExpr(const char** input)
{
    double lhs = parenExpr(input);

    // if the corresponding operator is found, parse another value and compute the expression
    // otherwise, return what has been parsed so far
    if (**input != '^')
        return lhs;
    *input += 1;

    double rhs = powExpr(input);

    return pow(lhs, rhs);
}


static double multExpr(const char** input)
{
    double lhs = powExpr(input);

    // if a corresponding operator is found, parse another value and compute the expression
    // otherwise, return what has been parsed so far
    char op = **input;
    if (   op != '*'
        && op != '/'
        && op != '%')
        return lhs;
    *input += 1;

    double rhs = multExpr(input);

    if (op == '*')
        return lhs * rhs;
    if (op == '/')
        return lhs / rhs;
    return (long long)lhs % (long long)rhs;
}


static double addExpr(const char** input)
{
    double lhs = multExpr(input);

    // if the corresponding operator is found, parse another value and compute the expression
    // otherwise, return what has been parsed so far
    char op = **input;
    if (   op != '+'
        && op != '-')
        return lhs;
    *input += 1;

    double rhs = addExpr(input);

    if (op == '+')
        return lhs + rhs;
    return lhs - rhs;
}


double calculate(const char* input)
{
    calc_errno_val = CALC_ERROR_NONE;

    if (input[0] == '\0')
    {
        calc_errno_val = CALC_ERROR_NO_INPUT;
        return 0;
    }
    return addExpr(&input);
}