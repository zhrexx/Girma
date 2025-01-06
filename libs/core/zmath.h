#ifndef ZMATH_H
#define ZMATH_H

#include <stdio.h>

// Math constants ()
#define ZM_E            2.71828182845904523536
#define ZM_LOG2E        1.44269504088896340736
#define ZM_LOG10E       0.43429448190325182765
#define ZM_LN2          0.69314718055994530942
#define ZM_LN10         2.30258509299404568402
#define ZM_PI           3.14159265358979323846
#define ZM_PI_2         1.57079632679489661923
#define ZM_PI_4         0.78539816339744830962
#define ZM_1_PI         0.31830988618319145600
#define ZM_2_PI         0.63661977236758134308
#define ZM_2_SQRTPI     1.12837916709551257390
#define ZM_SQRT2        1.41421356237309504880
#define ZM_SQRT1_2      0.70710678118654752440
#define ZM_EULER        0.57721566490153286060
#define ZM_TAU          6.28318530717958647692
#define ZM_INFINITY     1.0/0.0
#define ZM_NAN          0.0/0.0*-1
#define ZM_DECIMAL_DIG  17
#define ZM_RADIX        2
#define ZM_MANT_DIG     53
#define ZM_MAX_EXP      1024
#define ZM_MIN_EXP      -1021
#define ZM_MAX_10_EXP   308
#define ZM_MIN_10_EXP   -307
#define ZM_MAX          DBL_MAX
#define ZM_MIN          DBL_MIN
#define ZM_EPSILON      DBL_EPSILON
#define ZM_DIG          DBL_DIG



double zm_cos(double x);
double zm_sin(double x);
double zm_tan(double x);
double zm_atan(double x);
double zm_exp(double x);
double zm_sinh(double x);
double zm_cosh(double x);
double zm_tanh(double x);
double zm_pow(double x, double y);
double zm_log(double x);
double zm_sqrt(double x);
double zm_asin(double x);
double zm_acos(double x);
double zm_log10(double x);
double zm_abs(double x);
double zm_fabs(double x);
double zm_ceil(double x);
double zm_floor(double x);
double zm_round(double x);
double zm_hypot(double x, double y);
double zm_deg2rad(double degrees);
double zm_rad2deg(double radians);
double zm_factorial(int n);
double zm_gamma(double x);
double zm_lgamma(double x);
double zm_mod(double x, double y);
double zm_trunc(double x);
int zm_isnan(double x);
int zm_isinf(double x);

double zm_cos(double x) {
    double term = 1.0;
    double sum = term;
    int sign = -1;
    int max_terms = 10;

    for (int i = 1; i < max_terms; i++) {
        term *= x * x / ((2 * i - 1) * (2 * i));
        sum += sign * term;
        sign *= -1;
    }

    return sum;
}

double zm_sin(double x) {
    double term = x;
    double sum = term;
    int sign = -1;
    int max_terms = 10;

    for (int i = 1; i < max_terms; i++) {
        term *= x * x / ((2 * i) * (2 * i + 1));
        sum += sign * term;
        sign *= -1;
    }

    return sum;
}

double zm_tan(double x) {
    return zm_sin(x) / zm_cos(x);
}

double zm_atan(double x) {
    double term = x;
    double sum = term;
    int sign = -1;
    int max_terms = 10;

    for (int i = 1; i < max_terms; i++) {
        term *= x * x / (2 * i * (2 * i + 1));
        sum += sign * term;
        sign *= -1;
    }

    return sum;
}

double zm_exp(double x) {
    double term = 1.0;
    double sum = term;
    int sign = 1;
    int max_terms = 10;

    for (int i = 1; i < max_terms; i++) {
        term *= x / i;
        sum += term;
    }

    return sum;
}

double zm_sinh(double x) {
    return (zm_exp(x) - zm_exp(-x)) / 2;
}

double zm_cosh(double x) {
    return (zm_exp(x) + zm_exp(-x)) / 2;
}

double zm_tanh(double x) {
    return zm_sinh(x) / zm_cosh(x);
}

double zm_pow(double x, double y) {
    return zm_exp(y * zm_log(x));
}

double zm_log(double x) {
    if (x <= 0) return ZM_NAN;
    double result = 0;
    double term = (x - 1) / (x + 1);
    for (int n = 1; n < 100; n += 2) {
        result += (1.0 / n) * zm_pow(term, n);
    }
    return 2 * result;
}

double zm_sqrt(double x) {
    if (x < 0) return ZM_NAN;
    return zm_exp(zm_log(x) / 2);
}

double zm_asin(double x) {
    if (x < -1.0 || x > 1.0) return ZM_NAN;
    return zm_atan(x / zm_sqrt(1 - x * x));
}

double zm_acos(double x) {
    if (x < -1.0 || x > 1.0) return ZM_NAN;
    return ZM_PI_2 - zm_asin(x);
}

double zm_log10(double x) {
    return zm_log(x) / ZM_LN10;
}

double zm_abs(double x) {
    return x < 0 ? -x : x;
}

double zm_fabs(double x) {
    return x < 0.0 ? -x : x;
}

double zm_ceil(double x) {
    return (double)((int)x + (x > 0 ? 1 : 0));
}

double zm_floor(double x) {
    return (double)((int)x);
}

double zm_round(double x) {
    return (x > 0) ? zm_floor(x + 0.5) : zm_ceil(x - 0.5);
}

double zm_hypot(double x, double y) {
    return zm_sqrt(x * x + y * y);
}

double zm_deg2rad(double degrees) {
    return degrees * ZM_PI / 180.0;
}

double zm_rad2deg(double radians) {
    return radians * 180.0 / ZM_PI;
}

double zm_factorial(int n) {
    if (n == 0 || n == 1) return 1;
    double result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double zm_gamma(double x) {
    return (x < 0.5) ? ZM_PI / (zm_sin(ZM_PI * x) * zm_gamma(1 - x)) : (x - 1) * zm_gamma(x - 1);
}

double zm_lgamma(double x) {
    return zm_log(zm_gamma(x));
}

double zm_mod(double x, double y) {
    return x - y * zm_floor(x / y);
}

double zm_trunc(double x) {
    return (double)((int)x);
}

int zm_isnan(double x) {
    return x != x;
}

int zm_isinf(double x) {
    return x == ZM_INFINITY || x == -ZM_INFINITY;
}

#endif
