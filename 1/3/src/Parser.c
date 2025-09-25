#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "../include/Parser.h"

Status parseFlag(char* str, char *fl) {
    if(str[0] != '-' || str[1] == '\0' || str[2] != '\0') {
        return InvalidInput;
    }
    *fl = str[1];
    return Ok;
}

Status parseVals(char** strs, int cnt, long double *out) {
    char *end = NULL;
    for (int i = 0; i < cnt; ++i) {
        errno = 0;
        out[i] = strtold(strs[i], &end);
        if(errno == ERANGE || *end != '\0' || end == strs[i]) {
            return InvalidInput;
        }
    }
    return Ok;
}