#include <stdio.h>
#include <ctype.h>
#include "../include/Status.h"

#define max(a, b) ((a > b) ? (a): (b))

int getNum(char ch) {
    if(isdigit(ch)) {
        return ch - '0';
    } else if(isupper(ch)) {
        return 10 + ch - 'A';
    } else {
        return 10 + ch - 'a';
    }
}

Status operate(char* buf, FILE* out) {
    // макс символ + 1 -> основание минимальной сс
    int mx = 1, i, len;
    int st = 0;
    if(buf[0] == '-') {
        st = 1;
    }
    for(i = st; buf[i]; ++i) {
        if(!isalnum(buf[i])) {
            return UnocorrectNum;
        }
        mx = max(mx, getNum(buf[i]));
    }
    ++mx;
    len = i;
    i = st;
    while(buf[i] == '0') { 
        ++i;
    }
    if(buf[0] == '-' && buf[i]) {
        fputc('-', out);
    }
    if(!buf[i]) { // число 0
        fputc('0', out);
    } else {
        for(; buf[i]; ++i) {
            fputc(buf[i], out);
        }
    }
    fprintf(out, " %d ", mx);
    long long num = 0;
    i = st;
    for(; buf[i]; ++i) {
        // num * mx + c >= longmx
        // num >= (longmx - c) / mx
        if(num >= (__LONG_LONG_MAX__ - getNum(buf[i])) / mx) {
            return LongOverflow;
        }
        num = num * mx + getNum(buf[i]);
    }
    if(buf[0] == '-') {
        num *= -1;
    }
    fprintf(out, "%lld\n", num);
    return Ok;
}