#include "../include/Status.h"
#include "../include/ErrorHandler.h"
#include <stdio.h>

Status process(Status st) {
    switch (st) {
    case Ok:
        return Ok;
    case InvalidInput:
        printf("Введены некорректные данные!\n");
        break;
    case Zero: 
        printf("Был введен 0, а это некорректно!\n");
        break;
    case NotInteger: 
        printf("Было введено не целое число, а это некорректно!\n");
        break;
    case NegativeNum:
        printf("Было введено отрицательное число, а это некорректно!\n");
        break;
    case LongOverflow:
        printf("Было введено слишком большое число которое не помещается в целочисленный тип, а это некорректно!\n");
        break;
    }
    return HasException;
}