#pragma once
#include "LinkedList.h"
#include "Liver.h"

typedef union {
    int intData;
    char strData[50];
    float floatData;
    void *ptrData;
} CommandData;

typedef void (*comdFunc)(int livN, CommandData *d, LinkedList *livers, LinkedList *st);

typedef struct {
    comdFunc f;
    CommandData *data;
    int target;
} Command;

void editName(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editSurname(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editPatr(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editBirthDay(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editBirthMonth(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editBirthYear(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editSex(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editAvSal(int livN, CommandData *d, LinkedList *livers, LinkedList *st);
void addLiverCommand(int livN, CommandData* d, LinkedList *livers, LinkedList *st);
void delLiverCommand(int livN, CommandData* d, LinkedList *livers, LinkedList *st);
