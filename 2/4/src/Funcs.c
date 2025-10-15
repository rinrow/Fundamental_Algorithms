#include "../include/Status.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define max(a, b) (a > b ? (a): (b))

void toRroman(char* buf, int num) {
    int i = 0, j, written = 0, len;
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
    *buf = 0;
    return;
}

Status fromRoman(const char *roman, int *res) {
    int values[256] = {0};
    values['I'] = 1;
    values['V'] = 5;
    values['X'] = 10;
    values['L'] = 50;
    values['C'] = 100;
    values['D'] = 500;
    values['M'] = 1000;
    int total = 0;
    int prev = 0;
    int current;
    for (int i = strlen(roman) - 1; i >= 0; i--) {
        current = values[roman[i]];
        if (current == 0) {
            return CannotBeRoman;  
        }
        if (current < prev) {
            total -= current;  
        } else {
            total += current;
        }
        prev = current;
    }
    // Проверяем, что число в допустимом диапазоне
    if (total < 1 || total > 3999) {
        return CannotBeRoman;
    }
    *res = total;
    return Ok;
}

Status Ro(const char* buf, int *rd, va_list l) {
    int mxCnt = 30;
    char romstr[mxCnt], *ptr = romstr;
    int len = 0, *res = va_arg(l, int *);
    while(len < mxCnt && !isspace(*buf) && *buf) {
        *ptr++ = *buf++;
        ++len;
    }
    *ptr = 0;
    *rd = len;
    if(len == mxCnt) {
        return CannotBeRoman;
    }
    fromRoman(romstr, res);
    char tmp[mxCnt];
    toRroman(tmp, *res);
    if(strcmp(romstr, tmp)) {
        *res = -1;
        return CannotBeRoman;
    };
    return Ok;
}

// 4 млрд -> макс 49 чисел 
Status Zr(const char* buf, int *rd, va_list l) {
    int maxCnt = 50, i;
    char tmp[maxCnt], *ptr = tmp;
    unsigned int *res = va_arg(l, unsigned int *);
    int len = 0;
    while(len < maxCnt && !isspace(*buf) && *buf) {
        if((*buf != '1' && *buf != '0')) {
            return UncorrectZec;
        }
        *ptr++ = *buf++;
        ++len;
    }
    if(len == maxCnt) {
        return IntOverflow;
    }
    *rd = len;
    --len; // не читаем терминирующую единицу
    if(!len || *(ptr - 1) != '1') {
        return UncorrectZec;
    }
    long long fib[maxCnt];
    fib[0] = 1;
    fib[1] = 2;
    for(i = 2; i < maxCnt; ++i) {
        fib[i] = fib[i - 2] + fib[i - 1];
    }
    *res = 0;
    for(i = 0; i < len; ++i) {
        *res += fib[i] * (tmp[i] == '1');
    }
    return Ok;
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

Status fromBase(int *res, char *n, int base, bool up) {
    bool neg = n[0] == '-';
    Status cor = validateNum(n, base, up);
    if(cor != Ok) {
        return cor;
    }
    int num = 0;
    for(int i = n[0] == '-'; n[i]; ++i) {
        // num * mx + c >= longmx
        // num >= (longmx - c) / mx
        if(num >= (__INT_MAX__ - getNum(n[i])) / base) {
            return IntOverflow;
        }
        num = num * base + getNum(n[i]);
    }
    if(n[0] == '-') {
        num *= -1;
    }
    *res = num; 
    return Ok;
}

Status cvMain(const char* buf, int *rd, va_list l, bool up) {
    int *res = va_arg(l, int*), base = va_arg(l, int);
    if(base < 2 && base > 36) {
        base = 10;
    }
    char num[20], *ptr = num;
    int len = 0;
    while(len < 20 && !isspace(*buf) && *buf) {
        *ptr++ = *buf++;
        ++len;
    }
    *ptr = 0;
    if(len == 20) {
        return IntOverflow;
    }
    *rd = len;
    return fromBase(res, num, base, up);
}

Status Cv(const char* buf, int *rd, va_list l) {
    return cvMain(buf, rd, l, false);
}

Status CV(const char* buf, int *rd, va_list l) {
    return cvMain(buf, rd, l, true);
}