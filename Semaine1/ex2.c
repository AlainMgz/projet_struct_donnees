#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell {
char * data ;
struct cell * next ;
} Cell ;

typedef Cell* List ;

List* initList() {
    List* res = (List*)malloc(sizeof(List));
    return res;
}

Cell* buildCell(char* ch) {
    Cell* c = (Cell*)malloc(sizeof(Cell));
    c->data=strdup(ch);
    c->next=NULL;
    return c;
}

void insertFirst(List *L, Cell* C) {
    C->next=*L;
    (*L)->next=C;
}

int main() {
    return 0;
}