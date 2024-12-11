#include <stdio.h>
#include <math.h>
#include <conio.h>
#include "function.h"
#include "color.h"

int main() {
    double x = 0.0, a = 0.0, b = 0.0;
    double (*functionChoice)(double, double) = 0;
    int choiceFunction = validInputChoice(GREEN"Chose function:\n"
                                          YELLOW"1. cos(t / x) - 2 * sin(1 / x) + 1 / x\n"
                                          "2. sin(ln(x)) - cos(ln(x)) + t * ln(x)\n"RESET,
                                          '1', '2');
    int choiceMethod = validInputChoice(GREEN"Chose method:\n"
                                        YELLOW"1. Half division method\n"
                                        "2. Newton method\n"RESET,
                                        '1', '2');
    double t = validInputDouble(GREEN"Enter t (from -1000 to 1000):\n"RESET, conditionDoubleT);
    switch (choiceFunction) {
        case '1':
            functionChoice = f1;
            do {
                a = validInputDouble(GREEN"Enter a (from 0 to 100):\n"RESET, conditionDoubleA1);
                b = validInputDouble(GREEN"Enter b (from 0 to 100):\n"RESET, conditionDoubleB1);
                if (a >= b)
                    printf(RED"Value of a must be less the value of b."RESET);
            } while (a >= b);
            break;
        case '2':
            functionChoice = f2;
            do {
                a = validInputDouble(GREEN"Enter a (from 0 to 100):\n"RESET, conditionDoubleA2);
                b = validInputDouble(GREEN"Enter b (from 0 to 100):\n"RESET, conditionDoubleB2);
            } while (a >= b);
            break;
        default:
            printf(RED"Invalid input"RESET);
            break;
    }
    double epsilon = validInputDouble(GREEN"Enter precision of calculations (from 1e-15 to 1e-1):\n"RESET,
                                      conditionDoubleEpsilon);
    unsigned precision = (unsigned) fabs(log10(epsilon));
    switch (choiceMethod) {
        case '1':
            x = halfDivisionMethod(functionChoice, a, b, t, epsilon);
            printf("x = %.*lf\n", precision, x);
            break;
        case '2':
            //x = newtonMethod(functionChoice, fdChoice, a, b, t, epsilon);
            //x = newtonMethod2(functionChoice, a, b, t, epsilon);
            printf(BLUE"x = %.*lf\n"RESET, precision, x);
            break;
        default:
            printf(RED"Invalid input"RESET);
            break;
    }
    getch();
    return 0;
}
//x = newton_method(a, b, t, epsilon, functionChoice);