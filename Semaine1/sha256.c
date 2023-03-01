#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashFile(char* source, char* dest) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "sha256sum %s > %s", source, dest);
    system(buffer);
    return 0;
}

char* sha256file(char* file) {
    static char template[] = "/tmp/project_structXXXXXX" ;
    char fname[1000];
    strcpy(fname, template);
    int fd = mkstemp(fname);
    hashFile(file, fname);
    FILE* dest = fopen(fname, "r");
    char buffer[512];
    char nom_du_fichier[512];
    char* res = (char*)malloc(sizeof(char)*256);
    while (fgets(buffer,512,dest) != NULL) {
        sscanf(buffer, "%s %s", res, nom_du_fichier);
    }
    fclose(dest);
    return res;
}

/*
int main(int argc, char** argv){
    //hashFile(strdup(argv[1]), strdup(argv[2]));
    //system("sha256sum main.c > file.tmp");
    char* hash = sha256file("main.c");
    printf("hash: %s\n", hash);
    free(hash);
    return 0;
} */