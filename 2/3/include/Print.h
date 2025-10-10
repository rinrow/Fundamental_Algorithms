#include "Status.h"
#include <stdio.h>
#include <stdlib.h>

// Все ок -> кол-во записанных. Если ошибка вернет n -> -n ошибка в Status
int overfprintf(FILE* stream, const char* format, ...);
int oversprintf(char* buffer, const char* format, ...);
