#include <stdlib.h>
#include <stdbool.h>
#include "../include/NthPrime.h"
#include "../include/Status.h"

bool prime(long long num) {
    for(int i = 2; i * i <= num; ++i) {
        if(num % i == 0) {
            return false;
        }
    }
    return true;
}

int getPrime(long long pos, long long* ans) {
    long long primeCnt = 1;
    long long curNum = 2;
    while(primeCnt != pos) {
        if(curNum + 1 < curNum) {
            return LongOverflow;
        }
        curNum++;
        primeCnt += prime(curNum);
    }
    *ans = curNum;
    return Ok;
}