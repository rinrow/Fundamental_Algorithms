#include <stdlib.h>
#include <stdio.h>
#include "../include/Parser.h"

Status parseFlag(char* str, char *fl, bool* hasN) {
    if(str[0] != '-' && str[0] != '/' || str[1] == '\0') {
        return InvalidInput;
    }
    char flag = str[1 + (str[1] == 'n')];
    *hasN = str[1] == 'n'; 
    char *avFlags = "disa";
    for(int i = 0; i < 4; ++i) {
        if(flag == avFlags[i]) {
            *fl = flag;
            return Ok;
        }
    }
    return UncorrectFlag;
}
