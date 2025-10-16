#include "../include/Status.h"
#include "../include/ErrorHandler.h"
#include <stdio.h>

Status process(Status st) {
    switch (st) {
    case Ok:
        return Ok;
    case ErrorOnMalloc:
        printf("Ошибка при созданни студента!\n");
        break;
    case ErrorOnReading: 
        printf("Ошибка при чтении студента!\n");
        break;
    case ErrorOnRealloc: 
        printf("Ошибка при realloc!\n");
        break;
    default: 
        printf("Некоторая ошибка\n");
        break;
    }
    return HasException;
}