#include "LinkedList.h"
#include "Liver.h"
#include <stdio.h>

void deleteLiver(LinkedList* livers, LinkedList* st);
void addLiver(LinkedList* livers, LinkedList* st);
void changeLiver(LinkedList* livers, LinkedList* st);
void searchLiver(LinkedList* livers, LinkedList* st);
Node* findLiverNode(LinkedList *livers, Liver* tar);
void printLivers(LinkedList* livers, LinkedList* st);
void undoHalfN(LinkedList* livers, LinkedList* st);
Liver* readLiver(FILE* stream);
void readAllLivers(FILE* stream, LinkedList* list);

void printSearchInfo();
void printLiverStructInfo();
void printChangeInfo();