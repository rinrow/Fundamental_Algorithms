#include "Status.h"
#include <stdarg.h>

Status Ro(const char* buf, int *rd, va_list l);
Status Zr(const char* buf, int *rd, va_list l);
Status Cv(const char* buf, int *rd, va_list l);
Status CV(const char* buf, int *rd, va_list l);