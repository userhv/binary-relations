#ifndef MD_LIB
#define MD_LIB
struct ordenados
{
    int* eixo_x;
    int* eixo_y;
};
struct ordenados par;

int** aloc_int(int num_ln);
void free_aloc_int(int** free_int, int tam_int);
int** number_ln(FILE* arc, int* size);
char reflexiva(int** matriz_complete, int line);
char irreflexiva(char rpt_reflexiva);
char simetrica(int** matriz_complete, int line, char resposta_flexiva);
char anti_simetrica(int** matriz_complete,int line,char resposta_reflexiva);
char assimetrica(char resposta_reflexiva,char resposta_anti_simetrica);
char transitiva(int** matriz_complete,int line);
char fecho_transitivo(char resposta_transitiva);

#endif