#ifndef STUDENT_H
#define STUDENT_H

#define bufl 100

typedef struct {
    unsigned id;
    char name[bufl], lastName[bufl], group[bufl];
    unsigned char *scores;
} Student;

#endif