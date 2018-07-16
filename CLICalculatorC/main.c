#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

static const unsigned MAX_INPUT_LENGTH = 256;

static void catchSigint(int signo)
{
    fputs("Bye!\n", stdout);
    exit(EXIT_SUCCESS);
}

int main(void)
{
    if (signal(SIGINT, catchSigint) == SIG_ERR)
    {
        fputs("Error: could not bind SIGINT handler\n", stderr);
    }

    while (true)
    {
        char input[MAX_INPUT_LENGTH];
        fputs("calculator> ", stdout);
        fgets(input, MAX_INPUT_LENGTH, stdin);

        if (strstr(input, "exit") == input)
            break;

        printf(" = %g\n", calculate(input));
    }

    fputs("Bye!\n", stdout);

    return 0;
}
