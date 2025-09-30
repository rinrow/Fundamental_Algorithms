#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "include/Calculations.h"
#include "include/Status.h"

void printWaringIfNeed(Status st) {
    if(st == CannotReachAccur) {
        printf("Было введено слишком малое эпсилон, возможно посчитанное значение не удволетворяет заданной точности!\n");
    }
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Некорректное число аргументов\n");
        return 0;
    }
    errno = 0;
    char *end = NULL;
    long double eps = strtold(argv[1], &end);
    if(errno == ERANGE || *end != '\0' || end == argv[1]) {
        printf("Не смогли корректно прочитать eps!\n");
        return 0;
    }
    if (eps < 0) {
        printf("Ошибка! eps должен быть положительным!\n");
        return 0;
    }
    long double a = 0.0, b = 1.0;

    long double ansA, ansB, ansC, ansD;

    printWaringIfNeed(calc(fa, eps, a, b, &ansA));
    printf("интеграл ln(1+x)/x равен %.15Lf\n", ansA);

    printWaringIfNeed(calc(fb, eps, a, b, &ansB));
    printf("интеграл e^(-x^2/2) равен %.15Lf\n", ansB);

    printWaringIfNeed(calc(fc, eps, a, b - 2.L * eps, &ansC));
    printf("интеграл ln(1/(1-x)) равен %.15Lf\n", ansC);

    printWaringIfNeed(calc(fd, eps, a, b, &ansD));
    printf("интеграл x^x равен%.15Lf\n", ansD);

    return 0;
}