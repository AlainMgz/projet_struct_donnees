#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "ex2.h"
#include "sha256.h"

List* listdir(char* root_dir) {
    DIR* dir = opendir(root_dir);
    struct dirent* ent;
    List* res = initList();
    while((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            Cell* c = buildCell(ent->d_name);
            insertFirst(res, c);
        }
    }
    free(dir);
    return res;
}

int file_exists(char* file) {
    List* l = listdir(".");
    Cell* c = searchList(l, file);
    int res = 0;
    if (c) {
        res = 1;
    }
    freeList(l);
    return res;
}

void cp(char* to, char* from) {
    FILE* f1 = fopen(from, "r");
    if (f1) {
        FILE* f2 = fopen(to, "w");
        char* line = (char*)malloc(sizeof(char)*1024);
        while(fgets(line, 1024, f1) != NULL) {
            fputs(line, f2);
        }
        fclose(f2);
        fclose(f1);
        free(line);
    }   
}

char* hashToPath(char* hash) {
    int i = 0;
    char* res = (char*)malloc(sizeof(char)*257);
    res[0] = 0;
    while (i<strlen(hash)) {
        if (i == 2) {
            strcat(res, "/");
        } else {
            if (i>2) {
                strncat(res, &hash[i-1], 1);
            } else {
                strncat(res, &hash[i], 1);
            }
        }
        i++;
    }
    strncat(res, &hash[i-1], 1);
    return res;
}

void blobFile(char* file, int ext) {
    char* hash = sha256file(file);
    char* dir = (char*)malloc(sizeof(char)*256);
    char* path = hashToPath(hash);
    if (ext == 1) {
        strcat(path, ".t");
    }
    sscanf(path, "%2s", dir);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "mkdir %s", dir);
    system(buffer);
    cp(path, file);
    free(dir);
    free(path);
    free(hash);
}

/*
int main() {
    List* l = listdir("/home/leni/Documents/Etudes/L2/Struct_de_donnees/projet/projet_struct_donnees");
    char* s = ltos(l);
    printf(s);
    free(s);
    printf("\n");
    freeList(l);
    printf("%d", file_exists("ex2.c"));
    printf("\n");
    cp("test2", "test1");
    char* hash = hashToPath("1234sdfsdret435fst543rgfs");
    printf(hash);
    free(hash);
    printf("\n");
    blobFile("ex2.c", 0);
    
    return 0;
}
*/