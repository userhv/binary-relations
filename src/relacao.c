#include <stdio.h>
#include <stdlib.h>
#define MAX 5050

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
  int *par_eixo_x = NULL, *par_eixo_y = NULL;
  par_eixo_x = (int *)calloc(size_new + 2, sizeof(int));
  par_eixo_y = (int *)calloc(size_new + 2, sizeof(int));

  int pos_x = 0, pos_y = 0;
  for (int i = 0; i <= size_new; i++)
  {
    if (i % 2 == 0)
    {
      par_eixo_x[pos_x] = numbers_arc[count];
      count++;
      pos_x++;
    }
    else
    {
      par_eixo_y[pos_y] = numbers_arc[count];
      count++;
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
  return matriz_aloc;
}
/*TODAS AS RELAÇÕES*/
char reflexiva(int **matriz_complete, int line, int *vetor_resposta, int *tam_res)
{
  char resposta = ' ';
  int contador = 0, it_res = 0;
  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((i == j) && (matriz_complete[i][j] == 1))
      {
        contador++;
      }
      else if (matriz_complete[i][j] == 0 && i == j)
      {
        vetor_resposta[it_res] = matriz_complete[i][0];
        vetor_resposta[it_res + 1] = matriz_complete[0][j];
        it_res += 2;
      }
    }
  }
  *tam_res = it_res;
  if (contador == line)
  {
    return resposta = 'V';
  }
  else
    return resposta = 'F';
}
char irreflexiva(int **matriz_complete, int line, int *vetor_resposta, int *tam_res)
{
  char resposta = ' ';
  int contador = 0, it_res = 0;
  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((i == j) && (matriz_complete[i][j] == 0))
      {
        contador++;
      }
      else if ((i == j) && (matriz_complete[i][j] == 1))
      {
        vetor_resposta[it_res] = matriz_complete[i][0];
        vetor_resposta[it_res + 1] = matriz_complete[0][j];
        it_res += 2;
      }
    }
  }
  *tam_res = it_res;
  if (contador == line)
  {
    return resposta = 'V';
  }
  else
    return resposta = 'F';
}
char simetrica(int **matriz_complete, int line, int *vetor_resposta, int *tam_res)
{
  char resposta;
  int contador = 0, it_res = 0;

  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((matriz_complete[i][j] != 1 && matriz_complete[j][i] == 1) ||
          (matriz_complete[i][j] == 1 && matriz_complete[j][i] != 1))
      {
        contador++;
      }
      if (matriz_complete[i][j] == 0 && matriz_complete[j][i] == 1)
      {
        vetor_resposta[it_res] = matriz_complete[i][0];
        vetor_resposta[it_res + 1] = matriz_complete[0][j];
        it_res += 2;
      }
    }
  }
  *tam_res = it_res;
  if (contador != 0)
  {
    return resposta = 'F';
  }
  else
  {
    return resposta = 'V';
  }
}
char anti_simetrica(int **matriz_complete, int line, int *vetor_resposta, int *tam_res)
{
  char resposta = ' ';
  int contador = 0, it_res = 0;

  for (int i = 1; i <= line; i++)
  {
    for (int j = 1; j <= line; j++)
    {
      if ((matriz_complete[i][j] == 1 && matriz_complete[j][i] == 1) && i != j)
      {
        contador++;
        vetor_resposta[it_res] = matriz_complete[0][j];
        vetor_resposta[it_res + 1] = matriz_complete[i][0];
        it_res += 2;
      }
    }
  }
  *tam_res = it_res;
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
char transitiva(int **matriz_complete, int line, int *vetor_resposta, int *tam_res)
{
  char resposta;
  int contador = 0, it_res = 0;
  int vetorAuxTran[2] = {0, 0};
  for (int z = 1; z <= line; z++)
  {
    for (int i = 1; i <= line; i++)
    {
      for (int j = 1; j <= line; j++)
      {
        if (matriz_complete[i][j] == 1 && matriz_complete[j][z] == 1 && matriz_complete[i][z] != 1)
        {
          contador++;
          if (vetorAuxTran[0] != matriz_complete[i][0])
          {
            vetor_resposta[it_res] = matriz_complete[i][0];
            vetor_resposta[it_res + 1] = matriz_complete[0][z];
            it_res += 2;
            vetorAuxTran[0] = matriz_complete[i][0];
            vetorAuxTran[1] = matriz_complete[0][z];
          }
          else if (vetorAuxTran[0] == matriz_complete[i][0])
          {
            if (vetorAuxTran[1] != matriz_complete[0][z])
            {
              vetor_resposta[it_res] = matriz_complete[i][0];
              vetor_resposta[it_res + 1] = matriz_complete[0][z];
              it_res += 2;
              vetorAuxTran[0] = matriz_complete[i][0];
              vetorAuxTran[1] = matriz_complete[0][z];
            }
          }
        }
      }
    }
  }
  *tam_res = it_res;
  if (contador != 0)
  {
    int count = 0;
    for (int i = 1; i <= line; i++)
    {
      for (int j = 1; j <= line; j++)
      {
        if (matriz_complete[i][0] == vetor_resposta[count] && matriz_complete[0][j] == vetor_resposta[count + 1])
        {
          matriz_complete[i][j] = 1;
          count += 2;
        }
        if (count >= it_res)
        {
          return resposta = 'F';
        }
      }
    }
    return resposta = 'F';
  }
  else
  {
    return resposta = 'V';
  }
}
void imprimir_resposta(int *vetor_resposta, int tam_res)
{
  for (int i = 0; i < tam_res; i += 2)
  {
    printf("(%d,%d); ", vetor_resposta[i], vetor_resposta[i + 1]);
  }
  printf("\n");
}