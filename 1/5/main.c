#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/Parser.h"
#include "include/ErrorHandler.h"
#include "include/Operations.h"

int main(int argc, char **argv) {
    printf("Убедитесь в том что входной файл не содержит кирилицу и другие литеры которые записываются более чем двумя байтами\n");
    printf("Иначе эти литеры будут восприняты за два символа\n");
    if(argc < 3 || argc > 4) {
        printf("Некорректное кол-во аргументов\n");
        return 0;
    }
    bool hasN;
    char fl;
    if(process(parseFlag(argv[1], &fl, &hasN)) == HasException) {
        return 0;
    }
    FILE* toRead = fopen(argv[2], "r");
    if(toRead == NULL) {
        printf("Не смогли открыть для чтения данных\n");
        return 0;
    }
    FILE* toWrite;
    if(hasN) {
        if(argc != 4) {
            printf("Не передан файл для записи\n");
            fclose(toRead);
            return 0;
        }
        toWrite = fopen(argv[3], "w");
    } else {
        if(argc != 3) {
            printf("Некорректное кол-во аргументов\n");
            fclose(toRead);
            return 0;
        }
        if(strlen(argv[2]) >= BUFSIZ) {
            printf("Длина введенного файла слишком большая. Название не помещается в буфер!\n");
            fclose(toRead);
            return 0;
        }
        // идем справа налево когда находим первый / перед ним дописываем out_
        char buf[BUFSIZ];
        strcpy(buf, argv[2]);
        int pathLen = strlen(buf), nameSt = 0;
        for(int i = pathLen - 1; i >= 0; --i) {
            if(buf[i] == '/') {
                nameSt = i + 1;
                break;
            }
        }
        // Если нету / был передан относительный путь -> nameSt = 0
        // buf[nameSt : pathLen] -- сдвинуть вправо на 4
        for(int i = pathLen; i >= nameSt; --i) {
            buf[i + 4] = buf[i];
        }
        char *pref = "out_";
        for(int i = 0; i < 4; ++i) {
            buf[nameSt + i] = pref[i];
        }
        toWrite = fopen(buf, "w");
    }
    if(toWrite == NULL) {
        printf("Не удалось открыть/создать файл для записи\n"); // ?
        fclose(toRead);
        return 0;
    }
    switch (fl) {
    case 'd':
        process(dOp(toRead, toWrite));
        break;
    case 'i':
        process(iOp(toRead, toWrite));
        break;
    case 's':
        process(sOp(toRead, toWrite));
        break;
    case 'a':
        process(aOp(toRead, toWrite));
        break;
    default:
        break;
    }
    fclose(toRead);
    fclose(toWrite);
    return 0;
}