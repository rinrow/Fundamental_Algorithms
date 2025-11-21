#include "../include/Interactive.h"
#include "../include/InteractFuncs.h"
#include "../include/LinkedList.h"
#include "../include/Command.h"
#include <stdio.h>
#include <stdlib.h>

void printInputInfo() {
    printf("\
============== МЕНЮ ==============\n\
    Для поиска жителя введите 1\n\
    Для изменения сущ. жителя введите 2\n\
    Для удаления сущ. жителя введите 3\n\
    Для добавления жителя введите 4\n\
    Для выгрузки всех данных из списка введите 5\n\
    Для отмены половины последних операций введите 6\n\
    Для выхода введите 0\n\
================================\n\n");
}

typedef void(*operFunc)(LinkedList* livers, LinkedList* st);

void empty(LinkedList* livers, LinkedList* st) {}

void start() {
    FILE* in;
    char inName[200];
    printf("Введите файл для чтения\n");
    scanf("%s", inName);
    in = fopen(inName, "r");
    if(!in) {
        printf("не удалось открыть файл\n");
        return;
    }
    int oper = -1, readed;
    LinkedList livers = create_list(), st = create_list();
    readAllLivers(in, &livers);
    printf("Жители из файла прочитаны\n");
    operFunc funcs[] = {empty, searchLiver, changeLiver, deleteLiver, addLiver, printLivers, undoHalfN};
    do {    
        printInputInfo();
        readed = scanf("%d", &oper);
        if(readed != 1 || oper < 0 || oper > 6) {
            printf("Нет такой команды!\n");
            clearInBuffer(); // в случае если на вход поступила строка, нужно сброс буфер
            continue;
        }
        funcs[oper](&livers, &st);
    } while(oper);
    freeStack(&st);
    delete_list(&livers);
    fclose(in);
}