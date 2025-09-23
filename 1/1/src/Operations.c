#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/Status.h"

int hOp(long long x) {
    // Из интернета: положительное число на отрицательное не кратно
    if(x <= 0 || x > 100) {
        printf("диапазон [1: 100] не содержит чисел кратных x\n");
    } else {
        for(int i = x; i <= 100; i += x) {
            printf("%d ", i);
        }
        printf("\n");
    }
    return Succes;
}

int pOp(long long x) {
    // Из интернета: Разделение на простые и составные числа принято для натуральных чисел
    // 1 не просте и не составное поэтому не можем определить
    if(x <= 1) {
        return InvalidInput;
    }
    for(long long i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            printf("Число является составным\n");
            return Succes;
        }
    }
    printf("Число простое\n");
    return Succes;
}

int sOp(long long x) {
    // long long до 10^18 - 18 цифр максимально -> в 16 записи <= 18 цифр
    bool neg = 0;
    if(x < 0) { 
        neg = 1;
        x = -x;
    }
    char str[18];
    int ind = 0;
    while(x) {
        int num = x % 16;
        x /= 16;
        str[ind++] = (num >= 10 ? 'A' + num - 10: '0' + num);
    }
    if(neg) {
        printf("-%c ", str[--ind]);
    }
    while(ind) {
        printf("%c ", str[--ind]);
    }
    printf("\n");
    return Succes;
}

int eOp(long long x) {
    // в задании "диапазоне от 1 до x" - т.е предпол что x >= 1
    if(x > 10 || x < 1) {
        return InvalidInput;
    }
    long long num;
    for(int i = 1; i <= 10; i++) {
        num = 1;
        printf("Степени числа %d от 1 до %lld: ", i, x);
        for(int j = 1; j <= x; j++) {
            num *= i;
            printf(" %lld", num);
        }
        printf("\n");
    }
    return Succes;
}

int aOp(long long x) {
    // В задании от 1 до x т.е предпол что x >= 1
    // так как при умножении больших чисел возможно переполнение то будем принмать x <= 10^9
    if(x < 1 || x > 1e9) {
        return InvalidInput;
    }
    unsigned long long res = (1 + x) * x / 2;
    printf("%llu\n", res);
    return Succes;
}

int fOp(long long x) {
    // так как 21! - это переполение то принимаем только x : [0: 20]
    if(x < 0 || x > 20) {
        return InvalidInput;
    }
    unsigned long long res = 1;
    for(int i = 1; i <= x; i++) {
        res *= i;
    }
    printf("%llu\n", res);
    return Succes;
}