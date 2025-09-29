#include <stdio.h>
#include <ctype.h>
#include "../include/Status.h"

Status dOp(FILE* fin, FILE* fout) {
    int ch;
    while((ch = fgetc(fin)) != EOF) {
        if(isdigit(ch)) {
            continue;
        }
        if(fputc(ch, fout) == EOF) {
            return ErrorWhenWrite;
        }
    }
    return Ok;
}

Status iOp(FILE* fin, FILE* fout) {
    char buf[BUFSIZ];
    int cnt;
    while(fgets(buf, BUFSIZ, fin) != NULL) {
        cnt = 0;
        printf("%s", buf);
        for(int i = 0; buf[i]; ++i) {
            if(isalpha(buf[i])) {
                ++cnt;
            }
        }
        if(fprintf(fout, "%d\n", cnt) < 0) {
            return ErrorWhenWrite;
        }
    }
    return Ok;
}

Status sOp(FILE* fin, FILE* fout) {
    char buf[BUFSIZ];
    int cnt;
    while(fgets(buf, BUFSIZ, fin) != NULL) {
        cnt = 0;
        for(int i = 0; buf[i]; ++i) {
            if(!isalnum(buf[i]) && buf[i] != ' ') {
                ++cnt;
            }
        }
        if(fprintf(fout, "%d\n", cnt) < 0) {
            return ErrorWhenWrite;
        }
    }
    return Ok;
}

Status aOp(FILE* fin, FILE* fout) {
    int ch; // char не может хранить EOF
    char* spec;
    while((ch = fgetc(fin)) != EOF) {
        spec = isdigit(ch) ? "%c": "%X"; 
        if(fprintf(fout, spec, ch) < 0) {
            return ErrorWhenWrite;
        }
        if((ch == '\n' || ch == ' ') && fprintf(fout, "%c", ch) < 0) { // сохраняем перенос строки и пробел чтобы читалось лучше
            return ErrorWhenWrite;
        }
    }
    return Ok;
}