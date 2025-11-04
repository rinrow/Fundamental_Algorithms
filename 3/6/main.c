#include <stdio.h>
#include <stdlib.h>
#include "./include/solve.h"

int main() {
    printf("Введите строку в которой требуется проверить правильность расстановки скобок\n");
    char buf[BUFSIZ];
    scanf("%[^\n]", buf);
    printf("Расстановки скобок %sкорректна!\n", check_brackets(buf) ? "": "не");
    return 0;
}