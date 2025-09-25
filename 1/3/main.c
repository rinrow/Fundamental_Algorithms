#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "include/Parser.h"
#include "include/ErrorHandler.h"
#include "include/Operations.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Некорректное число аргументов\n");
        return 0;
    }
    char fl;
    long double vals[4], eps = 1e-9;
    if (process(parseFlag(argv[1], &fl)) != Ok) {
        return 0;
    }
    Status status;
    switch (fl) {
    case 'q':
        if (argc != 6) {
            printf("Некорректное число аргументов\n");
            break;
        }
        if (process(parseVals(argv + 2, 4, vals)) != Ok) {
            break;
        }
        if(vals[0] < 0) {
            printf("Было введено отрицательное эпсилон!\n");
            break;
        }
        long double sols[6][6];
        int n;
        if (process(getAllSollutions(vals[0], vals + 1, sols, &n)) != Ok) {
            break;
        }
        for(int i = 0; i < n; ++i) {
            printf("Для коэф %Lf %Lf %Lf ", sols[i][0], sols[i][1], sols[i][2]);
            if (isinf(sols[i][3])) {
                printf("Бесконечное колво корней\n");
            } else if (cmp(sols[i][3], 0, eps)) {
                printf("Нету вещественных корней\n");
            } else if(cmp(sols[i][3], 1, eps)) {
                printf("Один корень: %Lf\n", sols[i][4]);
            } else {
                printf("Два корня : %Lf, %Lf\n", sols[i][4], sols[i][5]);
            }
        }
        break;
    case 'm':
        if (argc != 4) {
            printf("Некорректное число аргументов\n");
            break;
        }
        if (process(parseVals(argv + 2, 2, vals)) != Ok) {
            break;
        }
        bool mul;
        if (process(isMultiple(vals[0], vals[1], &mul)) != Ok) {
            break;
        }
        if(mul) {
            printf("Первое число кратно второму\n");
        } else {
            printf("Первое число не кратно второму\n");
        }
        break;
    case 't':
        if (argc != 6) {
            printf("Некорректное число аргументов\n");
            break;
        }
        if(process(parseVals(argv + 2, 4, vals)) != Ok) {
            break;
        }
        if(vals[0] < 0) {
            printf("Было введено отрицательное эпсилон!\n");
            break;
        }
        bool tr;
        if (process(isTriangle(vals[0], vals[1], vals[2], vals[3], &tr)) != Ok) {
            break;
        }
        if(tr) {
            printf("Сущесвтует прямоугольный треугольник с данными сторонами\n");
        } else {
            printf("Не сущесвтует прямоугольного треугольника с данными сторонами\n");
        }
        break;
    default:
        printf("Такого флага нету\n");
        break;
    }
}