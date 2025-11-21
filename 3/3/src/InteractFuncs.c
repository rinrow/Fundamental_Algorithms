#include "../include/InteractFuncs.h"
#include "../include/Liver.h"
#include "../include/Command.h"
#include <ctype.h>
#include <string.h>
#include <math.h>

void clearInBuffer() {
    int c; 
    while((c = getchar()) != '\n' && c != EOF);
}

void printLiv(FILE* stream, Liver* l) {
    fprintf(stream, "%d %s %s %s %d %d %d %c %f\n", l->id, 
            l->name, l->surname, l->patronymic, l->birthDay, l->birthMonth, 
            l->birthYear, l->sex, l->avSal);
}

void deleteLiver(LinkedList* livers, LinkedList* st) {
    printf("Сначало нужно найти жителя\n");
    printSearchInfo();
    Liver *tar = readLiver(stdin);
    int res = findLiverInd(livers, tar);
    free(tar);
    if(res == -1) {
        printf("Не найден подходящий житель\n");
        return;
    }
    delLiverCommand(res, NULL, livers, st);
    printf("Успешно удалено!\n");
}

void addLiver(LinkedList* livers, LinkedList* st) {
    printf("Введите данные о новом жителе\n");
    printLiverStructInfo();
    Liver* tmp = readLiver(stdin);
    if(!tmp) {
        printf("Не удалось считать жителя\n");
        return;
    }
    CommandData *data = (CommandData *)malloc(sizeof(CommandData));
    if(!data) {
        printf("Не удалось создать команду\n");
        free(tmp);
        return;
    }
    data->ptrData = tmp;
    addLiverCommand(-1, data, livers, st);
    printf("Житель добавлен!\n");
}

void changeLiver(LinkedList* livers, LinkedList* st) {
    comdFunc funcs[] = {editName, editSurname, editPatr, editBirthDay, 
            editBirthMonth, editBirthYear, editSex, editAvSal};
    char *spec[] = {"%s", "%s", "%s", "%d", "%d", "%d", "%s", "%f"}; 
    printf("Сначало нужно найти жителя\n");
    printSearchInfo();
    Liver *tar = readLiver(stdin);
    int res = findLiverInd(livers, tar);
    free(tar);
    if(res == -1) {
        printf("Не найден подходящий житель\n");
        return;
    }
    printf("Теперь можно редактировать!\n");
    int ind;
    CommandData *data = (CommandData *)malloc(sizeof(CommandData));
    if(!data) {
        printf("Не удалось выполнить операцию\n");
        return;
    }
    data->ptrData = NULL;
    printChangeInfo();
    int readed = scanf("%d", &ind);
    if(ind < 0 || ind > 7 || readed != 1) {
        printf("Некорректная операция\n");
        free(data);
        clearInBuffer();
        return;
    }
    printf("Введите значение для этого поля:\n");
    // в зависимости от ind считыавем либо число либо строка    
    scanf(spec[ind], data);
    funcs[ind](res, data, livers, st);
    printf("Операция выполнена!\n");
}

void printLiverStructInfo() {
    printf("\
ID \n\
Имя \n\
Фамилия \n\
Отчество (если без отчества нажмите пробел)\n\
День рождения \n\
Месяц \n\
Год \n\
Пол\n\
Средняя зп \n\
");
}

void printSearchInfo() {
    printf("Поиск осуществляется по нескольким параметрам. Введите параметры поиска поряку!\n");
    printLiverStructInfo();
    printf("Если нужно скипнуть какой-то параметр, для имени, фамилии, отчества, пола введите вместо него ~. А для других полей введите -1\n");
}

void printChangeInfo() {
    printf("\
Для изменения имени введите 0\n\
Для изменения фамилии введите 1\n\
Для изменения отчества введите 2\n\
Для изменения дня рождения введите 3\n\
Для изменения месяца рождения введите 4\n\
Для изменения года рождения введите 5\n\
Для изменения пола введите 6\n\
Для изменения среденй зарплаты введите 7\n\
\n");
}

