#ifndef OP7_FUNCTION_H
#define OP7_FUNCTION_H
#include "color.h"

#define MIN_EPS 1e-15
#define MAX_EPS 1e-1
#define MIN_T -1000
#define MAX_T 1000
#define MIN_A -1000
#define MAX_A 1000
#define MIN_B -1000
#define MAX_B 1000
#define STEP 1e-5
#define MAX_ITER 1e4

char conditionDoubleA1(double value) {
    return ((value < MIN_A || value > MAX_A) || value == 0.0);
}

char conditionDoubleA2(double value) {
    return (value <= 0.0);
}

char conditionDoubleT(double value) {
    return (value < MIN_T || value > MAX_T);
}

char conditionDoubleB1(double value) {
    return ((value < MIN_B || value > MAX_B) || value == 0.0);
}

char conditionDoubleB2(double value) {
    return (value <= 0.0);
}

char conditionDoubleEpsilon(double value) {
    return (value < MIN_EPS || value > MAX_EPS);
}

double validInputDouble(char *message, char (*condition)(double)) {
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

int validInputChoice(char *message, int choice1, int choice2) {
    int value = 0;
    do {
        printf("%s", message);
        value = getch();
        if (value != choice1 && value != choice2) {
            printf(RED"Invalid input\n"RESET);
        }
        fflush(stdin);
    } while (value != choice1 && value != choice2);
    return value;
}

double f1(double x, double t) {
    return (cos(t / x) - 2.0 * sin(1.0 / x) + 1.0 / x);
}

/*double fd1(double x, double t) {
    return ((t * sin(t / x) + 2.0 * cos(1.0 / x) - 1.0) / (x * x));
}*/

double f2(double x, double t) {
    return (sin(log(x)) - cos(log(x)) + t * log(x));
}

/*double fd2(double x, double t) {
    return ((sin(log(x)) + cos(log(x)) + t ) / x);
}*/



double halfDivisionMethod(double (*f)(double, double), double a, double b, double t, double epsilon) {
    double x, delta;
    do {
        delta = fabs(b - a);
        x = (a + b) / 2.0;
        if ((f(a, t)) * f(x, t) > 0.0) {
            a = x;
        } else {
            b = x;
        }
    } while (delta > epsilon);
    return x;
}

double newtonMethod(double (*f)(double, double), double (*fd)(double, double), double a, double b, double t, double epsilon) {
    double x = f(b,t), delta = 0.0;
    do {
        delta = f(x, t) / fd(x, t);
        x -= delta;
    } while (fabs(delta) > epsilon);
    return x;
}

double newtonMethod2(double (*f)(double, double), double a, double b, double t, double epsilon) {
    double x = f(b,t), fd = 0.0, delta = 0.0;
    do {
        fd = f(x + a, t) / a;
        delta = f(x, t) / fd;
        x -= delta;
    } while (fabs(delta) > epsilon);
    return x;
}

/*double newton_method(double a, double b, double t, double epsilon, double (*function)(double, double)) {
    double delta = 0;
    double fd = 0;
    int iterations = 0;
    double x = (a + b) / 2.0;
    do {
        double fx = function(x, t);
        if (isnan(fx)) {
            printf(RED"Function is undefined at x = %lf.\n"RESET, x);
            return NAN;
        }
        fd = (function(x + STEP, t) - fx) / STEP;
        if (fabs(fd) < 1e-15) {
            printf(RED"Derivative too small at x = %lf. The method may not converge.\n"RESET, x);
            return NAN;
        }
        delta = fx / fd;
        x -= delta;
        iterations++;
        if (iterations > MAX_ITER) {
            printf(RED"Too many iterations.\n"RESET);
            return NAN;
        }
    } while (fabs(delta) > epsilon);
    printf("x = %.3d\n", iterations);
    return x;
}*/
#endif