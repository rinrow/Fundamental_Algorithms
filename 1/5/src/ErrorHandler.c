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
    case ErrorWhenWrite: 
        printf("При записи в файл получили статут EOF!\n");
        break;
    case UncorrectFlag:
        printf("Некорректный флаг!\n");
        break;
    default: 
        printf("Некоторая ошибка\n");
        break;
    }
    return HasException;
}