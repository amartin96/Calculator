#include <iostream>
#include "Calculator.h"

using namespace Calculator;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

int main()
{
    while (true)
    {
        string input;
        getline(cin, input);

        if (input.find("exit") == 0)
        {
            cout << "Bye!" << endl;
            break;
        }

        try
        {
            cout << calculate(input) << endl;
        }

        catch (const MismatchedParenException&)
        {
            cout << "Error: mismatched parens" << endl;
        }

        catch (const NaNException&)
        {
            cout << "Error: expected a number" << endl;
        }

        catch (const OverflowException&)
        {
            cout << "Error: number too small / large" << endl;
        }
    }

    return 0;
}