#include <stdlib.h>
#include <stdio.h>
#include "../include/ArgwParser.h"
#include "../include/Status.h"

int parseNum(char* str, long long *px) {
    int i = 0, mul = 1;
    if(str[0] == '-') {
        mul = -1;
        i = 1;
        if(str[i] == '\0') return InvalidInput;
    } 
    long long res = 0;
    while(str[i] != '\0') {
        if(str[i] < '0' || str[i] > '9') {
            return InvalidInput;
        }
        if(res > (res * 10 + (long long)(str[i] - '0'))) {
            return LongOverflow;
        }
        res = res * 10 + str[i] - '0';
        i++;
    }
    *px = res * mul;
    return Succes;
}

int parseFlag(char* str, char* fl) {
    if(str[0] != '/' && str[0] != '-') {
        return InvalidInput;
    }
    char *av_flags = "hpseaf";
    for(int i = 0; i < 6; i++) {
        if(str[1] == av_flags[i]) {
            if(str[2] != '\0') {
                return InvalidInput;
            }
            *fl = str[1];
            return Succes;
        }
    }
    return InvalidInput;
}
