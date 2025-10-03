#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include "../include/Status.h"

#define min(a, b) (a < b ? (a): (b))

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// имеет ли a таких же простых делителей как у b
bool samePrime(int a, int b) {
    for(int i = 2; i * i <= b; ++i) {
        if(!((b % i) || !(a % i))) {
            return false;
        } 
        while(a % i == 0) {
            a /= i;
        }
        while(b % i == 0) {
            b /= i;
        }
    }
    // b = prime ^ 1
    return a % b == 0;
}

/*
Десятичная дробь A имеет конечное представление в системе счисления с основанием B тогда и только тогда,
когда при представлении дроби A в виде несократимой дроби P/Q, 
знаменатель Q делится только на простые множители, 
которые являются также простыми множителями основания B.
*/
Status operate(bool* out, int base, int n, ...) {
    if(base <= 1) {
        return InvalidBase;
    }
    va_list num;
    va_start(num, n);
    const double eps = 1e-9;
    double frac;
    long long q;
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        frac = va_arg(num, double), q = 1;
        if(frac <= eps || frac - 1 >= eps) {
            return InvalidArgument;
        }
        while(fabs(frac - (int)frac) > eps) {
            frac *= 10.l;
            q *= 10;
            cnt++;
            if(cnt >= 1e6) {
                return PeriodFrac;
            }
        }
        // fraction -> p / q;
        out[i] = samePrime(base, q / gcd(frac, q));
    }
    va_end(num);
    return Ok;
}