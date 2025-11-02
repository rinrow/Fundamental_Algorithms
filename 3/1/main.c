#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./include/Func.h"

int main() {
    char buf[50];
    char *out;

    printf("1. Тест с нулем\n");
    out = toBase(0, 2, buf);
    printf("входные данные: number=0, r=2\n");
    printf("ожидаемые выходные данные: 0\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "0") == 0 ? "PASS" : "FAIL");
    
    printf("2. Тест с основанием 2\n");
    out = toBase(5, 1, buf);
    printf("входные данные: number=5, r=1\n");
    printf("ожидаемые выходные данные: 101\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "101") == 0 ? "PASS" : "FAIL");
    
    printf("3. Тест с основанием 4\n");
    out = toBase(10, 2, buf);
    printf("входные данные: number=10, r=2\n");
    printf("ожидаемые выходные данные: 22\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "22") == 0 ? "PASS" : "FAIL");
    
    printf("4. Тест с основанием 8\n");
    out = toBase(15, 3, buf);
    printf("входные данные: number=15, r=3\n");
    printf("ожидаемые выходные данные: 17\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "17") == 0 ? "PASS" : "FAIL");
    
    printf("5. Тест с основанием 16\n");
    out = toBase(27, 4, buf);
    printf("входные данные: number=27, r=4\n");
    printf("ожидаемые выходные данные: 1B\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "1B") == 0 ? "PASS" : "FAIL");
    
    printf("6. Тест с основанием 32\n");
    out = toBase(42, 5, buf);
    printf("входные данные: number=42, r=32\n");
    printf("ожидаемые выходные данные: 1A\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "1A") == 0 ? "PASS" : "FAIL");
    
    printf("7. Тест с большим числом\n");
    out = toBase(255, 2, buf);
    printf("входные данные: number=255, r=2\n");
    printf("ожидаемые выходные данные: 3333\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "3333") == 0 ? "PASS" : "FAIL");
    
    printf("8. Тест с r = 2\n");
    out = toBase(-1, 2, buf);
    printf("входные данные: number=-1, r=2\n");
    printf("ожидаемые выходные данные: -1\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "-1") == 0 ? "PASS" : "FAIL");
    
    printf("9. Тест с основанием 4 для числа 7\n");
    out = toBase(7, 2, buf);
    printf("входные данные: number=7, r=2\n");
    printf("ожидаемые выходные данные: 13\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "13") == 0 ? "PASS" : "FAIL");

    printf("10. Тест с основанием 16 для числа -296818\n");
    out = toBase(-296818, 4, buf);
    printf("входные данные: number=-296818, r=5\n");
    printf("ожидаемые выходные данные: -48772\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "-48772") == 0 ? "PASS" : "FAIL");

    printf("11. Тест с основанием 32 для числа 22866\n");
    out = toBase(22866, 5, buf);
    printf("входные данные: number=22866, r=5\n");
    printf("ожидаемые выходные данные: MAI\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "MAI") == 0 ? "PASS" : "FAIL");

    printf("12. Тест с основанием 32 для числа 510557\n");
    out = toBase(510557, 5, buf);
    printf("входные данные: number=510557, r=5\n");
    printf("ожидаемые выходные данные: FIIT\n");
    printf("что вывела программа: %s\n", out);
    printf("вердикт: %s\n\n", strcmp(out, "FIIT") == 0 ? "PASS" : "FAIL");
}