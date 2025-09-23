#include <stdio.h>
#include "include/NthPrime.h"
#include "include/Status.h"

int readNum(long long *px) {
    int status = Ok;
    int i = 0, mul = 1;
    char c = getchar();
    if(c == '\0') status = InvalidInput;
    if(c == '-') {
        mul = -1;
        i = 1;
        c = getchar();
        if(c == '\0') status = InvalidInput;
    } 
    long long res = 0;
    while(c != '\0' && c != '\n') {
        if(c < '0' || c > '9') {
            status = InvalidInput;
        }
        if(status != InvalidInput && res > (res * 10 + (long long)(c - '0'))) {
            status = LongOverflow;
        }
        res = res * 10 + (long long)(c - '0');
        c = getchar();
    }
    *px = res * mul;
    return status;
}

int main() {
    printf("asd\n");
    long long t, n;
    int status; 
    status = readNum(&t);
    if(t < 0) status = InvalidInput;
    if(status == InvalidInput) { printf("Некорректный формат ввода\n"); return -1; } 
    if(status == LongOverflow) { printf("Переполнение\n"); return -1; } 
    // Сложность алгоритма O(t * n * sqrt(n))
    while(t--) {
        // scnaf("%d", &n);
        status = readNum(&n);
        if(status == InvalidInput) { printf("Некорректный формат ввода\n"); continue; } 
        if(status == LongOverflow) { printf("Переполнение\n"); continue; } 
        if(n <= 0) {
            printf("n не натуральное -- непонятно что выводить\n");
            continue;
        }
        long long ans;
        if(getPrime(n, &ans) == LongOverflow) {
            printf("Число слишком большое чтобы поместиться в long long\n");
            continue;
        }
        printf("%lld\n", ans);
    }
    return 0;
}