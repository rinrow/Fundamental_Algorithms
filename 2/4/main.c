#include <stdio.h>
#include "include/Scan.h"

int main() {
    int res, a, b, c, d, e, f;
    double da, db;
    char s[10], ss[10], sss[10];
    res = oversscanf("\t\t11XX ffff ||1001", " 1%d%Ro %s ||%Zr", &a, &b, s, &c);
    printf("%d %d %d %s %d\n", res, a, b, s, c);       

    res = oversscanf("akdl akdl akdl 11", "%s %s %s %CV", s, ss, sss, a, 12);
    printf("%s %s %s %d\n", s, ss, sss, a); 

    res = oversscanf("II XI IX X MX L jskdhvfkjsdhk", "%Ro %Ro %Ro %Ro %Ro %Ro", &a, &b, &c, &d, &e, &f);
    printf("%d %d %d %d %d %d %d\n", res, a, b, c, d, e, f);       
    return 0;
}