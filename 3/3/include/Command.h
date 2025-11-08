#pragma once
#include "LinkedList.h"
#include "Liver.h"

typedef union {
    int intData;
    char strData[50];
    float floatData;
    void *ptrData;
} CommandData;

typedef void (*comdFunc)(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);

typedef struct {
    comdFunc f;
    CommandData *data;
    Node *target;
} Command;

void editName(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editSurname(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editPatr(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editBirthDay(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editBirthMonth(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editBirthYear(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editSex(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void editAvSal(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st);
void addLiverCommand(Node* livN, CommandData* d, LinkedList *livers, LinkedList *st);
void delLiverCommand(Node* livN, CommandData* d, LinkedList *livers, LinkedList *st);
