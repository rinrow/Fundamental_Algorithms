#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "include/ErrorHandler.h"
#include "include/Operations.h"

bool isCorrect(char cur, char prev) {
    if(!isalnum(cur) && cur != ' ' && cur != '\t' && cur != '\n' && cur != EOF && cur != '-') {
        return false;
    }
    return !isalnum(cur) <= (prev != '-');
}

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Некорректное кол-во аргументов\n");
        return 0;
    }
    FILE* toRead = fopen(argv[1], "r");
    if(toRead == NULL) {
        printf("Не смогли открыть файл для чтения данных\n");
        return 0;
    }
    FILE* toWrite;
    toWrite = fopen(argv[2], "w");
    if(toWrite == NULL) {
        printf("Не удалось открыть/создать файл для записи\n"); // ?
        fclose(toRead);
        return 0;
    }
    int cur, prev = 0;
    char buf[BUFSIZ];
    char *ptr = buf;
    do {
        cur = getc(toRead);
        if(!isCorrect(cur, prev)) { 
            printf("1Ошибка!!! Файл содержит символы о которых не сказано в ТЗ!!!!\n");
            break;
        }
        if(ptr - buf >= BUFSIZ - 1) {
            printf("Ошибка!!! Слишком большое число, не влезает в буффер!!!!\n");
            break;
        }
        if(isalnum(cur) || cur == '-') {
            *ptr++ = cur;
        } else if (isalnum(prev)){
            // buf хранит слово
            *ptr = 0;
            if(process(operate(buf, toWrite)) == HasException) {
                break;
            }
            ptr = buf;
        }
        prev = cur;
    } while(cur != EOF);
    fclose(toRead);
    fclose(toWrite);
    return 0;
}