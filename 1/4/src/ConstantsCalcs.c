#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/Status.h"

#define MAX_IT_CNT_IF_NO_BIG_NUMS 1000000

Status eLimit(long double eps, long double *out) {
    long double prev = 0, cur = 0;
    int n = 0;
    do {
        prev = cur;
        ++n;
        cur = powl(1.0L + 1.0L / n, n);
        if(n > MAX_IT_CNT_IF_NO_BIG_NUMS) {
            *out = prev;
            return CannotReachAccur;
        }
    } while(fabsl(prev - cur) > eps);
    *out = prev;
    return Ok;
}

Status eRow(long double eps, long double *out) {
    // cur - Значение суммы при n = 0
    long double cur = 1, invFact = 1;
    int n = 0;
    do {
        ++n;
        invFact /= n;
        cur += invFact;
        if(n > 30) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(invFact) > eps);
    *out = cur;
    return Ok;
}

Status eEquation(long double eps, long double *out) {
    *out = exp(1);
    return Ok;
}

Status pLimit(long double eps, long double *out) {
    long double cur = 0, prev = 0, nfact = 1, nP2 = 1, n2fact = 1;
    int n = 0;
    do {
        // 2^n = 2^(n - 1) * 2;
        // n! = (n - 1)! * n
        // (2 * n)! = (2 * n - 2)! * (2 * n - 1) * (2 * n) =  (2 * (n - 1))! * (2 * n - 1) * (2 * n)
        prev = cur;
        ++n;
        nfact *= n;
        nP2 *= 2.0L;
        n2fact *= (2 * n - 1) * (2 * n);
        cur = powl(nP2 * nfact, 4) / (n * n2fact * n2fact);
        if(n > 30) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(cur - prev) > eps);
    *out = cur;
    return Ok;
}

Status pRow(long double eps, long double *out) {
    long double cur = 0, add = 0, up = -1;
    int n = 0;
    do {
        ++n;
        up *= -1;
        add = 4.0L * up / (2 * n - 1);
        cur = cur + add;
        if(n > MAX_IT_CNT_IF_NO_BIG_NUMS) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(add) > eps);
    *out = cur;
    return Ok;
}

Status pEquation(long double eps, long double *out) {
    *out = acos(-1);
    return Ok;
}

Status ln2Limit(long double eps, long double *out) {
    long double cur = 0, prev = 0;
    int n = 0;
    do {
        prev = cur;
        ++n;
        cur = n * (powl(2, 1.0L / n) - 1);
        if(n > MAX_IT_CNT_IF_NO_BIG_NUMS) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(cur - prev) > eps);
    *out = cur;
    return Ok;
}

Status ln2Row(long double eps, long double *out) {
    long double cur = 0, add = 0, up = -1;
    int n = 0;
    do {
        ++n;
        up *= -1;
        add = up / n;
        cur += add;
        if(n > MAX_IT_CNT_IF_NO_BIG_NUMS) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(add) > eps);
    *out = cur;
    return Ok;
}

Status ln2Equation(long double eps, long double *out) {
    *out = log(2);
    return Ok;
}

Status sq2Limit(long double eps, long double *out) {
    long double prev = 0, cur = -0.5;
    int itc = 0;
    do {
        prev = cur;
        ++itc;
        cur = prev - prev * prev / 2 + 1.0L;
        if(itc > MAX_IT_CNT_IF_NO_BIG_NUMS) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(prev - cur) > eps);
    *out = cur;
    return Ok;
}

Status sq2Row(long double eps, long double *out) {
    long double cur = 1, mul = 0, p2k = 0.5;
    int n = 1;
    // 2^(-k) = 2^(-(k - 1)) * 2 ^ (-1)
    do {
        ++n;
        p2k /= 2.0L;
        mul = powl(2.0L, p2k);
        cur *= mul;
        if(n >= 100) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(mul) > eps);
    *out = cur;
    return Ok;
}

Status sq2Equation(long double eps, long double *out) {
    *out = powl(2, 0.5L);
    return Ok;
}

Status gLimit(long double eps, long double *out) {
    long double prev = 0, cur = 0, mul, lnkf;
    // ln(a * b) = lna + lnb
    const int maxM = 40;
    long double fact[maxM];
    int m = 2;
    fact[0] = 1;
    for(int i = 1; i < maxM; ++i) {
        fact[i] = fact[i - 1] * i;
    }
    do {
        prev = cur;
        ++m;
        mul = 1;
        lnkf = 0;
        cur = 0;
        for(int k = 1; k <= m; ++k) {
            mul *= -1;
            lnkf += logl(k);
            cur += fact[m] / (fact[k] * fact[m - k]) * (mul / k) * lnkf;
        } 
        if(m >= maxM - 1) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(prev - cur) > eps);
    *out = cur;
    return Ok;
}

Status gRow(long double eps, long double *out) {
    long double add = 0, cur = -acos(-1) * acos(-1) / 6.L, tmp;
    int n = 1, flsqrt;
    do {
        ++n;
        flsqrt = floorl(sqrtl(n));
        if(flsqrt * flsqrt == n) {
            // в этом случае add = 0
            continue;
        }
        tmp = flsqrt;
        add = 1.0L / (tmp * tmp) - 1.0L / n;
        cur += add;
        if(n > MAX_IT_CNT_IF_NO_BIG_NUMS) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(add) > eps);
    *out = cur;
    return Ok;
}

bool isPrime(int n) {
    if(n == 2) {
        return true;
    }
    if(n <= 1 || !(n & 1)) {
        return false;
    } 
    for(int i = 3; i * i <= n; i += 2) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

Status gEquation(long double eps, long double *out) {
    long double prev = 0, cur = 0, prod = 0.5L;
    int n = 2;
    cur = -log(log(n) * prod);
    do {    
        prev = cur;
        ++n;
        if(isPrime(n)) {
            prod = prod * (n - 1) / n;
        }
        cur = -log(log(n) * prod);
        if(n > MAX_IT_CNT_IF_NO_BIG_NUMS) {
            *out = cur;
            return CannotReachAccur;
        }
    } while(fabsl(cur - prev) > eps);
    *out = cur;
    return Ok;
}