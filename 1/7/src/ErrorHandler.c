#include "../include/Status.h"
#include "../include/ErrorHandler.h"
#include <stdio.h>

Status process(Status st) {
    switch (st) {
    case Ok:
        return Ok;
    case UnocorrectNum:
        printf("Введено некорректное число!\n");
        break;
    case LongOverflow: 
        printf("Было введено слишком большое число, котрое не влезает в целочисленный тип!\n");
        break;
    default: 
        printf("Некоторая ошибка\n");
        break;
    }
    return HasException;
}