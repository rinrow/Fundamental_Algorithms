#include "Status.h"
#include <stdarg.h>

Status Ro(char* buf, int *wr, va_list l);
Status Zr(char* buf, int *wr, va_list l);
Status Cv(char* buf, int *wr, va_list l);
Status CV(char* buf, int *wr, va_list l);
Status to(char* buf, int *wr, va_list l);
Status TO(char* buf, int *wr, va_list l);
Status mi(char* buf, int *wr, va_list l);
Status mu(char* buf, int *wr, va_list l);
Status md(char* buf, int *wr, va_list l);
Status mf(char* buf, int *wr, va_list l);