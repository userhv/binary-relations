#include <stdio.h>
#include <stdlib.h>
#include "libmd.h"
#define MAX 3000


int **aloc_int(int num_ln)
{
  int **mat_aloc;
  int aux = num_ln + 1;
  mat_aloc = (int **)calloc(aux, sizeof(int *));
  for (int aux1 = 0; aux1 < num_ln + 1; aux1++)
  {
    mat_aloc[aux1] = (int *)calloc(aux, sizeof(int));
  }
  if (mat_aloc == NULL)
  {
    printf("Houve um erro\n");
  }
  return mat_aloc;
}
void free_aloc_int(int **free_int, int tam_int)
{
  for (int aux3 = 0; aux3 < tam_int + 1; aux3++)
  {
    free(free_int[aux3]);
  }
  free(free_int);
}

/*Função principal do algoritmo*/
int **rlc_binary(FILE *arc, int *size)
{
  int numbers_arc[MAX] = {};
  int pos = 0, init = 0, linha_new = 0, count = 1;
  int **matriz_aloc = NULL;
  rewind(arc);
  if (arc == NULL)
  {
    printf("!!!!ERROR!!!!\n");
    exit;
  }
  while (!feof(arc))
  {
    fscanf(arc, "%d", &numbers_arc[pos]);
    ;
    pos++;
  }
  linha_new = pos - 1;
  init = numbers_arc[0];
  *size = init;
  matriz_aloc = aloc_int(init);
  for (int i = 1; i <= init; i++)
  {
    matriz_aloc[i][0] = numbers_arc[count];
    matriz_aloc[0][i] = numbers_arc[count];
    count++;
  }
  matriz_aloc[0][0] = 0;
  count = init + 1;
  int size_new = (pos - 1) - (numbers_arc[0] + 1);
  int *vetor_aux = NULL, *par_eixo_x = NULL, *par_eixo_y = NULL;
  vetor_aux = (int *)calloc(size_new + 2, sizeof(int));
  par_eixo_x = (int *)calloc(size_new + 2, sizeof(int));
  par_eixo_y = (int *)calloc(size_new + 2, sizeof(int));
  for (int i = 0; i <= size_new; i++)
  {
    vetor_aux[i] = numbers_arc[count];
    count++;
  }

  int pos_x = 0, pos_y = 0;
  for (int i = 0; i <= size_new; i++)
  {
    if (i % 2 == 0)
    {
      par_eixo_x[pos_x] = vetor_aux[i];
      pos_x++;
    }
    else
    {
      par_eixo_y[pos_y] = vetor_aux[i];
      pos_y++;
    }
  }
  pos_x = 0, pos_y = 0;

  for (int i = 0; i <= size_new; i++)
  {
    pos_x = par_eixo_x[i];
    pos_y = par_eixo_y[i];
    for (int x = 1; x <= init; x++)
    {
      if (matriz_aloc[x][0] == pos_x)
      {
        for (int y = 1; y <= init; y++)
        {
          if (matriz_aloc[0][y] == pos_y)
          {
            matriz_aloc[x][y] = 1;
            break;
          }
        }
        break;
      }
    }
  }

  free(par_eixo_x);
  free(par_eixo_y);
  free(vetor_aux);
  return matriz_aloc;
}

