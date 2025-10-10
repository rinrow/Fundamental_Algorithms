#include "../include/Status.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define max(a, b) ((a > b) ? (a): (b))

Status Ro(char* buf, int *wr, va_list l) {
    int num = va_arg(l, int), i = 0, j, written = 0, len;
    if(num <= 0 || num > 3999) {
        return CannotBeRoman;
    }
    const char* lit[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int val[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    while(num) {
        len = strlen(lit[i]);
        while(num >= val[i]) {
            num -= val[i];
            for(j = 0; j < len; ++j, ++written) {
                *buf++ = lit[i][j];
            }
        }
        ++i;
    }
    *wr = written;
    return Ok;
}

Status Zr(char* buf, int *wr, va_list l) {
    unsigned int n = va_arg(l, unsigned int);
    // n до 4млрд -> хватит 49 чисел фиббонач
    int maxCnt = 50, i;
    long long fib[maxCnt];
    // кор послед 1 2 3 5
    // т.к в случ 1 1 2 3 5 -> предс не ед (можем взять как первую так и вторую ед)
    fib[0] = 1;
    fib[1] = 2;
    for(i = 2; i < maxCnt; ++i) {
        fib[i] = fib[i - 2] + fib[i - 1];
    }
    char tmp[50];
    for(i = maxCnt - 1; i >= 0; --i) {
        if(fib[i] <= n) {
            tmp[i] = '1';
            n -= fib[i];
            if(i) {
                tmp[--i] = '0';
            }
        } else {
            tmp[i] = '0';
        }
    }
    for(; maxCnt > 1 && tmp[maxCnt - 1] == '0'; --maxCnt);   
    for(i = 0; i < maxCnt; ++i) {
        *buf++ = tmp[i];
    }
    *buf++ = '1';
    *wr = maxCnt + 1;
    return Ok;
}

char getLit(int n, int b) {
    int rem = n % b; 
    return rem >= 10 ? 'a' + rem - 10: '0' + rem;
}

// Берет число переводит в сс записывает в буфер
Status toBase(char* buf, int* wr, long long n, int base, bool up) {
    if(base < 2 || base > 36) {
        base = 10;
    }
    bool neg = false;
    if(n < 0) {
        neg = true;
        n *= -1;
    }
    char tmp[40];
    char *ptr = tmp;
    if(!n) {
        *ptr++ = '0';
    }
    while(n) {
        *ptr++ = (up ? toupper: tolower)(getLit(n, base));
        n /= base;
    }
    if(neg) {
        *ptr++ = '-';
    }
    *wr = ptr - tmp;
    while(ptr != tmp) {
        *buf++ = *--ptr;
    }
    return Ok;
}

Status Cv(char* buf, int *wr, va_list l) {
    int n = va_arg(l, int), base = va_arg(l, int);
    return toBase(buf, wr, n, base, false);
}

Status CV(char* buf, int *wr, va_list l) {
    int n = va_arg(l, int), base = va_arg(l, int);
    return toBase(buf, wr, n, base, true);
}

int getNum(char ch) {
    if(isdigit(ch)) {
        return ch - '0';
    } else if(isupper(ch)) {
        return 10 + ch - 'A';
    } else {
        return 10 + ch - 'a';
    }
}

Status validateNum(char* n, int base, bool up) {
    if(!n[0]) {
        return UncorrectNum;
    }
    int st = 0, i, mx = 0;
    for(i = n[0] == '-'; n[i]; ++i) {
        if(!isalnum(n[i])) {
            return UncorrectNum;
        }
        if(isupper(n[i]) && !up) {
            return ShouldBeLower;
        }
        if(islower(n[i]) && up) {
            return ShouldBeUpper;
        }
        mx = max(mx, getNum(n[i]));
    }
    if(mx >= base) {
        return NotInBase;
    }
    return Ok;
}

Status fromBase(char* buf, int* wr, va_list l, bool up) {
    char* n = va_arg(l, char*);
    int base = va_arg(l, int);
    if(base < 2 || base > 36) {
        base = 10;
    }
    bool neg = n[0] == '-';
    Status cor = validateNum(n, base, up);
    if(cor != Ok) {
        return cor;
    }
    long long num = 0;
    for(int i = n[0] == '-'; n[i]; ++i) {
        // num * mx + c >= longmx
        // num >= (longmx - c) / mx
        if(num >= (__LONG_LONG_MAX__ - getNum(n[i])) / base) {
            return LongOverflow;
        }
        num = num * base + getNum(n[i]);
    }
    if(n[0] == '-') {
        num *= -1;
    }
    toBase(buf, wr, num, 10, false);
    return Ok;
}

Status to(char* buf, int *wr, va_list l) {
    return fromBase(buf, wr, l, false);
}

Status TO(char* buf, int *wr, va_list l) {
    return fromBase(buf, wr, l, true);
}

Status getDump(char* buf, int *wr, unsigned char *pi, int bcnt) {
    for(int i = 0; i < bcnt; ++i) {
        for(int j = 7; j >= 0; --j) {
            *buf++ = (*pi & (1 << j)) ? '1': '0';
        }
        if(i != bcnt - 1) {
            *buf++ = ' ';
        }
        ++pi;
    }
    *wr = bcnt * 8 + bcnt - 1;
    return Ok;
}

Status mi(char* buf, int *wr, va_list l) {
    int n = va_arg(l, int);
    return getDump(buf, wr, (unsigned char *)&n, sizeof(int));
}

Status mu(char* buf, int *wr, va_list l) {
    unsigned int n = va_arg(l, unsigned int);
    return getDump(buf, wr, (unsigned char *)&n, sizeof(unsigned int));
}

Status md(char* buf, int *wr, va_list l) {
    double n = va_arg(l, double);
    return getDump(buf, wr, (unsigned char *)&n, sizeof(double));
}

Status mf(char* buf, int *wr, va_list l) {
    float n = (float)va_arg(l, double);
    return getDump(buf, wr, (unsigned char *)&n, sizeof(float));
}