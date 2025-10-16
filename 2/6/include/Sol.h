#include "Status.h"
#include "Student.h"
#include <stdio.h>

Student** readStuds(FILE* in, Status *st, int *len);
void freeStud(Student **st, int len);
Status interact(Student **st, int len, FILE* out);