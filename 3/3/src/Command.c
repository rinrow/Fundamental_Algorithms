#include "../include/Command.h"
#include <string.h>

void initCom(Command* c, CommandData *d, comdFunc f, Node *n) {
    c->f = f;
    c->data = d;
    c->target = n;
}

void editName(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)(livN->data);
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

void editSurname(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)(livN->data);
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

void editPatr(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)(livN->data);
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

void editBirthDay(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    printf("in editBirthDay\n");
    Liver *cur = (Liver *)(livN->data);
    int tmp = cur->birthDay; 
    cur->birthDay = d->intData;
    d->intData = tmp;
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, d, editBirthDay, livN);
    printf("Created command and pushed");
    push_stack(st, (void *)com);
}

void editBirthMonth(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)(livN->data);
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

void editBirthYear(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)(livN->data);
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

void editSex(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)(livN->data);
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

void editAvSal(Node* livN, CommandData *d, LinkedList *livers, LinkedList *st) {
    Liver *cur = (Liver *)(livN->data);
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

void addLiverCommand(Node* livN, CommandData* d, LinkedList *livers, LinkedList *st) {
    printf("In add\n");
    printf("In smth\n");
    printf("l adress = %p\n", d);
    int ind = insertLiver(livers, d->ptrData);
    free(d);
    printf("Insertet at index = %d\n", ind);
    livN = livers->head;
    while(ind--) {
        livN = livN->next;
    }
    printf("livN->data->name = %s\n", ((Liver *)(livN->data))->name);
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, NULL, delLiverCommand, livN);
    // com->f = delLiverCommand;
    // com->target = livN;
    // com->data = NULL;
    push_stack(st, com);
}

void delLiverCommand(Node* livN, CommandData* d, LinkedList *livers, LinkedList *st) {
    printf("In del\n");
    printf("livN = %p\n", livN);
    printf("livN->data->name = %s\n", ((Liver *)(livN->data))->name);
    CommandData *data = (CommandData *)malloc(sizeof(CommandData));
    if(!data) {
        return;
    }
    data->ptrData = livN->data;
    if(!livN->prev) {
        printf("livN->pre\n");
        pop_front_list(livers);
    }
    else if(!livN->next) {
        printf("livN->next\n");
        pop_back_list(livers);
    } else {
        livN->prev->next = livN->next;
        livN->next->prev = livN->prev;
        livers->size--;
        free(livN);
    }
    printf("Creating New commands\n");
    Command *com = (Command *)malloc(sizeof(Command));
    if(!com) {
        return;
    }
    initCom(com, data, addLiverCommand, NULL);
    // com->f = addLiverCommand;
    // com->data = data;
    // com->target = NULL;
    push_stack(st, com);
}

