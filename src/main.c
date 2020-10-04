#include <stdio.h>
#include <stdlib.h>
#include "libmd.h"
#define MAX 5050

int main(int argc, char *argv[])
{
  int **matriz_int_aloc = NULL;
  int linhas = 0, tam_res = 0;
  char rpt_reflexiva, rpt_irreflexiva, rpt_simetrica, rpt_anti_simetrica, rpt_assimetrica, rpt_transitiva, rpt_fecho;
  FILE *arq;
  arq = fopen(argv[1], "r");
  matriz_int_aloc = rlc_binary(arq, &linhas);
  fclose(arq);
  int vetor_resposta[MAX] = {};
  rpt_reflexiva = reflexiva(matriz_int_aloc, linhas, vetor_resposta, &tam_res);
  if (rpt_reflexiva == 'V')
  {
    printf("Reflexiva: V\n");
  }
  else if (rpt_reflexiva == 'F')
  {
    printf("Reflexiva: F\n");
    imprimir_resposta(vetor_resposta, tam_res);
  }

  rpt_irreflexiva = irreflexiva(matriz_int_aloc, linhas, vetor_resposta, &tam_res);
  if (rpt_irreflexiva == 'V')
  {
    printf("Irreflexiva: V\n");
  }
  else if (rpt_irreflexiva == 'F')
  {
    printf("Irreflexiva: F\n");
    imprimir_resposta(vetor_resposta, tam_res);
  }

  rpt_simetrica = simetrica(matriz_int_aloc, linhas, vetor_resposta, &tam_res);
  if (rpt_simetrica == 'V')
  {
    printf("Simétrica: V\n");
  }
  else if (rpt_simetrica == 'F')
  {
    printf("Simétrica: F\n");
    imprimir_resposta(vetor_resposta, tam_res);
  }

  rpt_anti_simetrica = anti_simetrica(matriz_int_aloc, linhas, vetor_resposta, &tam_res);
  if (rpt_anti_simetrica == 'V')
  {
    printf("Anti-simétrica: V\n");
  }
  else if (rpt_anti_simetrica == 'F')
  {
    printf("Anti-simétrica: F\n");
    imprimir_resposta(vetor_resposta, tam_res);
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

  rpt_transitiva = transitiva(matriz_int_aloc, linhas, vetor_resposta, &tam_res);
  if (rpt_transitiva == 'V')
  {
    printf("Transitiva: V\n");
  }
  else if (rpt_transitiva == 'F')
  {
    printf("Transitiva: F\n");
    imprimir_resposta(vetor_resposta, tam_res);
  }
  if (rpt_reflexiva == 'V' && rpt_transitiva == 'V' && rpt_simetrica == 'V')
  {
    printf("Relação de equivalência: V\n");
  }
  else
  {
    printf("Relação de equivalência: F\n");
  }

  if (rpt_reflexiva == 'V' && rpt_transitiva == 'V' && rpt_anti_simetrica == 'V')
  {
    printf("Relação de ordem parcial: V\n");
  }
  else
  {
    printf("Relação de ordem parcial: F\n");
  }
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
    int vetorAuxTran[2] = {0, 0};
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
  free_aloc_int(matriz_int_aloc, linhas);
  return 0;
}