/*TODAS AS RELAÇÕES*/
char reflexiva(int **matriz_complete, int line)
{
  char resposta = ' ';
  int contador = 0;
  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((i == j) && (matriz_complete[i][j] == 1))
      {
        contador++;
      }
    }
  }
  if (contador == line)
  {
    return resposta = 'V';
  }
  else
    return resposta = 'F';
}
char irreflexiva(int **matriz_complete, int line)
{
  char resposta = ' ';
  int contador = 0;
  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((i == j) && (matriz_complete[i][j] == 0))
      {
        contador++;
      }
    }
  }
  if (contador == line)
  {
    return resposta = 'V';
  }
  else
    return resposta = 'F';
}
char simetrica(int **matriz_complete, int line)
{
  char resposta;
  int contador = 0;

  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((matriz_complete[i][j] != 1 && matriz_complete[j][i] == 1) ||
          (matriz_complete[i][j] == 1 && matriz_complete[j][i] != 1))
      {
        contador++;
      }
    }
  }
  if (contador != 0)
  {
    return resposta = 'F';
  }
  else
  {
    return resposta = 'V';
  }
}
char anti_simetrica(int **matriz_complete, int line)
{
  char resposta = ' ';
  int contador = 0;

  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((matriz_complete[i][j] == 1 && matriz_complete[j][i] == 1) && i != j)
      {
        contador++;
      }
    }
  }

  if (contador != 0)
  {
    return resposta = 'F';
  }
  else if (contador == 0)
  {
    return resposta = 'V';
  }
}
char assimetrica(char resposta_irreflexiva, char resposta_anti_simetrica)
{
  char resposta;
  if (resposta_irreflexiva == 'V' && resposta_anti_simetrica == 'V')
  {
    return resposta = 'V';
  }
  else
  {
    return resposta = 'F';
  }
}
char transitiva(int **matriz_complete, int line)
{
  char resposta;
  int contador = 0;
  for (int z = 1; z <= line; z++)
  {
    for (int i = 1; i <= line; i++)
    {
      for (int j = 1; j <= line; j++)
      {
        if (matriz_complete[i][j] == 1 && matriz_complete[j][z] == 1 && matriz_complete[i][z] != 1)
        {
          contador++;
        }
      }
    }
  }
  if (contador != 0)
  {
    return resposta = 'F';
  }
  else
    return resposta = 'V';
}

//--------------- FUNÇÃO PRINCIPAL -------------------//

