#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/Status.h"

bool cmp(long double a, long double b, long double eps) {
    return fabsl(a - b) <= eps;
}

// out[i] = {ai, bi, ci, solve_cnt, 1solve, 2solve}
// максимум 3! перестановок;
// Будем рассматривать только вещественные корни 
Status getAllSollutions(long double eps, long double vals[3], long double (*sols)[6], int* n) {
    // long double sols[6][6];
    int cnt = 0;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            for(int k = 0; k < 3; ++k) {
                if(i == j || j == k || i == k) {
                    continue;
                }
                // не было ли раньше таких значений
                bool was = false;
                for(int ind = 0; ind < cnt; ind++) {
                    if(cmp(sols[ind][0], vals[i], eps) &&
                            cmp(sols[ind][1], vals[j], eps) &&
                            cmp(sols[ind][2], vals[k], eps)) {
                        was = true;
                        break;
                    }
                }
                if(was) {
                    continue;
                }
                long double a = vals[i], b = vals[j], c = vals[k];
                sols[cnt][0] = a;
                sols[cnt][1] = b;
                sols[cnt][2] = c;
                if(cmp(a, 0, eps)) {
                    if(cmp(b, 0, eps)) {
                        // c = 0
                        sols[cnt][3] = cmp(c, 0, eps) ? INFINITY: 0;
                    } else {
                        // линейное ур.е b * x + c = 0
                        // x = -c / b;
                        sols[cnt][3] = 1;
                        sols[cnt][4] = -c / b;
                    }
                } else {
                    long double D = b * b - 4 * a * c;
                    if(D < 0) {
                        sols[cnt][3] = 0;
                    } else if(cmp(D, 0, eps)) {
                        sols[cnt][3] = 1;
                        sols[cnt][4] = -b / (2 * a);
                    } else {
                        D = sqrt(D);
                        sols[cnt][3] = 2;
                        sols[cnt][4] = (-b + D) / (2 * a);
                        sols[cnt][5] = (-b - D) / (2 * a);
                    }
                }
                cnt++;
            }
        }
    }
    *n = cnt;
    return Ok;
}

Status isMultiple(long double a, long double b, bool* isMul) {
    long double eps = 1e-9;
    // если введенное a не помещается в long long то нельзя проверить целое ли число и кратность
    // при больших числах floor работает очень плохо поэтому принимае a <= __INT32_MAX__
    if(a > __INT32_MAX__ || b > __INT32_MAX__) {
        return LongOverflow;
    }
    int aInt = floor(a), bInt = floor(b);
    if(!cmp(a, aInt, eps) || !cmp(b, bInt, eps)) {
        return NotInteger;
    }
    if(!aInt || !bInt) {
        return Zero;
    }
    if(aInt < 0 || bInt < 0) {
        return NegativeNum;
    }
    *isMul = aInt % bInt == 0;
    return Ok;
}

Status isTriangle(long double eps, long double a, long double b, long double c, bool* isTr) {
    if(a < 0 || b < 0 || c < 0) {
        return NegativeNum;
    }
    long double mx = fmaxl(a, fmaxl(b, c));
    *isTr = cmp(a * a + b * b + c * c, 2 * mx * mx, eps);
    if(a + b + c <= 2 * mx) {
        *isTr = false;
    }

    return Ok;
}