int isEqLivers(Liver* a, Liver* b) {
    int equal = 1;
    if(a->id != -1) {
        equal = equal && a->id == b->id;
    }
    if(strcmp(a->name, "~")) {
        equal = equal && !strcmp(a->name, b->name);
    }
    if(strcmp(a->surname, "~")) {
        equal = equal && !strcmp(a->surname, b->surname);
    }
    if(strcmp(a->patronymic, "~")) {
        equal = equal && !strcmp(a->patronymic, b->patronymic);
    }
    if(a->birthDay != -1) {
        equal = equal && a->birthDay == b->birthDay;
    }
    if(a->birthMonth != -1) {
        equal = equal && a->birthMonth == b->birthMonth;
    }
    if(a->birthYear != -1) {
        equal = equal && a->birthYear == b->birthYear;
    }
    if(a->sex != '~') {
        equal = equal && a->sex == b->sex;
    }
    if(fabs(a->avSal + 1) > 1e-7) {
        equal = equal && fabs(a->avSal - b->avSal) <= 1e-7;
    }
    return equal;
}

int findLiverInd(LinkedList *livers, Liver* tar) {
    if(!tar) {
        return -1;
    }
    Node* cur = livers->head;
    int res = 0;
    // Node* res = NULL;
    while(cur) {
        if(isEqLivers(tar, cur->data)) {
            break;
        }
        cur = cur->next;
        res++;
    }
    if(res >= livers->size) { 
        res = -1;
    }
    return res;
}

void searchLiver(LinkedList* livers, LinkedList* st) {
    printSearchInfo();
    Liver *tar = readLiver(stdin);
    printLiv(stdout, tar);
    int res = findLiverInd(livers, tar);
    if(res == -1) {
        printf("Не найден житель соответствующий параметрам!\n");
    } else {
        printf("Найден житель соответствующий параметрам!\n");
        printLiv(stdout, (Liver *)get_at_list(livers, res));
    }
}

void undo(LinkedList* livers, LinkedList* st) {
    if(!st->size) { 
        return;
    }
    Command *com = (Command *)pop_stack(st);
    com->f(com->target, com->data, livers, st);
    Command* newCom = (Command *)pop_stack(st); // вновь вызванная команда положит себя в стек
    if(!com->data) {
        // если delete очищать не надо
        free(newCom->data->ptrData);
    } 
    if(com->target != -1) {
        // если add очищать не надо
        free(com->data);
    } 
    if(!com->data || com->target == -1) {
        // если change очищать не надо
        free(newCom->data);
    }
    free(com);
    free(newCom);
}

void undoHalfN(LinkedList* livers, LinkedList* st) {
    int n = st->size;
    for(int i = 0; i < n / 2; i++) {
        undo(livers, st);
    }
    freeStack(st);
}

void printLivers(LinkedList* livers, LinkedList* st) {
    Node* cur = livers->head;
    int num = 0;
    FILE* f = stdout;
    printf("Для печати в файл введите 1, иначе любую другую цифру\n");
    scanf("%d", &num);
    char buf[200];
    if(num == 1) {
        printf("Введите путь к файлу\n");
        scanf("%s", buf);
        f = fopen(buf, "a");
        if(!f) {
            printf("Не удалось открыть файл\n");
            return;
        }
        fprintf(f, "=======================\n");
    }
    while(cur) {
        printLiv(f, (Liver *)(cur->data));
        cur = cur->next;
    }
    if(f != stdout) {
        fclose(f);
    }
}

Liver* readLiver(FILE* stream) {
    Liver *l = (Liver *)malloc(sizeof(Liver));
    if(!l) {
        return NULL;
    }
    if(4 != fscanf(stream, " %d %s %s %s", &(l->id), l->name, l->surname, l->patronymic)) {
        free(l);
        return NULL;
    }
    if(isdigit(l->patronymic[0]) || l->patronymic[0] == '-') {
        // отчества нету
        l->birthDay = atoi(l->patronymic);
        l->patronymic[0] = '\0';
    } else {
        fscanf(stream, "%d", &(l->birthDay));
    }
    fscanf(stream, " %d %d %c %f", &(l->birthMonth), 
        &(l->birthYear), &(l->sex), &(l->avSal));
    return l;
}  

void readAllLivers(FILE* stream, LinkedList* list) {
    Liver* cur;
    while(cur = readLiver(stream)) {
        if(!cur) break;
        insertLiver(list, cur);
    }
}
