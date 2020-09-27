#ifndef MD_LIB
#define MD_LIB

int **aloc_int(int);
void free_aloc_int(int **, int);
int **rlc_binary(FILE *, int *);
char reflexiva(int **, int, int *, int *);
char irreflexiva(int **, int, int *, int *);
char simetrica(int **, int, int *, int *);
char anti_simetrica(int **, int, int *, int *);
char assimetrica(char, char);
char transitiva(int **, int, int *, int *);
void imprimir(int *, int);

#endif