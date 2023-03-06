#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ex4.h"


int getChmod ( const char * path ) {
    struct stat ret ;
    if ( stat ( path , & ret ) == -1) {
        return -1;
    }

    return ( ret . st_mode & S_IRUSR ) |( ret . st_mode & S_IWUSR ) |( ret . st_mode & S_IXUSR ) |/*
    owner*/
    ( ret . st_mode & S_IRGRP ) |( ret . st_mode & S_IWGRP ) |( ret . st_mode & S_IXGRP ) |/*
    group*/
    ( ret . st_mode & S_IROTH ) |( ret . st_mode & S_IWOTH ) |( ret . st_mode & S_IXOTH ) ;/*
    other*/
}

void setMode ( int mode , char * path ) {
    char buff [100];
    sprintf ( buff , "chmod %d %s " , mode , path ) ;
    system ( buff ) ;
}

WorkFile* createWorkFile(char* name) {
    WorkFile* wf = malloc(sizeof(WorkFile));
    wf->name = name;
    wf->hash = NULL;
    wf->mode = 0;
    return wf;
}

char* wfts(WorkFile* wf) {
    char* buff = malloc(sizeof(char)*256);
    sprintf(buff, "%s\t%s\t%d", wf->name, wf->hash, wf->mode);
    return buff;
}

WorkFile* stwf(char* ch) {
    WorkFile* wf = malloc(sizeof(WorkFile));
    char* name = malloc(sizeof(char)*256);
    char* hash = malloc(sizeof(char)*256);
    int mode;
    sscanf(ch, "%s\t%s\t%d", name, hash, &mode);
    wf->name = name;
    wf->hash = hash;
    wf->mode = mode;
    return wf;
}

WorkTree* initWorkTree() {
    WorkTree* wt = malloc(sizeof(WorkTree));
    wt->tab = malloc(sizeof(WorkFile)*256);
    wt->size = 256;
    wt->n = 0;
    return wt;
}

int inWorkTree(WorkTree* wt, char* name) {
    for(int i = 0; i < wt->n; i++) {
        if(strcmp(wt->tab[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode) {
    if(wt->n == wt->size || inWorkTree(wt, name) != -1) {
        return -1;
    }
    wt->tab[wt->n].name = name;
    wt->tab[wt->n].hash = hash;
    wt->tab[wt->n].mode = mode;
    wt->n++;
    return 0;
}

char* wtts(WorkTree* wt) {
    char* buff = malloc(sizeof(char)*256*wt->n);
    for(int i = 0; i < wt->n; i++) {
        strcat(buff, wfts(&wt->tab[i]));
        strcat(buff, "\n");
    }
    return buff;
}

WorkTree* stwt(char* wts) {
    WorkTree* wt = initWorkTree();
    char* buff = malloc(sizeof(char)*256);
    int i = 0;
    while(wts[i] != '\0') {
        if(wts[i] == '\n') {
            appendWorkTree(wt, stwf(buff)->name, stwf(buff)->hash, stwf(buff)->mode);
            buff = malloc(sizeof(char)*256);
        } else {
            buff[strlen(buff)] = wts[i];
        }
        i++;
    }
    return wt;
}

int wttf(WorkTree* wt, char* file) {
    FILE* f = fopen(file, "w");
    if(f == NULL) {
        return -1;
    }
    fprintf(f, "%s", wtts(wt));
    fclose(f);
    return 0;
}

WorkTree* ftwt(char* file) {
    FILE* f = fopen(file, "r");
    if(f == NULL) {
        return NULL;
    }
    char* buff = malloc(sizeof(char)*256);
    char* wts = malloc(sizeof(char)*256);
    while(fgets(buff, 256, f) != NULL) {
        strcat(wts, buff);
    }
    fclose(f);
    return stwt(wts);
}

void freeWorkTree(WorkTree* wt) {
    free(wt->tab);
    free(wt);
}

/*
int main() {
    WorkTree* wt = initWorkTree();
    appendWorkTree(wt, "test1", "hash1", 1);
    appendWorkTree(wt, "test2", "hash2", 2);
    appendWorkTree(wt, "test3", "hash3", 3);
    wttf(wt, "test.txt");
    WorkTree* wt2 = ftwt("test.txt");
    printf("%s", wtts(wt2));
    freeWorkTree(wt);
    freeWorkTree(wt2);
    return 0;
}
*/