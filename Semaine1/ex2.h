typedef struct cell {
char * data ;
struct cell * next ;
} Cell ;
typedef Cell* List ;

List* initList();
Cell* buildCell(char* ch);
void insertFirst(List *L, Cell* C);
char* ctos(Cell* c);
char* ltos(List* l);
Cell* listGet(List* l, int i);
Cell* searchList(List* l, char* str);
List* stol(char* s);
void ltof(List* l, char* path);
List* ftol(char* path);
void freeList(List* l);