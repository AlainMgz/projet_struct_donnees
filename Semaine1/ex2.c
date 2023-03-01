#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex2.h"

List* initList() {
    List* res = (List*)malloc(sizeof(List));
    *res = NULL;
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
    (*L)=C;
}

char* ctos(Cell* c) {
    return c->data;
}

char* ltos(List* l) {
    char* res = (char*)malloc(sizeof(char)*1024);
    res[0] = 0;
    Cell* c = *l;
    while(c->next != NULL) {
        strcat(res, ctos(c));
        strcat(res, "|");
        c=c->next;
    }
    strcat(res, ctos(c));
    return res;
}

Cell* listGet(List* l, int i) {
    int n=0;
    Cell* res = *l;
    while(n<i) {
        res=res->next;
        n++;
    }
    return res;
}

Cell* searchList(List* l, char* str) {
    Cell* res = *l;
    while(res) {
        if (strcmp(str, res->data) == 0) {
            return res;
        }
        res=res->next;
    }
    return NULL;
}

List* stol(char* s) {
    List* res = initList();
    char* dat;
    dat = strtok (s,"|");
    while (dat != NULL) {
        insertFirst(res, buildCell(dat));
        dat = strtok (NULL, "|");
    }
    return res;
}

void ltof(List* l, char* path) {
    FILE* f = fopen(path, "w");
    Cell* c = *l;
    while(c->next != NULL) {
        fprintf(f, "%s|", ctos(c));
        c=c->next;
    }
    fprintf(f, "%s", ctos(c));
    fclose(f);
}

List* ftol(char* path) {
    FILE* f = fopen(path, "r");
    char* s = (char*)malloc(sizeof(char)*256);
    fscanf(f, "%s", s);
    fclose(f);
    return stol(s);
}

void freeList(List* l) {
    Cell* c = *l;
    Cell* tmp;
    while(c) {
        tmp = c;
        c=c->next;
        free(tmp->data);
        free(tmp);
        tmp=NULL;
    }
    free(l);
}

/*
int main() {
    List *l = initList();
    Cell* c1 = buildCell("cell1");
    insertFirst(l, c1);
    Cell* c2 = buildCell("cell2");
    insertFirst(l, c2);
    Cell* c3 = buildCell("cell3");
    insertFirst(l, c3);
    printf(ltos(l));
    printf("\n");
    printf(ctos(listGet(l, 1)));
    printf("\n");
    printf(ctos(searchList(l, "cell2")));
    printf("\n");
    printf(ltos(stol(ltos(l))));
    printf("\n");
    return 0;
}
*/