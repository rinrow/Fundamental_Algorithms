#include "../include/Funcs.h"
#include "../include/ErrorMsgs.h"
#include <stdint.h>
#include <stdio.h>

// Обработать случаи с NULL, my_strerror

#define min(a, b) ((a) < (b) ? (a): (b))

// в оригинальном memchr если переданное с не влезает в байт идет обрезание по младшему байту
// тут аналогично
void *my_memchr(const void *str, int c, size_t n) { // ?
    if(str == NULL) {
        return NULL;
    }
    uint8_t *ptr = str;
    uint8_t tar = c;
    for(; n; --n, ++ptr) {
        if(*ptr == tar) {
            return (void *)ptr;
        }
    }
    return NULL;
}

// 0 - equal, > 0 - str1 greater than str2, < 0 - str2 greater than str1
int my_memcmp(const void *str1, const void *str2, size_t n) {
    if(str1 == NULL && str2 == NULL) { 
        return 0;
    }
    if(str1 == NULL) {
        return -1;
    }
    if(str2 == NULL) {
        return 1;
    }
    uint8_t *l = str1, *r = str2;
    for(; n && *l == *r; --n, ++l, ++r);
    return n ? *l - *r: 0;
}

// Скорее всего под 'символов' имелось ввиду байты 
// так как в противном случае ф.я не отличается от strcpy
void *my_memcpy(void *dest, const void *src, size_t n) {
    if(dest == NULL || src == NULL) {
        return NULL;
    }
    uint8_t *d = dest, *s = src;
    while(n--) {
        *d++ = *s++;
    }
    return dest;
}   

void *my_memset(void *str, int c, size_t n) {
    if(str == NULL) {
        return NULL;
    }
    uint8_t *ptr = str, tar = c;
    while(n--) {
        *ptr++ = tar;
    }
    return str;
}

// Оригинальный strncat не аллоцирует память
// src == NULL -> пустая строка dest + пустая строка = dest
char *my_strncat(char *dest, const char *src, size_t n) {
    if(dest == NULL || src == NULL) {
        return dest;
    }
    n = min(n, my_strlen(src));
    char *ptr = dest + my_strlen(dest);
    while(n--) {
        *ptr++ = *src++;
    }
    *ptr = 0;
    return dest;  
}

char *my_strchr(const char *str, int c) {
    if(str == NULL) {
        return NULL;
    }
    char tar = c, *ptr = str;
    for(; *ptr && *ptr != tar; ++ptr);
    return *ptr == tar ? ptr: NULL;
}

// 0 - equal, > 0 - str1 greater than str2, < 0 - str2 greater than str1
// str1 == NULL -> empty string
int my_strncmp(const char *str1, const char *str2, size_t n) { // ?
    if(str1 == NULL && str2 == NULL) { 
        return 0;
    }
    if(str1 == NULL) {
        return -1;
    }
    if(str2 == NULL) {
        return 1;
    }
    n = min(n, min(my_strlen(str1), my_strlen(str2)) );
    for(; n && *str1 == *str2; --n, ++str1, ++str2);
    if(!n) return 0;
    return *str1 - *str2;
}

char *my_strncpy(char *dest, const char *src, size_t n) {
    if(dest == NULL || src == NULL) { // Оба ни на что не указывают поэтому равны
        return NULL;
    }
    char *ptr = dest;
    n = min(n, my_strlen(src));
    while(n--) {
        *ptr++ = *src++;
    }   
    *ptr = 0;
    return dest;
}

size_t my_strcspn(const char *str1, const char *str2) {
    if(str1 == NULL || str2 == NULL) { 
        return 0;
    }
    int has[256] = {1};
    size_t sz = 0;
    for(; *str2; ++str2) {
        has[*str2] = 1;
    }
    for(; !has[*str1]; ++str1, ++sz);
    return sz;
}

// в оригинале возвращается не копия а указатель 
// (если программист захочет изменить строку ошибки - это его проблема XD )
char *my_strerror(int errnum) {
    if (errnum < 0 || errnum > MAX_ERRNO) {
        return "Unknown error";
    }
    return errors[errnum];
}

size_t my_strlen(const char *str) {
    if(str == NULL) {
        return 0;
    }
    size_t sz = 0;
    for(; *str; ++sz, ++str);
    return sz;
}

char *my_strpbrk(const char *str1, const char *str2) {
    if(str1 == NULL || str2 == NULL) {
        return NULL;
    }
    str1 += my_strcspn(str1, str2);
    return *str1 ? str1: NULL;
}

char *my_strrchr(const char *str, int c) {
    if(str == NULL) {
        return NULL;
    }
    char *ptr = NULL, tar = c;
    for(; *str; ++str) {
        if(*str == tar) {
            ptr = str;
        }
    }
    return ptr;
}

char *my_strstr(const char *haystack, const char *needle) {
    if(needle == NULL || haystack == NULL) {
        return haystack;
    }
    int n = my_strlen(needle), i;
    if(n > my_strlen(haystack)) {
        return NULL;
    }
    for(; *(haystack + n - 1); ++haystack) {
        for(i = 0; i < n; ++i) {
            if(needle[i] != haystack[i]) {
                break;
            }
        }
        if(i == n) {
            return haystack;
        }
    }
    return NULL;
}

size_t my_strspn(const char *str1, const char *str2) {
    if(str1 == NULL || str2 == NULL) { 
        return 0;
    }
    int has[256] = {1};
    size_t sz = 0;
    for(; *str2; ++str2) {
        has[*str2] = 1;
    }
    for(; has[*str1]; ++str1, ++sz);
    return sz;
}

// оригинальный my_strtok изменят str, и тут тоже
char *my_strtok(char *str, const char *delim) { 
    static char *buf;
    if(str != NULL) {
        buf = str;
    }
    if(buf == NULL || delim == NULL || !*buf) {
        return NULL;
    }
    buf += my_strspn(buf, delim);
    str = buf;
    buf += my_strcspn(buf, delim);
    if(*buf) {
        *buf++ = 0;
    }
    return str;
}