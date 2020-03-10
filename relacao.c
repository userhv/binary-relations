#include <stdio.h>
#include <stdlib.h>
#include "libmd.h"
#define MAX 2500
 
/* INSTALLABLE VERSION :
  PATCH NOTES:
    - Verificar alocação dinamica
    - Corrigir a função "transitiva" e sua impressão no main
    - O algoritmo precisa ser otimizado
    - O algoritmo precisa ser sintetizado
    - beta.8
*/

int** aloc_int(int num_ln)
  {
    int** mat_aloc;
    mat_aloc = (int**)calloc(num_ln+1,sizeof(int*));
    for(int aux1 = 0; aux1 < num_ln+1; aux1++)
      {
        mat_aloc[aux1] = (int*)calloc(num_ln+1,sizeof(int));
      }
    if (mat_aloc == NULL)
      {
        printf("Houve um erro\n");
      }
    return mat_aloc;
}
void free_aloc_int(int** free_int, int tam_int)
  {
    for(int aux3 = 0; aux3 < tam_int+1; aux3++)
      {
        free(free_int[aux3]);
      }
    free(free_int);   
  }

/*Essa função recebe a matriz alocada*/
int** number_ln(FILE* arc, int* size){
    int numbers_arc[MAX];
    int i = 0, init, linha_new,count;
    int** matriz_aloc;
    rewind(arc);
    if (arc == NULL)
      {
        printf("!!!!ERROR!!!!\n");
        exit;
      }

    while(!feof(arc))
      {
        fscanf(arc, "%d",&numbers_arc[i]); 
        i++;      
      }
    linha_new = i - 1;
    init = numbers_arc[0];
    *size = init;
    matriz_aloc = aloc_int(init);
    count = 1;
    for (int aux_1 = 1; aux_1 <= init ; aux_1++)
      {
        matriz_aloc[aux_1][0] = numbers_arc[count];
        count++;
      }
    count = 1;
    for (int aux_2 = 1; aux_2 <= init ; aux_2++)
      {
        matriz_aloc[0][aux_2] = numbers_arc[count];
        count++;
      }
    matriz_aloc[0][0] = 0;   
    count = init+1;
      
    int size_new = (i-1) - (numbers_arc[0]+1) ;
    int* vetor_aux;
    vetor_aux = (int*)calloc(size_new-1,sizeof(int));
    par.eixo_x = (int*)calloc(size_new/2,sizeof(int));
    par.eixo_y = (int*)calloc(size_new/2,sizeof(int));
    for(int aux_1 = 0; aux_1 < size_new; aux_1++)
        {
          vetor_aux[aux_1] = numbers_arc[count];
          count++;
        }
    int aux_8 = 0;
    for(int j = 0; j < size_new/2; j++) {
        par.eixo_x[j] = vetor_aux[aux_8];
        par.eixo_y[j] = vetor_aux[aux_8+1];
        aux_8+=2;
    }
    int aux_3 = 0;
    for(int aux_2 = 0; aux_2 < size_new; aux_2++)
      {
        for(int linha_x = 1; linha_x <= init; linha_x++)
          {
            for(int linha_y = 1; linha_y <= init; linha_y++)
              {
                if((matriz_aloc[linha_x][0] == par.eixo_x[aux_3]) && (matriz_aloc[0][linha_y] == par.eixo_y[aux_3]))
                  {
                    matriz_aloc[linha_x][linha_y] = 1;
                    aux_3++;    
                  }
              }
          }
      }
    free(par.eixo_x);
    free(par.eixo_y);
    free(vetor_aux);
  return matriz_aloc;
}

 /*TODAS AS FUNÇÕES E SUAS PROPRIEDADES*/
char reflexiva(int** matriz_complete, int line)
  {
    char resposta;
    int contador = 0;
    for(int i = 1; i <= line; i++){
      for(int j = 1; j <= line; j++){
        if ((i==j) && (matriz_complete[i][j] == 1)){
          contador++;
        }
      }
    }
    if(contador == line){
      return resposta = 'V';
    }
    else 
      return resposta = 'F';
  }

char irreflexiva(char rpt_reflexiva)
  {
    char resposta;
    if(rpt_reflexiva == 'V'){
      return resposta = 'F';
    }
    else{
      return resposta = 'V';
    }
  }
