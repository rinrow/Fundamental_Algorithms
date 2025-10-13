#include <stdio.h>
#include "include/Scan.h"

int main() {
    int res, a, b, c, d, e, f;
    double da, db;
    char s[10], ss[10], sss[10];
    res = oversscanf("\t\t11XX ffff ||1001", " 1%d%Ro %s ||%Zr", &a, &b, s, &c);
    printf("%d %d %d %s %d\n", res, a, b, s, c);       

    res = oversscanf("akdl akdl akdl", "%s %s %s", s, ss, sss);
    printf("%s %s %s\n", s, ss, sss); 

    res = oversscanf("II XI IIIX VV MX XXXXX", "%Ro %Ro %Ro %Ro %Ro %Ro", &a, &b, &c, &d, &e, &f);
    printf("%d %d %d %d %d %d %d\n", res, a, b, c, d, e, f);       
    return 0;
}