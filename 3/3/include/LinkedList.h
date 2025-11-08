#pragma once

#include <stdlib.h>
#include "Liver.h"

// Узел двусвязного списка
typedef struct Node {
    void* data;
    struct Node *prev;
    struct Node *next;
} Node;

// Двусвязный список
typedef struct {
    Node *head; 
    Node *tail; 
    size_t size;
} LinkedList;

// ----------------- БАЗОВЫЕ ОПЕРАЦИИ ----------------
// Создание пустого списка
LinkedList create_list();
// Очистка содержимого списка (удаление всех элементов) 
void erase_list(LinkedList *list);
// Полное удаление списка (освобождение ресурсов)
void delete_list(LinkedList *list);
// Добавление элемента в конец списка
void push_back_list(LinkedList *list, void* value);
// Добавление элемента в начало списка
void push_front_list(LinkedList *list, void* value);
// Удаление элемента с конца списка 
void* pop_back_list(LinkedList *list); 
// Удаление элемента с начала списка 
void* pop_front_list(LinkedList *list);
// Вставка элемента по индексу
void insert_at_list(LinkedList *list, size_t index, void* value);
// Удаление элемента по индексу
void delete_at_list(LinkedList *list, size_t index);
// Получение элемента по индексу
void* get_at_list(const LinkedList *list, size_t index);
// Сравнение двух списков (лексикографически) 
// возвращает 1 — равны, 0 — не равны
int is_equal_list(const LinkedList *l1, const LinkedList *l2);
// ----------------- СТЕК ----------------- 
// Поместить элемент на вершину стека
void push_stack(LinkedList *stack, void* value);
// Извлечь элемент с вершины стека 
void* pop_stack(LinkedList *stack);
// Получить элемент с вершины стека без удаления
void* peek_stack(const LinkedList *stack); 
// ----------------- ОЧЕРЕДЬ -----------------
// Добавить элемент в очередь
void enqueue(LinkedList *queue, void* value);
// Извлечь элемент из очереди 
void* dequeue(LinkedList *queue);
// Получить первый элемент очереди без удаления 
void* peek_queue(const LinkedList *queue); 

// доп функции
int insertLiver(LinkedList* list, Liver* l);
void freeStack(LinkedList *st);