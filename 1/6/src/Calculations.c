#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/Status.h"
#include "../include/Calculations.h"

long double fa(long double x, long double eps) {
    if (fabsl(x) < eps) {
        return 1.0;  // lim(x→0+) ln(1 + x) / x = 1
    }
    return logl(1.L + x) / x;
}

long double fb(long double x, long double eps) {
    return exp(-(x*x) / 2.0L);
}

long double fc(long double x, long double eps) {
    return -logl(1.L - x);
}

long double fd(long double x, long double eps) {
    if (fabsl(x) < eps) {
        return 1.0L;  // lim(x→0+) x^x = 1
    }
    return powl(x, x);
}

Status calc(long double (* f)(long double, long double), 
            long double eps, long double a, long double b, long double *out) {
    long double prev = 0, cur = 0, width = (b - a) / 2;
    int n = 2, step = 0;
    const int maxOpCnt = 1e3;
    do {
        prev = cur;
        n += 10;
        width = (b - a) / n;
        cur = 0;
        for(step = 0; step < n; ++step) {
            long double x1 = a + step * width;
            long double x2 = x1 + width;
            cur += 0.5L * (x2 - x1) * (f(x1, eps) + f(x2, eps)); 
        }
        if(n > maxOpCnt || isinf(cur)) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(cur - prev) > eps);
    *out = cur;
    return Ok;
}