int main(int argc, char *argv[])
{
  int **matriz_int_aloc = NULL;
  int linhas;
  char rpt_reflexiva, rpt_irreflexiva, rpt_simetrica, rpt_anti_simetrica, rpt_assimetrica, rpt_transitiva, rpt_fecho;
  FILE *arq;
  arq = fopen(argv[1], "r");
  matriz_int_aloc = rlc_binary(arq, &linhas);
  rpt_reflexiva = reflexiva(matriz_int_aloc, linhas);
  if (rpt_reflexiva == 'V')
  {
    printf("Reflexiva: V\n");
  }
  else if (rpt_reflexiva == 'F')
  {
    printf("Reflexiva: F\n");
    for (int i = 0; i <= linhas; i++)
    {
      for (int j = 1; j <= linhas; j++)
      {
        if ((i == j) && matriz_int_aloc[i][j] == 0)
        {
          printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][j]);
        }
      }
    }
    printf("\n");
  }

  rpt_irreflexiva = irreflexiva(matriz_int_aloc, linhas);
  if (rpt_irreflexiva == 'V')
  {
    printf("Irreflexiva: V\n");
  }
  else if (rpt_irreflexiva == 'F')
  {
    printf("Irreflexiva: F\n");
    for (int i = 0; i <= linhas; i++)
    {
      for (int j = 1; j <= linhas; j++)
      {
        if ((i == j) && matriz_int_aloc[i][j] == 1)
        {
          printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][j]);
        }
      }
    }
    printf("\n");
  }

  rpt_simetrica = simetrica(matriz_int_aloc, linhas);
  if (rpt_simetrica == 'V')
  {
    printf("Simetrica: V\n");
  }
  else if (rpt_simetrica == 'F')
  {
    printf("Simetrica: F\n");
    for (int i = 1; i <= linhas; i++)
    {
      for (int j = 1; j <= linhas; j++)
      {
        if ((matriz_int_aloc[i][j] == 0 && matriz_int_aloc[j][i] == 1))
        {
          printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][j]);
        }
      }
    }
    printf("\n");
  }

  rpt_anti_simetrica = anti_simetrica(matriz_int_aloc, linhas);
  if (rpt_anti_simetrica == 'V')
  {
    printf("Anti-simétrica: V\n");
  }
  else if (rpt_anti_simetrica == 'F')
  {
    printf("Anti-simétrica: F\n");
    for (int i = 1; i <= linhas; i++)
    {
      for (int j = 1; j <= i; j++)
      {
        if (matriz_int_aloc[i][j] == 1 && matriz_int_aloc[j][i] == 1 && i != j)
        {
          printf("(%d,%d); (%d,%d); ", matriz_int_aloc[0][j], matriz_int_aloc[i][0],
                 matriz_int_aloc[i][0], matriz_int_aloc[0][j]);
        }
      }
    }
    printf("\n");
  }

  rpt_assimetrica = assimetrica(rpt_irreflexiva, rpt_anti_simetrica);
  if (rpt_assimetrica == 'V')
  {
    printf("Assimétrica: V\n");
  }
  else if (rpt_assimetrica == 'F')
  {
    printf("Assimétrica: F\n");
  }

  rpt_transitiva = transitiva(matriz_int_aloc, linhas);
  int vetorAuxTran[2] = {0, 0};
  if (rpt_transitiva == 'V')
  {
    printf("Transitiva: V\n");
  }
  else if (rpt_transitiva == 'F')
  {
    printf("Transitiva: F\n");
    for (int z = 1; z <= linhas; z++)
    {
      for (int i = 1; i <= linhas; i++)
      {
        for (int j = 1; j <= linhas; j++)
        {
          if (matriz_int_aloc[i][j] == 1 && matriz_int_aloc[j][z] == 1 && matriz_int_aloc[i][z] != 1)
          {
            if (vetorAuxTran[0] != matriz_int_aloc[i][0])
            {
              printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][z]);
              vetorAuxTran[0] = matriz_int_aloc[i][0];
              vetorAuxTran[1] = matriz_int_aloc[0][z];
            }
            else if (vetorAuxTran[0] == matriz_int_aloc[i][0])
            {
              if (vetorAuxTran[1] != matriz_int_aloc[0][z])
              {
                printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][z]);
                vetorAuxTran[0] = matriz_int_aloc[i][0];
                vetorAuxTran[1] = matriz_int_aloc[0][z];
              }
            }
          }
        }
      }
    }
    printf("\n");
  }
  if (rpt_reflexiva == 'V' && rpt_transitiva == 'V' && rpt_simetrica == 'V')
    printf("Relação de equivalência: V\n");
  else
    printf("Relação de equivalência: F\n");

  if (rpt_reflexiva == 'V' && rpt_transitiva == 'V' && rpt_anti_simetrica == 'V')
    printf("Relação de ordem parcial: V\n");
  else
    printf("Relação de ordem parcial: F\n");

  printf("Fecho transitivo da relação: ");
  for (int i = 1; i <= linhas; i++)
  {
    for (int j = 1; j <= linhas; j++)
    {
      if (matriz_int_aloc[i][j] == 1)
      {
        printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][j]);
      }
    }
  }

  if (rpt_transitiva == 'F')
  {
    vetorAuxTran[0] = 0;
    vetorAuxTran[1] = 0;
    for (int z = 1; z <= linhas; z++)
    {
      for (int i = 1; i <= linhas; i++)
      {
        for (int j = 1; j <= linhas; j++)
        {
          if (matriz_int_aloc[i][j] == 1 && matriz_int_aloc[j][z] == 1 && matriz_int_aloc[i][z] != 1)
          {
            if (vetorAuxTran[0] != matriz_int_aloc[i][0])
            {
              printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][z]);
              vetorAuxTran[0] = matriz_int_aloc[i][0];
              vetorAuxTran[1] = matriz_int_aloc[0][z];
            }
            else if (vetorAuxTran[0] == matriz_int_aloc[i][0])
            {
              if (vetorAuxTran[1] != matriz_int_aloc[0][z])
              {
                printf("(%d,%d); ", matriz_int_aloc[i][0], matriz_int_aloc[0][z]);
                vetorAuxTran[0] = matriz_int_aloc[i][0];
                vetorAuxTran[1] = matriz_int_aloc[0][z];
              }
            }
          }
        }
      }
    }
  }
  printf("\n");

  fclose(arq);
  free_aloc_int(matriz_int_aloc, linhas);
  return 0;
}