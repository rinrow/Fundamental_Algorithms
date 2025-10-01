#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "./include/Operations.h"
#include "./include/ErrorHandler.h"

int main(int argc, char **argv) {
    printf("Введите основание сс\n");
    int base;
    if(scanf("%d", &base) != 1) {
        printf("Не удалось считать число\n");
        return 0;
    }
    if(base < 2 || base > 36) {
        printf("Сс должна быть в диап [2:36]\n");
        return 0;
    }
    printf("Вводите числа(числа должны содержать 1-9, A-Z)\n");
    printf("Другие символы (кроме строчных литиниц) будет обработаны как разделители\n");
    int cur, prev = 0;
    char buf[BUFSIZ];
    char *ptr = buf, *stop = "Stop";
    long long mx = 0;
    bool wasN = false;
    do {
        cur = getc(stdin);
        if(ptr - buf >= BUFSIZ - 1) {
            printf("Ошибка!!! Слишком большое число, не влезает в буффер!!!!\n");
            return 0;
        }
        if(isalnum(cur) || cur == '-') {
            *ptr++ = cur;
        } else if (isalnum(prev)){
            // buf хранит слово
            *ptr = 0;
            if(!strcmp(buf, stop)) {
                break;
            }
            if(process(operate(buf, &mx, base)) == HasException) {
                return 0;
            }
            wasN = true;
            ptr = buf;
        }
        prev = cur;
    } while(cur != EOF);
    if(!wasN) {
        printf("В введенных данных нету чисел\n");
        return 0;
    }
    getInBase(mx, base, &ptr, buf);
    printf("Максимальное число по модулю -- %s\n", ptr);
    int bases[] = {9, 18, 27, 36};
    for(int i = 0; i < 4; ++i) {
        getInBase(mx, bases[i], &ptr, buf);
        printf("Это число в сс с основанием %d -- %s\n", bases[i], ptr);
    }
    return 0;
}