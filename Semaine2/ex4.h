typedef struct {
    char * name ;
    char * hash ;
    int mode ;
} WorkFile ;

typedef struct {
    WorkFile * tab ;
    int size ;
    int n ;
} WorkTree ;

int getChmod ( const char * path );
void setMode ( int mode , char * path );
WorkFile* createWorkFile(char* name);
char* wfts(WorkFile* wf);
WorkFile* stwf(char* ch);
WorkTree* initWorkTree();
int inWorkTree(WorkTree* wt, char* name);
int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode);
void freeWorkTree(WorkTree* wt);
WorkTree* ftwt(char* file);
int wttf(WorkTree* wt, char* file);
WorkTree* stwt(char* wts);
char* wtts(WorkTree* wt);