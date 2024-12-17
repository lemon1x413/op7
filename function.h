#ifndef OP7_FUNCTION_H
#define OP7_FUNCTION_H

#include "color.h"
#include <stdbool.h>

#define MIN_EPS 1e-15
#define MAX_EPS 1e-1
#define MIN_T -100
#define MAX_T 100
#define MIN_RANGE -100
#define MAX_RANGE 100
#define STEP 1e-6
#define MAX_ITER 1e4
#define MAX_ROOTS 1000

bool conditionDoubleT(double value) {
    return (value < MIN_T || value > MAX_T);
}

bool conditionDoubleIntervals1(double value) {
    return ((value < MIN_RANGE || value > MAX_RANGE) || value == 0.0);
}

bool conditionDoubleIntervals2(double value) {
    return (value < 1e-15);
}

bool conditionDoubleEpsilon(double value) {
    return (value < MIN_EPS || value > MAX_EPS);
}

double validInputDouble(char *message, bool (*condition)(double)) {
    double value = 0;
    int validInput = 0;
    do {
        printf("%s", message);
        validInput = scanf("%lf", &value);
        if (validInput != 1 || condition(value)) {
            printf(RED"Invalid input\n"RESET);
        }
        fflush(stdin);
    } while (validInput != 1 || condition(value));
    return value;
}

char validInputChoice(char *message, char choice1, char choice2) {
    char value = 0;
    do {
        printf("%s", message);
        value = getch();
        if (value != choice1 && value != choice2) {
            printf(RED"Invalid input\n"RESET);
        }
    } while (value != choice1 && value != choice2);
    return value;
}

double f1(double x, double t) {
    return (cos(t / x) - 2.0 * sin(1.0 / x) + 1.0 / x);
}

double f2(double x, double t) {
    return (sin(log(x)) - cos(log(x)) + t * log(x));
}

double fd1(double x, double t) {
    return ((t * sin(t / x) + 2.0 * cos(1.0 / x) - 1.0) / (x * x));
}

double fd2(double x, double t) {
    return ((sin(log(x)) + cos(log(x)) + t) / x);
}

bool uniqueRoot(double roots[], int count, double new_root, double epsilon) {
    for (int i = 0; i < count; i++) {
        if (fabs(roots[i] - new_root) < epsilon) {
            return false;
        }
    }
    return true;
}

bool rootInInterval(double x, double a, double b) {
    if (x < a || x > b) {
        printf(RED"Root is out of the given interval.\n"RESET);
        return false;
    }
    return true;
}

double halfDivisionMethod(double (*f)(double, double), double a, double b, double t, double epsilon) {
    double delta = 0;
    int iter = 0;
    double x = 0, fa = 0, fx = 0;
    do {
        x = (a + b) / 2.0;
        delta = fabs(b - a);
        fa = f(a, t);
        fx = f(x, t);
        if (isnan(fa) || isnan(fx)) {
            printf(RED"Function has a discontinuity in the interval [%lf, %lf]. Skipping...\n"RESET, a, b);
            return NAN;
        }
        fa * fx > 0
                ? (a = x)
                : (b = x);
        iter++;
        if (iter > MAX_ITER) {
            printf(RED"Maximum iterations reached. The method may not converge.\n"RESET);
            return NAN;
        }
    } while (delta > epsilon);
    return x;
}

double newtonMethod(double (*f)(double, double), double (*df)(double, double), double a, double t, double epsilon) {
    double x = a;
    double delta;
    int iter = 0;
    do {
        double derivative = df(x, t);
        delta = f(x, t) / derivative;
        x -= delta;
        iter++;
        if (iter > MAX_ITER) {
            printf(RED"Newton's method did not converge within the maximum number of iterations.\n"RESET);
            return NAN;
        }
    } while (fabs(delta) > epsilon);
    return x;
}

void findAllRoots(double (*f)(double, double), double (*df)(double, double), double a, double b, double t, double epsilon, int method) {
    double left = a;
    int precision = fabs(log10(epsilon));
    int rootsFound = 0;
    double roots[MAX_ROOTS] = {0};
    while (left < b) {
        double right = fmin(left + STEP, b);
        double fLeft = f(left, t);
        double fRight = f(right, t);
        if (left <= 0 && right >= 0) {
            left = right;
            continue;
        }
        if (fLeft * fRight <= 0) {
            double x = 0;
            switch (method) {
                case '1':
                    x = halfDivisionMethod(f, left, right, t, epsilon);
                    break;
                case '2':
                    x = newtonMethod(f, df, left, t, epsilon);
                    break;
                default:
                    printf(RED"Invalid input\n"RESET);
                    break;
            }
            if (uniqueRoot(roots, rootsFound, x, epsilon) && rootInInterval(x, a, b) && !isnan(x)) {
                roots[rootsFound] = x;
                printf(BLUE"Root x%02d: x = %.*lf\n"RESET, rootsFound + 1, precision, x);
                rootsFound++;
            }
        }
        left = right;
    }
    if (rootsFound == 0) {
        printf(RED"No roots found in the given interval.\n"RESET);
    }
}

#endif