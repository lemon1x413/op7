#ifndef OP7_FUNCTION_H
#define OP7_FUNCTION_H

#define MIN_EPS 1e-15
#define MAX_EPS 1e-1
#define MIN_T -1000
#define MAX_T 1000
#define MIN_A -1000
#define MAX_A 1000
#define MIN_B -1000
#define MAX_B 1000

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\x1b[36m"
#define YELLOW  "\x1b[33m"
#define RESET "\033[0m"

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

double fd1(double x, double t) {
    return ((t * sin(t / x) + 2.0 * cos(1.0 / x) - 1.0) / (x * x));
}

double f2(double x, double t) {
    return (sin(log(x)) - cos(log(x)) + t * log(x));
}

double fd2(double x, double t) {
    return ((sin(log(x)) + cos(log(x)) + t ) / x);
}



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
    double x = f(b,t), fd = 0.0 delta = 0.0;
    do {
        fd =
        delta = f(x, t) / fd(x, t);
        x -= delta;
    } while (fabs(delta) > epsilon);
    return x;
}

#endif