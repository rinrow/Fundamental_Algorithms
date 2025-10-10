#include "../include/Print.h"
#include "../include/Specs.h"
#include "../include/Funcs.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef Status (*func)(char* buf, int *wr, va_list l);

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
    char *names[] = {"Ro", "Zr", "Cv", "CV", "to", "TO", "mi", "mu", "md", "mf"};
    func funcs[] = {Ro, Zr, Cv, CV, to, TO, mi, mu, md, mf};
    for(int i = 0; i < 10; ++i) {
        if(!strcmp(names[i], cur)) {
            *sp = NotStandart;
            *f = funcs[i];
            return;
        }
    }
}

int overformat(char* buffer, const char* format, va_list l) {
    char bufSt[BUFSIZ], *ptrSt = bufSt;
    int written, out = 0;
    Spec sp;
    Status st;
    func f;
    while(*format) {
        if(*format != '%') {
            *buffer++ = *format++;
            continue;
        }
        parseSpec(format, &sp, &f);
        if(sp == Standart) {
            // вызываем vsprintf
            // двиг ptr до след %
            // vsprintf нужно кинуть новую строку вида %... . Посл s[i] -> s[i + 1] == '%'
            if(format[1] == '%') { // 2 процента -> %
                *ptrSt++ = *format++;
            }
            do {
                *ptrSt++ = *format++;
            } while(*format && *format != '%');
            *ptrSt = 0;
            written = vsprintf(buffer, bufSt, l);
            if(written < 0) {
                return -VSPFError;
            }
            ptrSt = bufSt;
            buffer += written;
            out += written;
            continue;
        }
        // Спец кот в ТЗ всегда занимают 3 литера, ptr += 3 
        st = f(buffer, &written, l);
        if(st != Ok) {
            return -st;
        }
        format += 3;
        buffer += written;
        out += written;
    }
    *buffer = 0;
    return out;
}

int oversprintf(char* buffer, const char* format, ...) {
    va_list l;
    va_start(l, format);
    int ret = overformat(buffer, format, l); 
    va_end(l);
    return ret;
}

int overfprintf(FILE* stream, const char* format, ...) {
    char buf[BUFSIZ];
    va_list l;
    va_start(l, format);
    int ret = overformat(buf, format, l);
    va_end(l);
    fprintf(stream, "%s", buf);
    return ret;
}
