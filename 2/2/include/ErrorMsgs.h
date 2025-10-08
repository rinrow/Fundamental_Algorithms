#ifndef ERROR_MSGS_H
#define ERROR_MSGS_H

#include <errno.h>

#if defined(__APPLE__)
    #define MAX_ERRNO 107
#elif defined(__linux__)
    #define MAX_ERRNO 133
#else
    #error "Unsupported operating system"
#endif

// Объявляем массив как extern - он будет определен в .c файле
extern const char* const errors[];

#endif