char simetrica(int** matriz_complete, int line, char resposta_flexiva)
  {
    char resposta;
    int contador = 0;
    if(resposta_flexiva == 'F'){
      return resposta = 'F';
    }
    else if(resposta_flexiva == 'V'){
      for(int i = 0; i <= line; i++){
        for(int j = 1; j <= line; j++){
          if(matriz_complete[i][j] == 1 && matriz_complete[j][i] == 1 && i != j){
            contador++;
          }

        }
      }
    }
    if(line*2 == contador){
      return resposta = 'V';
    }
    else if(line*2 != contador) {
      return resposta = 'F';
    }
  }
char anti_simetrica(int** matriz_complete,int line,char resposta_reflexiva)
  {
    char resposta;
    int contador = 0;
    if(resposta_reflexiva == 'V'){
      for(int i = 1; i <= line; i++){
        for(int j = 1; j <= line; j++){
          if ((matriz_complete[i][j] || (matriz_complete[j][i]) == 0) && (i != j)){
            contador++;
          }

        }
      }
    }
    else if (resposta_reflexiva == 'F')
      {
        return resposta = 'F';
      }
    if(line*2 == contador)
      {
        return resposta = 'V';
      }
    else if (line*2 != contador)
      {
        return resposta = 'F';
      }
  }
char assimetrica(char resposta_reflexiva,char resposta_anti_simetrica)
  {
    char resposta;
    if(resposta_reflexiva == 'F' && resposta_anti_simetrica == 'F')
    {
      return resposta = 'V';
    }
    else
    {
        return resposta = 'F';
    }    
  }


char transitiva(int** matriz_complete,int line)
  {
    char resposta;
    int contador = 0;
    for(int z = 1; z <= line; z++){
      for(int i = 1; i <= line; i++){
        for(int j = 1; j <= line; j++){
          if(matriz_complete[i][j] == 1 && matriz_complete[j][z] == 1 && matriz_complete[i][z] == 1){
            contador++;
            //printf(" (%d, %d), (%d, %d), (%d, %d); ",matriz_complete[i][0],matriz_complete[0][j],matriz_complete[j][0],matriz_complete[0][z], matriz_complete[i][0],matriz_complete[0][z]);
            //printf("\n");
          }
        }
      }
    }
    if(contador == line*9){
      return resposta = 'V';
    }
    else 
      return resposta = 'F';
  }
char fecho_transitivo(char resposta_transitiva)
  {
    char resposta;
    if (resposta_transitiva == 'V')
      {
        return resposta = 'V';
      }
    else 
      {
        return resposta = 'F';
      }
  }

//--------------- FUNÇÃO PRINCIPAL -------------------//
 
