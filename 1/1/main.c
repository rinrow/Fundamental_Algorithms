#include <stdlib.h>
#include <stdio.h>
#include "include/ArgwParser.h"
#include "include/Operations.h"
// #include "include/Status.h"

int main(int argc, char **argw) {
    if(argc != 3) {
        printf("Не корректное число аргументов\n");
        return -1;
    }
    long long x;
    char fl;
    int pfStatus = parseFlag(argw[2], &fl), pnStatus = parseNum(argw[1], &x); 
    if(pfStatus == InvalidInput || pnStatus == InvalidInput) {
        printf("Некорректные данные\n");
        return -1;
    }
    if(pnStatus == LongOverflow) {
        printf("Введено слишком большое число\n");
        return -1;
    }
    if(fl == 'h') if(hOp(x) != Succes) printf("Что-то не так с числом\n");
    if(fl == 'p') if(pOp(x) != Succes) printf("Что-то не так с числом\n");
    if(fl == 's') if(sOp(x) != Succes) printf("Что-то не так с числом\n");
    if(fl == 'e') if(eOp(x) != Succes) printf("Что-то не так с числом\n");
    if(fl == 'a') if(aOp(x) != Succes) printf("Что-то не так с числом\n");
    if(fl == 'f') if(fOp(x) != Succes) printf("Что-то не так с числом\n");
    return 0;
}