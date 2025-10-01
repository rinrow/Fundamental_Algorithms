#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/Status.h"

#define max(a, b) ((a > b) ? (a): (b))

int getNum(char ch) {
    if(isdigit(ch)) {
        return ch - '0';
    } 
    return 10 + ch - 'A';
}

char toDigit(int num) {
    if(num <= 9) {
        return num + '0';
    }
    return num - 10 + 'A';
}

Status operate(char* buf, long long *mx, int base) {
    int i, st = 0;
    if(buf[0] == '-') {
        st = 1;
    }
    i = st;
    while(buf[i] == '0') { // убираем ведущие нули
        ++i;
    }
    long long num = 0;
    int curN;
    for(i = st; buf[i]; ++i) {
        // num * base + c >= longmx
        // num >= (longmx - c) / base
        if(islower(buf[i])) {
            return NumHasLower;
        }
        curN = getNum(buf[i]);
        if(curN >= base) {
            return NotInBase;
        }
        if(num >= (__LONG_LONG_MAX__ - curN) / base) {
            return LongOverflow;
        }
        num = num * base + curN;
    }
    if(buf[0] == '-') {
        num *= -1;
    }
    if(llabs(num) > llabs(*mx)) {
        *mx = num;
    }
    return Ok;
}

Status getInBase(long long num, int base, char **out, char *buf) {
    // для двоичной 64 цифр для других меньше
    char *ptr = buf + 65;
    *ptr = 0;
    bool isNeg = false;
    if(num < 0) {
        isNeg = true;
        num *= -1;
    }
    if(!num) {
        *(--ptr) = '0';
    }
    while(num) {
        *(--ptr) = toDigit(num % base);
        num /= base;
    }
    if(isNeg) {
        *(--ptr) = '-';
    }
    *out = ptr;
    return Ok;
}