int main(int argc, char* argv[ ]){                        
    int** matriz_int_aloc;
    int linhas;
    char rpt_reflexiva, rpt_irreflexiva, rpt_simetrica, rpt_anti_simetrica, rpt_assimetrica, rpt_transitiva,rpt_fecho;
    FILE *arq;
    arq = fopen(argv[1],"r");
    
    matriz_int_aloc = number_ln(arq, &linhas);
    printf("Propriedades:\n");
    rpt_reflexiva = reflexiva(matriz_int_aloc,linhas);
    if(rpt_reflexiva == 'V')
      {
        printf("1. Reflexiva: V\n");
      }
    else if(rpt_reflexiva == 'F')
      {
        printf("1. Reflexiva: F\n");
        for(int i = 0; i <= linhas; i++)
          {
          for(int j = 1; j <= linhas; j++)
            {
              if((i == j) && matriz_int_aloc[i][j] == 0 )
                {
                  printf(" (%d, %d); ",matriz_int_aloc[i][0],matriz_int_aloc[0][j]);
                }
              }
            }
        printf("\n");
      }

    rpt_irreflexiva = irreflexiva(rpt_reflexiva);
    if(rpt_irreflexiva == 'V')
      {
          printf("2. Irreflexiva: V\n");
      }
    else if(rpt_irreflexiva == 'F')
      {
        printf("2. Irreflexiva: F\n");
        for(int i = 0; i <= linhas; i++)
          {
          for(int j = 1; j <= linhas; j++)
            {
              if((i == j) && matriz_int_aloc[i][j] == 1)
                {
                   printf(" (%d, %d); ",matriz_int_aloc[i][0],matriz_int_aloc[0][j]);                    
                }
            }        
        }
        printf("\n");
      }
    
    rpt_simetrica = simetrica(matriz_int_aloc,linhas,rpt_reflexiva);
    if(rpt_simetrica == 'V')
      {
          printf("3. Simetrica: V\n");
      }
    else if(rpt_simetrica == 'F')
      {
        printf("3. Simetrica: F\n");
        for(int i = 0; i <= linhas; i++)
          {
          for(int j = 1; j <= linhas; j++)
            {
              if(matriz_int_aloc[i][j] == 1 && matriz_int_aloc[j][i]== 0 || matriz_int_aloc[i][j] == 0 &&
                  matriz_int_aloc[j][i]== 1 || (matriz_int_aloc[i][j] && matriz_int_aloc[j][i]) == 0 && i == j)
                { 
                      printf(" (%d, %d); ",matriz_int_aloc[i][0],matriz_int_aloc[0][j]);                
                }
            }
        }
        printf("\n");
      }

    rpt_anti_simetrica = anti_simetrica(matriz_int_aloc,linhas,rpt_reflexiva);
    if(rpt_anti_simetrica == 'V')
      {
        printf("4. Anti-simetrica: V\n");
      }
    else if(rpt_anti_simetrica == 'F')
      {
        printf("4. Anti-simetrica: F\n");
        for(int i = 0; i <= linhas; i++)
          {
          for(int j = 1; j <= i; j++)
            {
              if((matriz_int_aloc[i][j] == matriz_int_aloc[j][i]) && matriz_int_aloc[i][j] == 1 && matriz_int_aloc[j][i] == 1 && i != j)
                {
                  printf(" (%d, %d) e (%d, %d); ", matriz_int_aloc[0][j],matriz_int_aloc[i][0], matriz_int_aloc[i][0],matriz_int_aloc[0][j]);
                }
            }
        }
        printf("\n");
      }

    rpt_assimetrica = assimetrica(rpt_reflexiva,rpt_anti_simetrica);
    if(rpt_assimetrica == 'V')
      {
          printf("5. Assimetrica: V\n");
      }
    else if(rpt_assimetrica == 'F')
      {
        printf("5. Assimetrica: F\n");
        }
     
    rpt_transitiva = transitiva(matriz_int_aloc,linhas);
    if(rpt_transitiva == 'V')
      {
          printf("6. Transitiva: V\n");
      }
    else if(rpt_transitiva == 'F')
      {
        printf("6. Transitiva: F\n");
        for(int z = 1; z <= linhas; z++)
          {
            for(int i = 1; i <= z; i++)
              {
                for(int j = 1; j <= i; j++)
                {
                  if(matriz_int_aloc[i][j] == 0 && matriz_int_aloc[j][z] == 1 && matriz_int_aloc[i][z] != 1)
                    {
                     // printf(" (%d, %d) ; ",matriz_int_aloc[i][0],matriz_int_aloc[0][z]);
                    }
                }  
              }
            }
        printf("\n");
      }
    printf("\n");
    if(rpt_reflexiva == 'V' && rpt_transitiva == 'V' && rpt_simetrica == 'V')
      printf("Relação de ordem de equivalência: V\n");       
    else
    printf("Relação de ordem de equivalência: F\n");

    if(rpt_reflexiva == 'V' && rpt_transitiva == 'V' && rpt_anti_simetrica == 'V')
      printf("Relação de ordem parcial: V\n");    
    else 
    printf("Relação de ordem parcial: F\n");
    
    printf("\n");
    rpt_fecho = fecho_transitivo(rpt_transitiva);
    if (rpt_fecho == 'V')
      {
        printf("Fecho transitivo da relação = {");       
          for(int i = 0; i <= linhas; i++)
          {
            for(int j = 1; j <= linhas; j++)
              {
                if(matriz_int_aloc[i][j] == 1 && matriz_int_aloc[j][i] == 1)
                  {  
                    printf(" (%d, %d); ",matriz_int_aloc[i][0],matriz_int_aloc[0][j]);              
                  }
              }
          }        
        printf("}");
        printf("\n");
      }

    fclose(arq);
    free_aloc_int(matriz_int_aloc,linhas);
    return 0;
  }