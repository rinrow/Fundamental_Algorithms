#include "../include/Func.h"
#include <stdbool.h>

char* toBase(int n, int r, char* buf) {
    // n / (2**r)  <=>  n >> r
    // n % (2**r)  <=>  n & ((1 << r) - 1)
    char *ptr = buf + 40;
    *ptr-- = '\0';
    char *letters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int tmp = ((1 << r) - 1);
    bool neg = false;
    if(n < 0) {
        neg = true;
        n *= -1;
    }   
    if(!n) {
        *ptr-- = '0';
    }
    while(n) {
        *ptr-- = letters[n & tmp];
        n >>= r;
    }
    if(neg) {
        *ptr-- = '-';
    }
    return 1 + ptr;
}