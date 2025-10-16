#include "../include/Sol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

Student** readStuds(FILE* in, Status *stat, int *len) {
    int cap = 2, sz = 0, readed;   
    Student **st = (Student **) malloc(sizeof(Student *) * cap), **tmp;
    if(!st) {
        *len = 0;
        *stat = ErrorOnMalloc;
        return st;
    }
    Student *nst;
    *stat = Ok;
    while (!feof(in)) {
        if(sz == cap) {
            tmp = realloc(st, (cap *= 2) * sizeof(Student *));
            if(!tmp) {
                *stat = ErrorOnRealloc;
                break;
            }
            st = tmp;
        }
        nst = (Student *) malloc(sizeof(Student));
        st[sz] = nst;        
        if(!nst) {
            *stat = ErrorOnMalloc;
            break;
        }
        ++sz;
        nst->scores = (unsigned char *) malloc(sizeof(unsigned char) * 5);
        if(!nst->scores) {
            *stat = ErrorOnMalloc;
            break;
        }
        readed = fscanf(in, " %u %s %s %s %hhd %hhd %hhd %hhd %hhd", 
            &nst->id, nst->name, nst->lastName, nst->group,
            nst->scores, nst->scores + 1, nst->scores + 2, nst->scores + 3, nst->scores + 4);
        if(readed != 9) {
            *stat = ErrorOnReading;
            break;
        }
    }
    *len = sz;
    return st;
}

void printStud(FILE* stream, Student *nst) {
    float avScore = 0;
    for(int i = 0; i < 5; ++i) {
        avScore += nst->scores[i];
    }
    avScore /= 5;
    fprintf(stream, "============================\n");
    fprintf(stream, "%u %s %s %s\n\tСредняя оценка: %f\n", 
            nst->id, nst->name, nst->lastName, nst->group,
            avScore);
    fprintf(stream, "============================\n");
}

typedef void(* searchFunc)(Student **st, int len, FILE* out);

void SearchId(Student **st, int len, FILE* out) {
    printf("Хотите результат записать в файл?\n");
    printf("Введите 1 если да. Если нет любое другое число\n");
    int c;
    scanf("%d", &c);
    bool write = c == 1, found = false;
    int id;
    printf("Введите id по которому будет происходить поиск\n");
    scanf("%d", &id);
    for(int i = 0; i < len; ++i) {
        if(st[i]->id == id) {
            printf("Студент найден!\n");
            printStud(stdout, st[i]);
            if(write) {
                printStud(out, st[i]);
            }
            found = true;
        }
    }
    if(!found) {
        printf("Такой студент не найден ( ఠ ͟ʖ ఠ)\n");
    }
}

void SearchName(Student **st, int len, FILE* out) {
    bool found = false;
    char name[bufl];
    printf("Введите имя по которому будет происходить поиск\n");
    scanf("%s", name);
    for(int i = 0; i < len; ++i) {
        if(!strcmp(st[i]->name, name)) {
            printf("Студент найден!\n");
            printStud(stdout, st[i]);
            found = true;
        }
    }
    if(!found) {
        printf("Такой студент не найден ( ఠ ͟ʖ ఠ)\n");
    }
}

void SearchLasName(Student **st, int len, FILE* out) {
    bool found = false;
    char name[bufl];
    printf("Введите фамилию по которой будет происходить поиск\n");
    scanf("%s", name);
    for(int i = 0; i < len; ++i) {
        if(!strcmp(st[i]->lastName, name)) {
            printf("Студент найден!\n");
            printStud(stdout, st[i]);
            found = true;
        }
    }
    if(!found) {
        printf("Такой студент не найден ( ఠ ͟ʖ ఠ)\n");
    }
}

void SearchGroup(Student **st, int len, FILE* out) {
    bool found = false;
    char group[bufl];
    printf("Введите группу по которой будет происходить поиск\n");
    scanf("%s", group);
    for(int i = 0; i < len; ++i) {
        if(!strcmp(st[i]->group, group)) {
            printf("Студент найден!\n");
            printStud(stdout, st[i]);
            found = true;
        }
    }
    if(!found) {
        printf("Такой студент не найден ( ఠ ͟ʖ ఠ)\n");
    }
}

