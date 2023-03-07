#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ex4.h"
#include "../Semaine1/ex3.h"
#include "../Semaine1/sha256.h"

char* blobWorkTree(WorkTree* wt) {
    wttf(wt, "temp.wt");
    blobFile("temp.wt", 1);
    char* res = sha256file("temp.wt");
    system("rm temp.wt");
    return res;
}

int isDir(const char* fileName)
{
    struct stat path;

    stat(fileName, &path);

    return S_ISREG(path.st_mode);
}

char* saveWorkTree(WorkTree* wt, char* path) {
    for (int i = 0; i<wt->n; i++) {
        WorkFile* wf = &(wt->tab[i]);
        char* pathf = malloc(sizeof(char)*256);
        pathf[0] = 0;
        strcat(pathf, path);
        strcat(pathf, wf->name);
        if (isDir(pathf) != 0) {
            blobFile(pathf, 0);
            char* hash = sha256file(pathf);
            wf->hash = hash;
            wf->mode = getChmod(pathf);
        } else {
            List* l = listdir(pathf);
            WorkTree* newWT = initWorkTree();
            Cell* c = *l;
            while (c) {
                appendWorkTree(newWT, c->data, NULL, 0);
                c = c->next;
            }
            char* hash = saveWorkTree(newWT, pathf);
            wf->hash = hash;
            wf->mode = getChmod(pathf);
        }
        
    }
    return blobWorkTree(wt);
}

void restoreWorkTree(WorkTree* wt, char* path) {
    for (int i = 0; i<wt->n; i++) {
        WorkFile* wf = &(wt->tab[i]);
        char* ext = strrchr(wf->hash,'.');
        if (ext == NULL ) {
            char* dest = malloc(sizeof(char)*256);
            dest[0] = 0;
            strcat(dest, path);
            strcat(dest, wf->name);
            char* src = malloc(sizeof(char)*256);
            src[0] = 0;
            strcat(src, wf->hash);
            cp(dest, src);
            setMode(wf->mode, dest);
        } else {
            if(strcmp(ext,".t") == 0) {
                WorkTree* newWT = ftwt(wf->hash);
                strcat(path, wf->name);
                strcat(path, "/");
                restoreWorkTree(newWT, path);
            }
        }
        
    }
}

int main() {
    WorkTree* wt = initWorkTree();
    List* l = listdir("/home/leni/Documents/Etudes/L2/Struct_de_donnees/projet/projet_struct_donnees/Semaine2/Test/");
    Cell* c = *l;
    while (c) {
        appendWorkTree(wt, c->data, NULL, 0);
        c = c->next;
    }
    saveWorkTree(wt, "/home/leni/Documents/Etudes/L2/Struct_de_donnees/projet/projet_struct_donnees/Semaine2/Test/");
    //restoreWorkTree(wt, "/home/leni/Documents/Etudes/L2/Struct_de_donnees/projet/projet_struct_donnees/Semaine2/Test/");
    return 0;
}