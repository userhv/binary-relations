#ifndef MD_LIB
#define MD_LIB

int** aloc_int(int );
void free_aloc_int(int** , int);
int** rlc_binary(FILE* , int*);
char reflexiva(int** , int);
char irreflexiva(int** , int);
char simetrica(int** , int);
char anti_simetrica(int** ,int);
char assimetrica(char , char);
char transitiva(int** , int);

#endif