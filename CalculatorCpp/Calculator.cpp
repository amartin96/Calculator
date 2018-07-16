#include <cmath>
#include <stdexcept>
#include "Calculator.h"

using namespace Calculator;
using std::invalid_argument;
using std::out_of_range;
using std::stod;
using std::string;

namespace
{
    double addExpr(const string&, size_t&);
    double parenExpr(const string& input, size_t& pos)
    {
        double result;

        // discard prepended whitespace
        while (input[pos] == ' ')
            ++pos;

        // if a parenthetical expression exists, evaluate it
        if (input[pos] == '(')
        {
            ++pos;
            result = addExpr(input, pos);
            if (input[pos] != ')')
            {
                throw MismatchedParenException();
            }
            ++pos;

            return result;
        }

        // otherwise, parse a number
        // NOTE: this will throw 'invalid_argument' if NaN, and 'out_of_range' if the result can't fit in a double
        size_t end;
        try
        {
            result = stod(input.substr(pos), &end);
        }
        catch (const invalid_argument&)
        {
            throw NaNException();
        }
        catch (const out_of_range&)
        {
            throw OverflowException();
        }
        pos += end;

        // discard appended whitespace
        while (input[pos] == ' ')
            ++pos;

        return result;
    }

    double powExpr(const string& input, size_t& pos)
    {
        double lhs = parenExpr(input, pos);

        if (input[pos] != '^')
            return lhs;
        ++pos;

        double rhs = powExpr(input, pos);

        return pow(lhs, rhs);
    }

    double multExpr(const string& input, size_t& pos)
    {
        double lhs = powExpr(input, pos);

        char op = input[pos];
        if (   op != '*'
            && op != '/'
            && op != '%')
            return lhs;
        ++pos;

        double rhs = multExpr(input, pos);

        if (op == '*')
            return lhs * rhs;
        if (op == '/')
            return lhs / rhs;
        return static_cast<long long>(lhs) % static_cast<long long>(rhs);
    }

    double addExpr(const string& input, size_t& pos)
    {
        double lhs = multExpr(input, pos);

        char op = input[pos];
        if (   op != '+'
            && op != '-')
            return lhs;
        ++pos;

        double rhs = addExpr(input, pos);

        if (op == '+')
            return lhs + rhs;
        return lhs - rhs;
    }
}

namespace Calculator
{
    double calculate(const string& input)
    {
        size_t pos = 0;
        if (input.length() == 0)
            return 0;
        return addExpr(input, pos);
    }
}