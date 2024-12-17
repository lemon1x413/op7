#include <stdio.h>
#include <math.h>
#include <conio.h>
#include "function.h"
#include "color.h"

#define ENTER 13

int main() {
    do {
        double a = 0.0, b = 0.0;
        double (*functionChoice)(double, double) = 0;
        double (*derivativeChoice)(double, double) = 0;
        printf(YELLOW"This program finds all roots of nonlinear equations in the given interval [a; b]\n"RESET);
        char choiceFunction = validInputChoice(GREEN"Chose function:\n"
                                               YELLOW"1. cos(t / x) - 2 * sin(1 / x) + 1 / x\n"
                                               "2. sin(ln(x)) - cos(ln(x)) + t * ln(x)\n"RESET,
                                               '1', '2');
        choiceFunction == '1'
                        ? printf(BLUE"You choose function: \ncos(t / x) - 2 * sin(1 / x) + 1 / x\n"RESET)
                        : printf(BLUE"You choose function: \nsin(ln(x)) - cos(ln(x)) + t * ln(x)\n"RESET);
        char choiceMethod = validInputChoice(GREEN"Chose method:\n"
                                             YELLOW"1. Half division method\n"
                                             "2. Newton method\n"RESET,
                                             '1', '2');
        choiceMethod == '1'
                        ? printf(BLUE"You choose half division method\n"RESET)
                        : printf(BLUE"You choose Newton method\n"RESET);
        double t = validInputDouble(GREEN"Enter t (from -100 to 100):\n"RESET, conditionDoubleT);
        printf(GREEN"Enter intervals of x (from a to b):\n"RESET);
        switch (choiceFunction) {
            case '1':
                functionChoice = f1;
                derivativeChoice = fd1;
                do {
                    a = validInputDouble(GREEN"Enter a (from -100 to 100)[not 0]:\n"RESET, conditionDoubleIntervals1);
                    b = validInputDouble(GREEN"Enter b (from -100 to 100)[not 0]:\n"RESET, conditionDoubleIntervals1);
                    if (a >= b)
                        printf(RED"Value of a must be less the value of b.\n"RESET);
                } while (a >= b);
                break;
            case '2':
                functionChoice = f2;
                derivativeChoice = fd2;
                do {
                    a = validInputDouble(GREEN"Enter a (from 1e-15 to 100):\n"RESET, conditionDoubleIntervals2);
                    b = validInputDouble(GREEN"Enter b (from 1e-15 to 100):\n"RESET, conditionDoubleIntervals2);
                    if (a >= b)
                        printf(RED"Value of a must be less the value of b.\n"RESET);
                } while (a >= b);
                break;
            default:
                printf(RED"Invalid input"RESET);
                break;
        }
        double epsilon = validInputDouble(GREEN"Enter precision of calculations (from 1e-15 to 1e-1):\n"RESET,
                                          conditionDoubleEpsilon);
        findAllRoots(functionChoice, derivativeChoice, a, b, t, epsilon, choiceMethod);
        printf(GREEN"Press ENTER to continue, or any other key to exit.\n"RESET);
    } while (getch() == ENTER);
    return 0;
}