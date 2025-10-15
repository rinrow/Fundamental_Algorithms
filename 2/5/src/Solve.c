#include "../include/Solve.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void moveRight(char *str, int st, int fn, int cnt) {
    for(; fn >= st; --fn) {
        str[fn + cnt] = str[fn];
    }
}

void calcWords(char *ptr, int* wCnt, int *dl, int* lastWordEnd) {
    for(int i = 1; i < 81; ++i) {
        if(isspace(ptr[i]) && !isspace(ptr[i - 1])) {
            // (i - 1) - end of the word
            ++(*wCnt), *dl = 80 - i;
            *lastWordEnd = i - 1;
        }
    }  
}

void doStrCor(char *ptrTmp, int wCnt, int dl, int lastWordEnd) {
    int cntMove = dl / (wCnt - 1), rem = dl % (wCnt - 1);
    int i, j;
    for(i = 1; i < 80; ++i) {
        if(isspace(ptrTmp[i]) && !isspace(ptrTmp[i - 1])) {
            // (i - 1) - end of the word
            // сдвинуть [i: lastWordEnd] на cntMove + !!rem
            moveRight(ptrTmp, i, lastWordEnd, cntMove + !!rem);
            // [i: i + cntMove + !!rem] - зап проб
            for(j = i; j < i + cntMove + !!rem; ++j) {
                ptrTmp[j] = ' ';
            }
            lastWordEnd += cntMove + !!rem;
            if(rem) {
                --rem;
            }
        }
    }  
}

Status operate(FILE *in, FILE *out) {
    char buf[BUFSIZ], *ptr = buf, tmpBuf[BUFSIZ];
    int i, wCnt, dl, lastWordEnd, cntMove, rem, j;
    while(fgets(buf, BUFSIZ, in)) {
        ptr = buf;
        ptr += strspn(ptr, " \t\n");
        while(strlen(ptr) > 80) {
            wCnt = 0, dl = -1;
            calcWords(ptr, &wCnt, &dl, &lastWordEnd);
            if(!wCnt || wCnt == 1 && lastWordEnd != 79) {
                // одно длинное слово
                return BadWord;
            }
            memcpy(tmpBuf, ptr, lastWordEnd + 1);
            if(wCnt > 1) {
                doStrCor(tmpBuf, wCnt, dl, lastWordEnd);
            }
            ptr += lastWordEnd + 1;
            ptr += strspn(ptr, " \t\n");
            for(i = 0; i < 80; ++i) {
                fputc(tmpBuf[i], out);
            }
            fputc('\n', out);
        }
        if(*ptr) {
            fputs(ptr, out);
        }
        if(!buf[strspn(buf, " \t\n")]) {
            fputc('\n', out);
        }
    }
    return Ok;
}