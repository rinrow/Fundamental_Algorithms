#include <stdio.h>
#include <stdlib.h>
#include "./include/Student.h"
#include "./include/Sol.h"
#include "./include/ErrorHandler.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Некорректно число аргументов\n");       
        return 0;
    }
    FILE* in = fopen(argv[1], "r"), *out;
    if (!in) {
        printf("Не удалось открыть файл для чтения\n");
        return 0;
    }
    out = fopen(argv[2], "w");
    if (!out) {
        printf("Не удалось открыть файл для записи\n");
        fclose(in);
        return 0;
    }
    Student **studs;
    Status stat;
    int sz;
    studs = readStuds(in, &stat, &sz);
    if (process(stat) == Ok) {
        interact(studs, sz, out);
    }
    freeStud(studs, sz);
    fclose(in);
    fclose(out);
    return 0;
}