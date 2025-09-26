#include <stdlib.h>
#include <stdio.h>
#include "include/ConstantsCalcs.h"

void printWaringIfNeed(Status st) {
    if(st == CannotReachAccur) {
        printf("Было введено слишком малое эпсилон, возможно посчитанное значение не удволетворяет заданной точности!\n");
    }
}

int main() {
    printf("Введите точность вычислений eps\n");
    long double eps;
    if(scanf("%Lf", &eps) != 1) {
        printf("Ошибка! не смогли прочитать eps\n");
        return 0;
    }
    if(eps < 0) {
        printf("Ошибка! eps должен быть положительным\n");
        return 0;
    }
    long double elim, erow, eeq, plim, prow, peq, ln2lim, 
        ln2row, ln2eq, sq2lim, sq2row, sq2eq, glim, grow, geq;
    printf("Число e:\n");
    printWaringIfNeed(eLimit(eps, &elim));
    printf("Значение e помощью предела: %.10Lf\n\n", elim);
    
    printWaringIfNeed(eRow(eps, &erow));
    printf("Значение e помощью суммы: %.10Lf\n\n", erow);

    printWaringIfNeed(eEquation(eps, &eeq));
    printf("Значение e помощью уравнения: %.10Lf\n\n", eeq);
    
    printf("Число pi:\n");
    printWaringIfNeed(pLimit(eps, &plim));
    printf("Значение pi помощью предела: %.10Lf\n\n", plim);
    
    printWaringIfNeed(pRow(eps, &prow));
    printf("Значение pi помощью суммы: %.10Lf\n\n", prow);

    printWaringIfNeed(pEquation(eps, &peq));
    printf("Значение pi помощью уравнения: %.10Lf\n\n", peq);

    printf("Число ln2:\n");
    printWaringIfNeed(ln2Limit(eps, &ln2lim));
    printf("Значение ln2 помощью предела: %.10Lf\n\n", ln2lim);
    
    printWaringIfNeed(ln2Row(eps, &ln2row));
    printf("Значение ln2 помощью суммы: %.10Lf\n\n", ln2row);

    printWaringIfNeed(ln2Equation(eps, &ln2eq));
    printf("Значение ln2 помощью уравнения: %.10Lf\n\n", ln2eq);

    printf("Число sqrt2:\n");
    printWaringIfNeed(sq2Limit(eps, &sq2lim));
    printf("Значение sqrt2 помощью предела: %.10Lf\n\n", sq2lim);
    
    printWaringIfNeed(sq2Row(eps, &sq2row));
    printf("Значение sqrt2 помощью суммы: %.10Lf\n\n", sq2row);

    printWaringIfNeed(sq2Equation(eps, &sq2eq));
    printf("Значение sqrt2 помощью уравнения: %.10Lf\n\n", sq2eq);

    printf("Число g:\n");
    printWaringIfNeed(gLimit(eps, &glim));
    printf("Значение g помощью предела: %.10Lf\n\n", glim);
    
    printWaringIfNeed(gRow(eps, &grow));
    printf("Значение g помощью суммы: %.10Lf\n\n", grow);

    printWaringIfNeed(gEquation(eps, &geq));
    printf("Значение g помощью уравнения: %.10Lf\n\n", geq);
    return 0;
}