Status Search(Student **st, int len, FILE* out) {
    printf("Для параметра поиска по id введите 0:\n");
    printf("Для параметра поиска по имени введите 1:\n");
    printf("Для параметра поиска по фамилии введите 2:\n");
    printf("Для параметра поиска по группе введите 3:\n");
    int i;
    scanf("%d", &i);
    while(i < 0 || i > 3) {
        printf("Введите корректное число\n");
        scanf("%d", &i);
    }
    searchFunc f[] = {SearchId, SearchName, SearchLasName, SearchGroup};
    f[i](st, len, out);
    return Ok; 
}

typedef int (*cmpFunc)(const void *a, const void *b);

int cmpId(const void *a, const void *b) {
    int id1 = ( *(Student **)a )->id; 
    int id2 = ( *(Student **)b )->id; 
    return id1 - id2;
}

int cmpName(const void *a, const void *b) {
    char *n1 = ( *(Student **)a )->name; 
    char *n2 = ( *(Student **)b )->name; 
    return strcmp(n1, n2);
}

int cmpLastName(const void *a, const void *b) {
    char *n1 = ( *(Student **)a )->lastName; 
    char *n2 = ( *(Student **)b )->lastName; 
    return strcmp(n1, n2);
}

int cmpGroup(const void *a, const void *b) {
    char *n1 = ( *(Student **)a )->group; 
    char *n2 = ( *(Student **)b )->group; 
    return strcmp(n1, n2);
}

cmpFunc getCmp() {
    printf("Для выбора компаратора по id введите 0:\n");
    printf("Для выбора компаратора по имени введите 1:\n");
    printf("Для выбора компаратора по фамилии введите 2:\n");
    printf("Для выбора компаратора по группе введите 3:\n");
    int i;
    scanf("%d", &i);
    while(i < 0 || i > 3) {
        printf("Введите корректное число\n");
        scanf("%d", &i);
    }
    cmpFunc f[] = {cmpId, cmpName, cmpLastName, cmpGroup};
    return f[i]; 
}

Status Sort(Student **st, int len) {
    qsort(st, len, sizeof(Student *), getCmp());
    printf("Отсортировано!\n");
}

Status moreThanAverage(Student **st, int len, FILE* out, double allAvScore) {
    double av;
    for(int i = 0, j; i < len; ++i) {
        av = 0;
        for(j = 0; j < 5; ++j) {
            av += st[i]->scores[j];
        }
        av /= 5;
        if(av > allAvScore) {
            printStud(stdout, st[i]);
            printStud(out, st[i]);
        }
    }
    
    return Ok;
}

void printInform() {
    printf("Для поиска введите - 1\n");
    printf("Для сортировки введите - 2\n");
    printf("Для печати в файл всех студентов чей средний балл выше чем общий средний балл введите - 3\n");
    printf("Для выхода введите - 4\n");
}

Status interact(Student **st, int len, FILE* out) {
    int i, j;
    double allAvScore = 0;
    for(i = 0; i < len; ++i) {
        for(j = 0; j < 5; ++j) {
            allAvScore += st[i]->scores[j];
        }
    }
    allAvScore /= len * 5;
    i = 5;
    while(i != 4) {
        switch (i) {
        case 1:
            Search(st, len, out);
            break;
        case 2:
            Sort(st, len);
            break;
        case 3:
            moreThanAverage(st, len, out, allAvScore);
            break;
        default:
            break;
        }   
        printInform();
        scanf("%d", &i);
        while(i < 1 || i > 4) {
            printf("Введите корректное число!\n");
            scanf("%d", &i);
        } 
    }   
}

void freeStud(Student **st, int len) {
    for(int i = 0; i < len; ++i) {
        free(st[i]->scores);
        free(st[i]);
    }
    free(st);
}