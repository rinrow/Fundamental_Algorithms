#include "../include/Scan.h"
#include "../include/Status.h"
#include "../include/Specs.h"
#include "../include/Funcs.h"
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

typedef Status (*func)(const char* buf, int *rd, va_list l);

void parseSpec(const char* str, Spec *sp, func *f) {
    // Стандарт все те кто не в ТЗ
    // Берем три штуки %..
    // Если не наши возвр Standart
    // Наши парсим возвр
    // str[0] = '%' str[1] str[2]
    *sp = Standart;
    if(!str[1]) {
        return;
    }
    char cur[] = {str[1], str[2], 0};
    char *names[] = {"Ro", "Zr", "Cv", "CV"};
    func funcs[] = {Ro, Zr, Cv, CV};
    for(int i = 0; i < 4; ++i) {
        if(!strcmp(names[i], cur)) {
            *sp = NotStandart;
            *f = funcs[i];
            return;
        }
    }
}

int overformat(const char *str, char *format, va_list l) {
    Spec sp;
    Status st;
    func f;
    char bufSt[BUFSIZ], *ptrSt = bufSt;
    int readed, out = 0, readedFromStr;
    while(*format) {
        if(!*str) {
            return -UncorrectFormat;
        }
        if(isspace(*format)) {
            // проп все проб подряд в str
            while(*str && isspace(*str)) {
                ++str;
            }
            ++format;
            continue;
        }
        if(*format != '%') {
            // должны быть равны
            if(*format != *str) {
                return -NotInFormat;
            }
            ++format, ++str;
            continue;
        }
        parseSpec(format, &sp, &f);
        if(sp == Standart) {
            do {
                *ptrSt++ = *format++;
            } while(*format && *format != '%' && !isspace(*format));
            void * arg = va_arg(l, void *);
            strcpy(ptrSt, "%n");
            readed = sscanf(str, bufSt, arg, &readedFromStr);
            if(readed < 0) {
                return -VSSFError;
            }
            ptrSt = bufSt;
            out += readed;
            str += readedFromStr;
            continue;
        }
        format += 3;
        st = f(str, &readedFromStr, l);
        if(st != Ok) {
            return -st;
        }
        str += readedFromStr;
        ++out;
    }
    return out;
}

int overfscanf(FILE *stream, char *format, ...) {
    char buf[BUFSIZ], *ptr = buf;
    int c;
    while((c = getc(stream)) != EOF) {
        *ptr++ = c;
    }
    *ptr = 0;
    va_list l;
    va_start(l, format);
    return overformat(buf, format, l);
}

int oversscanf(const char *str, char *format, ...) {
    va_list l;
    va_start(l, format);
    return overformat(str, format, l);
}