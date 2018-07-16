#pragma once

#include <exception>
#include <string>

namespace Calculator
{
    class MismatchedParenException : public std::exception {};
    class NaNException : public std::exception {};
    class OverflowException : public std::exception {};
    double calculate(const std::string& input);
}