#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "calculator.h"


static CalcError calc_errno_val;
CalcError calc_errno() { return calc_errno_val; }


static double addExpr(const char* input, size_t* pos);


static double lex(const char* input, size_t* pos)
{
    // discard prepended whitespace
    while (input[*pos] == ' ')
        *pos += 1;

    char* endptr;
    double result = strtod(&input[*pos], &endptr);
    *pos += endptr - input;

    // check for conversion errors
    if (errno == ERANGE)
    {
        if (result == HUGE_VAL || result == -HUGE_VAL)
            calc_errno_val = CALC_ERROR_OVERFLOW;
        else
            calc_errno_val = CALC_ERROR_UNDERFLOW;
    }

    // discard appended whitespace
    while (input[*pos] == ' ')
        *pos += 1;

    return result;
}


static double parenExpr(const char* input, size_t* pos)
{
    double result;

    // discard prepended whitespace
    while (input[*pos] == ' ')
        *pos += 1;

    if (input[*pos] == '(')
    {
        *pos += 1;
        result = addExpr(input, pos);
        if (input[*pos] != ')')
        {
            calc_errno_val = CALC_ERROR_PAREN_MISMATCH;
            return 0;
        }
        *pos += 1;
    }

    else
    {
        if (isalpha(input[*pos]))
        {
            calc_errno_val = CALC_ERROR_NUMBER_EXPECTED;
            return 0;
        }

        result = lex(input, pos);
    }

    // discard appended whitespace
    while (input[*pos] == ' ')
        *pos += 1;

    return result;
}


static double powExpr(const char* input, size_t* pos)
{
    double lhs = parenExpr(input, pos);

    if (input[*pos] != '^')
        return lhs;
    *pos += 1;

    double rhs = powExpr(input, pos);

    return pow(lhs, rhs);
}


static double multExpr(const char* input, size_t* pos)
{
    double lhs = powExpr(input, pos);

    char op = input[*pos];
    if (   op != '*'
        && op != '/'
        && op != '%')
        return lhs;
    *pos += 1;

    double rhs = multExpr(input, pos);

    if (op == '*')
        return lhs * rhs;
    if (op == '/')
        return lhs / rhs;
    return (long long)lhs % (long long)rhs;
}


static double addExpr(const char* input, size_t* pos)
{
    double lhs = multExpr(input, pos);

    char op = input[*pos];
    if (   op != '+'
        && op != '-')
        return lhs;
    *pos += 1;

    double rhs = addExpr(input, pos);

    if (op == '+')
        return lhs + rhs;
    return lhs - rhs;
}


double calculate(const char* input)
{
    calc_errno_val = CALC_ERROR_NONE;

    size_t pos = 0;
    if (input[pos] == '\0')
    {
        calc_errno_val = CALC_ERROR_NO_INPUT;
        return 0;
    }
    return addExpr(input, &pos);
}