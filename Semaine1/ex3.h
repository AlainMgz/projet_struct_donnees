#ifdef XML_EX
#include "ex2.h"
#else
#include "ex2.h"
#endif

List* listdir(char* root_dir);
int file_exists(char* file);
void cp(char* to, char* from);
char* hashToPath(char* hash);
void blobFile(char* file, int ext);