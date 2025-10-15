#include <stdio.h>
#include "./include/Solve.h"
#include "./include/Status.h"

int main() {
    FILE *fin, *fout;
    char finName[BUFSIZ], foutName[BUFSIZ];
    printf("Введите путь к входному файлу\n");
    scanf("%s", finName);
    printf("Введите путь к выходному файлу\n");
    scanf("%s", foutName);
    fin = fopen(finName, "r");
    if(fin == NULL) {
        printf("Ошибка при открытии входного файла\n");
        return 0;
    }
    fout = fopen(foutName, "w");
    if(fout == NULL) {
        printf("Ошибка при открытии выходного файла\n");
        fclose(fin);
        return 0;
    }
    if(operate(fin, fout) == BadWord) {
        printf("В переданном файле находиться некорректное слово\n");
        printf("Строку содержащую такое слово нельзя разбить на строки по 80 символов согласно ТЗ\n");
    }
    fclose(fin);
    fclose(fout);
    return 0;
}