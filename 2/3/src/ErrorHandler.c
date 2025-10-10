#include "../include/Status.h"
#include "../include/ErrorHandler.h"
#include <stdio.h>

Status process(Status st) {
    switch (st) {
    case Ok:
        return Ok;
    case UncorrectNum:
        printf("Некорректное число!\n");
        break;
    case CannotBeRoman: 
        printf("Не может быть римским!\n");
        break;
    case VSPFError: 
        printf("Ошибка при записи данных средствами std!\n");
        break;
    case LongOverflow: 
        printf("Слишком большое число, котрое не влезает в целочисленный тип!\n");
        break;
    case ShouldBeUpper: 
        printf("Ошибка!!! цифры > 9 должны вводиться как прописные!!!!\n");
        break;
    case NotInBase: 
        printf("Число не соответствует введенной сс!\n");
        break;
    case ShouldBeLower: 
        printf("Ошибка!!! цифры > 9 должны вводиться как строчные!!!!\n");
        break;
    default: 
        printf("Некоторая ошибка\n");
        break;
    }
    return HasException;
}