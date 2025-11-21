#include "../include/Command.h"
#include <string.h>
#include <stdio.h>

void initCom(Command* c, CommandData *d, comdFunc f, int tar) {
    c->f = f;
    c->data = d;
    c->target = tar;
}

void editName(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    char buf[50];
    strcpy(buf, cur->name);
    strcpy(cur->name, d->strData);
    strcpy(d->strData, buf);
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editName, livN);
    push_stack(st, (void *)com);
}

void editSurname(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    char buf[50];
    strcpy(buf, cur->surname);
    strcpy(cur->surname, d->strData);
    strcpy(d->strData, buf);
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editSurname, livN);
    push_stack(st, (void *)com);
}

void editPatr(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    char buf[50];
    strcpy(buf, cur->patronymic);
    strcpy(cur->patronymic, d->strData);
    strcpy(d->strData, buf);
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editPatr, livN);
    push_stack(st, (void *)com);
}

void editBirthDay(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    int tmp = cur->birthDay; 
    cur->birthDay = d->intData;
    d->intData = tmp;
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editBirthDay, livN);
    push_stack(st, (void *)com);
}

void editBirthMonth(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    int tmp = cur->birthMonth; 
    cur->birthMonth = d->intData;
    d->intData = tmp;
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editBirthMonth, livN);
    push_stack(st, (void *)com);
}

void editBirthYear(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    int tmp = cur->birthYear; 
    cur->birthYear = d->intData;
    d->intData = tmp;
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editBirthYear, livN);
    push_stack(st, (void *)com);
}

void editSex(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    char tmp = cur->sex; 
    cur->sex = d->strData[0];
    d->strData[0] = tmp;
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editSex, livN);
    push_stack(st, (void *)com);
}

void editAvSal(int livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)get_at_list(livers, livN);
    float tmp = cur->avSal;
    cur->avSal = d->floatData;
    d->floatData = tmp;
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editAvSal, livN);
    push_stack(st, (void *)com);
}
#include <stdio.h>

void addLiverCommand(int livN, CommandData* d, LinkedList *livers, LinkedList *st) {
    livN = insertLiver(livers, d->ptrData);
    free(d);
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, NULL, delLiverCommand, livN);
    push_stack(st, com);
}

void delLiverCommand(int livN, CommandData* d, LinkedList *livers, LinkedList *st) {
    CommandData *data = (CommandData *)malloc(sizeof(CommandData));
    if(!data) {
        return;
    }
    data->ptrData = get_at_list(livers, livN);
    delete_at_list(livers, livN);
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, data, addLiverCommand, -1);
    push_stack(st, com);
}

