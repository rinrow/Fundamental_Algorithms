#include "../include/solve.h"
#include "../include/vector.h"
#include <stdio.h>

DEFINE_VEC(char)

void delChar(char c) {}
char copyChar(char c) {
    return c;
}

int check_brackets(const char *ptr) {
    if(!ptr) {
        return true;
    }
    bool isOpen[256] = {false}, isClose[256] = {false};
    char brackets[] = "(){}[]<>", brPair[256]; // brPair[')'] = '(';
    for(int i = 0; i < 8; i += 2) {
        isOpen[brackets[i]] = true;
        isClose[brackets[i + 1]] = true;
        brPair[brackets[i + 1]] = brackets[i];
    }
    vector st = create_vector(2, copyChar, delChar);
    bool res = true;
    while(*ptr) {
        if(isOpen[*ptr]) {
            push_back_vector(&st, *ptr);
        } else if(isClose[*ptr]) {
            if(!st.sz || pop_back_vector(&st) != brPair[*ptr]) {
                res = false;
                break;
            }
        }
        // Если не скобка то просто скип
        ++ptr;
    }
    res = res && !st.sz;
    delete_vector(&st);
    return res;
}