#include "../include/LinkedList.h"
#include "../include/Command.h"

LinkedList create_list() {
    LinkedList l = {NULL, NULL, 0};
    return l;
}

void erase_list(LinkedList *list) {
    if(!list) { 
        return;
    }
    Node *tmp;
    while(list->size) {
        tmp = list->tail;
        pop_back_list(list);
        free(tmp);
    }
}

void delete_list(LinkedList *list) {
    if(!list) { 
        return;
    }
    Liver *tmp;
    while(list->size) {
        tmp = list->tail->data;
        pop_back_list(list);
        free(tmp);
    }
    // free(list);
}

void push_back_list(LinkedList *list, void* value) {
    if(!list) {
        return;
    }
    Node *cur = (Node*)malloc(sizeof(Node));
    cur->next = NULL;
    cur->prev = NULL;
    if(!cur) {
        return;
    }
    cur->data = value;
    if(!list->tail) {
        list->tail = list->head = cur;
    } else {
        list->tail->next = cur;
        cur->prev = list->tail;
        list->tail = cur;
    }
    list->size++;
}

void push_front_list(LinkedList *list, void* value) {
    if(!list) {
        return;
    }
    Node *cur = (Node*)malloc(sizeof(Node));
    cur->next = NULL;
    cur->prev = NULL;
    if(!cur) {
        return;
    }
    cur->data = value;
    if(!list->head) {
        list->tail = list->head = cur;
    } else {
        list->head->prev = cur;
        cur->next = list->head;
        list->head = cur;
    }
    list->size++;
}

// Удаление элемента с конца списка 
void* pop_back_list(LinkedList *list) {
    if(!list || !list->tail) {
        return NULL;
    }
    void* data = list->tail->data;
    if (list->tail == list->head) {
        list->head = NULL;
    } else {
        list->tail->prev->next = NULL; 
    }
    Node* to_free = list->tail;  
    list->tail = list->tail->prev;
    free(to_free);  
    list->size--;
    return data;
}

// Удаление элемента с начала списка 
void* pop_front_list(LinkedList *list) {
    if(!list || !list->head) {
        return NULL;
    }
    void* data = list->head->data;
    if (list->tail == list->head) {
        list->tail = NULL;
    } else {
        list->head->next->prev = NULL; 
    }
    Node* to_free = list->head;  
    list->head = list->head->next;
    free(to_free);  
    list->size--;
    return data;
}
#include <stdio.h>

void insert_at_list(LinkedList *list, size_t index, void* value) {
    if(!list) {
        return;
    }
    if(index == list->size) {
        push_back_list(list, value);
        return;
    }
    if(!index) {
        push_front_list(list, value);
        return;
    }
    if(index > list->size) {
        return;
    }
    Node* cur = list->head, *new = (Node*)malloc(sizeof(Node));
    if(!new) {
        return;
    }
    new->next = NULL;
    new->prev = NULL;
    while(index--) {
        cur = cur->next;
    }
    new->next = cur;
    new->prev = cur->prev;
    cur->prev = new;
    new->prev->next = new;
    new->data = value;
    list->size++;
}

void delete_at_list(LinkedList *list, size_t index) {
    if(!list || index >= list->size) {
        return;
    }
    if(index == list->size - 1) {
        pop_back_list(list);
        return;
    }
    if(!index) {
        pop_front_list(list);
        return;
    }
    Node* cur = list->head;
    while (index--) {
        cur = cur->next;
    }
    cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
    free(cur);
    list->size--;
}

void* get_at_list(const LinkedList *list, size_t index) {
    if(!list) {
        return NULL;
    }
    if(index >= list->size) {
        return NULL;
    }
    Node* cur = list->head;
    while (index--) {
        cur = cur->next;
    }
    return cur->data;
}

int is_equal_list(const LinkedList *l1, const LinkedList *l2) {
    if(!l1 || !l2) {
        return !l1 && !l2;
    }
    if(l1->size != l2->size) {
        return 0;
    }
    Node *u = l1->head, *v = l2->head;
    for(int i = 0; i < l1->size; ++i) {
        if(u->data != v->data) {
            return 0;
        }
        u = u->next;
        v = v->next;
    }
    return 1;
}

void push_stack(LinkedList *stack, void* value) {
    push_back_list(stack, value);
}

void* pop_stack(LinkedList *stack) {
    return pop_back_list(stack);
}

void* peek_stack(const LinkedList *stack) {
    if(!stack->head) {
        return NULL;
    }
    return stack->tail->data;
}

void enqueue(LinkedList *queue, void* value) {
    push_back_list(queue, value);
}

void* dequeue(LinkedList *queue) {
    return pop_front_list(queue);
}

void* peek_queue(const LinkedList *queue) {
    if(!queue->head) {
        return NULL;
    }
    return queue->head->data;
}

int lessByBirth(Liver* a, Liver* b) {
    if(a->birthYear == b->birthYear) {
        if(a->birthMonth == b->birthMonth) {
            return a->birthDay < b->birthDay;
        }
        return a->birthMonth < b->birthMonth;
    }
    return a->birthYear < b->birthYear;
}

int insertLiver(LinkedList* list, Liver* l) {
    int ind = 0;
    Node* cur = list->head;
    while(cur && lessByBirth((Liver*)(cur->data), l)) {
        ind++;
        cur = cur->next;
    }
    insert_at_list(list, ind, (void *)l);
    return ind;
}

void freeStack(LinkedList *st) {
    Command *tmp;
    while(st->size) {
        tmp = (Command *)st->tail->data;
        if(tmp->data) {
            // ptrData только у add
            if(tmp->target == -1) {
                free(tmp->data->ptrData);
            }
            free(tmp->data);
        }
        free(tmp);
        pop_stack(st);
    }
}