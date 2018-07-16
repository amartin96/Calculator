#pragma once

typedef enum
{
    CALC_ERROR_NONE,
    CALC_ERROR_NO_INPUT,
    CALC_ERROR_OVERFLOW,
    CALC_ERROR_UNDERFLOW,
    CALC_ERROR_PAREN_MISMATCH,
    CALC_ERROR_NUMBER_EXPECTED,
} CalcError;

CalcError calc_errno();

double calculate(const char* input);
