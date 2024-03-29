/* Programa que le um arquivo binario com dois valores inteiros (indicando as dimensoes de uma matrizUM) 
 * e uma sequencia com os valores da matrizUM (em float)
 * Entrada: nome do arquivo de entrada
 * Saida: valores da matrizUM escritos no formato texto (com 6 casas decimais) na saida padrao 
 * */

#include<stdio.h>

#include<stdlib.h>

#include "timer.h"

#include<pthread.h>

int nthreads;
float * matrizUM; //matrizUM que será carregada do arquivo
float * matrizDOIS; //matrizUM que será carregada do arquivo
float * matrizSAIDA; //matrizUM que será carregada do arquivo
int linhasMatriz1, colunasMatriz1; //dimensoes da matrizUM
int linhasMatriz2, colunasMatriz2; //dimensoes da matrizUM
long long int tamMatriz1; //qtde de elementos na matrizUM
long long int tamMatriz2; //qtde de elementos na matrizUM
long long int tamSaida; //qtde de elementos na matrizUM
FILE * matriz1; //descritor do arquivo de entrada
FILE * matriz2; //descritor do arquivo de entrada
size_t retMatriz1; //retorno da funcao de leitura no arquivo de entrada
size_t retMatriz2; //retorno da funcao de leitura no arquivo de entrada


void *calculaMatrix(void * arg) {
  long int id = (long int) arg;
  //imprime a matrizUM na saida padrao
  for (int i = id; i < linhasMatriz1; i += nthreads) {
    for (int j = 0; j < colunasMatriz2; j++) {
      for (int k = 0; k < linhasMatriz2; k++) {
        matrizSAIDA[i * colunasMatriz1 + j] += matrizUM[i * colunasMatriz1 + k] * matrizDOIS[k * colunasMatriz1 + j];
      }
    }
  }
  pthread_exit((void *)matrizSAIDA);
}

int main(int argc, char * argv[]) {

  pthread_t *tid;

  double inicio, fim, delta;
  int *retorno;

  FILE * descritorArquivo; //descritor do arquivo de saida
  size_t ret; //retorno da funcao de escrita no arquivo de saida

  //recebe os argumentos de entrada
  if (argc < 5) {
    fprintf(stderr, "Digite: %s <o primeiro arquivo entrada> <o segundo arquivo entrada> <arquivo de saida> <número de threads>\n", argv[0]);
    return 1;
  }
  GET_TIME(inicio);
  //abre o arquivo para leitura binaria
  matriz1 = fopen(argv[1], "rb");
  if (!matriz1) {
    fprintf(stderr, "Erro de abertura do arquivo 1\n");
    return 2;
  }

  //abre o arquivo para leitura binaria
  matriz2 = fopen(argv[2], "rb");
  if (!matriz2) {
    fprintf(stderr, "Erro de abertura do arquivo 2\n");
    return 2;
  }

  nthreads = atoi(argv[4]);
  if (!nthreads) {
    fprintf(stderr, "Erro na leitura dos números de threads\n");
    return 2;
  }

  GET_TIME(fim);
  delta = fim - inicio;
  printf("\nTempo de leitura dos arquivos binários: %lf\n", delta);

  GET_TIME(inicio);
  //le as dimensoes da matrizUM
  retMatriz1 = fread( & linhasMatriz1, sizeof(int), 1, matriz1);
  if (!retMatriz1) {
    fprintf(stderr, "Erro de leitura das dimensoes da matrizUM arquivo \n");
    return 3;
  }
  retMatriz1 = fread( & colunasMatriz1, sizeof(int), 1, matriz1);
  if (!retMatriz1) {
    fprintf(stderr, "Erro de leitura das dimensoes da matrizUM arquivo \n");
    return 3;
  }
  //le as dimensoes da matrizUM
  retMatriz2 = fread( & linhasMatriz2, sizeof(int), 1, matriz2);
  if (!retMatriz2) {
    fprintf(stderr, "Erro de leitura das dimensoes da matrizUM arquivo \n");
    return 3;
  }
  retMatriz2 = fread( & colunasMatriz2, sizeof(int), 1, matriz2);
  if (!retMatriz2) {
    fprintf(stderr, "Erro de leitura das dimensoes da matrizUM arquivo \n");
    return 3;
  }
  tamMatriz1 = linhasMatriz1 * colunasMatriz1; //calcula a qtde de elementos da matrizUM
  tamMatriz2 = linhasMatriz2 * colunasMatriz2; //calcula a qtde de elementos da matrizUM
  tamSaida = linhasMatriz2 * colunasMatriz1; //calcula a qtde de elementos da matrizUM

  //aloca memoria para a matrizUM
  matrizUM = (float * ) malloc(sizeof(float) * tamMatriz1);
  if (!matrizUM) {
    fprintf(stderr, "Erro de alocao da memoria da matrizUM\n");
    return 3;
  }
  matrizDOIS = (float * ) malloc(sizeof(float) * tamMatriz2);
  if (!matrizDOIS) {
    fprintf(stderr, "Erro de alocao da memoria da matrizDOIS\n");
    return 3;
  }
  matrizSAIDA = (float * ) malloc(sizeof(float) * tamSaida);
  if (!matrizSAIDA) {
    fprintf(stderr, "Erro de alocao da memoria da matrizDOIS\n");
    return 3;
  }

  //carrega a matrizUM de elementos do tipo float do arquivo
  retMatriz1 = fread(matrizUM, sizeof(float), tamMatriz1, matriz1);
  if (retMatriz1 < tamMatriz1) {
    fprintf(stderr, "Erro de leitura dos elementos da matrizUM\n");
    return 4;
  }

  //carrega a matrizUM de elementos do tipo float do arquivo
  retMatriz2 = fread(matrizDOIS, sizeof(float), tamMatriz2, matriz2);
  if (retMatriz2 < tamMatriz2) {
    fprintf(stderr, "Erro de leitura dos elementos da matrizUM\n");
    return 4;
  }

  GET_TIME(fim);
  delta = fim - inicio;
  printf("\nTempo de alocação de memória: %lf\n", delta);

  GET_TIME(inicio);

  tid = (pthread_t *) malloc(sizeof(pthread_t) *nthreads);

  //criar as threads
  for(long int i=0;i<nthreads;i++){
      if(pthread_create(tid+i, NULL, calculaMatrix, (void*) i)){
          fprintf(stderr, "ERRO --- pthread_create\n");
          return 3;
      }
  }

      //aguardar o termino das threads
    for(long int i=0; i<nthreads; i++){
        if(pthread_join(*(tid+i), (void**) &retorno)){
            fprintf(stderr, "ERRO --- pthread_join\n");
            return 3;
        }
    }

  GET_TIME(fim);

  delta = fim - inicio;
  printf("\nTempo multiplicacao: %lf\n", delta);

  GET_TIME(inicio);
  //escreve a matriz no arquivo
  //abre o arquivo para escrita binaria
  descritorArquivo = fopen(argv[3], "wb");
  if (!descritorArquivo) {
    fprintf(stderr, "Erro de abertura do arquivo\n");
    return 3;
  }
  //escreve numero de linhas e de colunas
  ret = fwrite( & linhasMatriz2, sizeof(int), 1, descritorArquivo);
  //escreve os elementos da matriz
  ret = fwrite( & colunasMatriz2, sizeof(int), 1, descritorArquivo);
  ret = fwrite(matrizSAIDA, sizeof(float), tamSaida, descritorArquivo);
  if (ret < tamSaida) {
    fprintf(stderr, "Erro de escrita no  arquivo\n");
    return 4;
  } else {
    printf("\nArquivo escrito com sucesso\n");
  }
  GET_TIME(fim);
  delta = fim - inicio;
  printf("\nTempo de criação do arquivo de saída: %lf\n", delta);

  //finaliza o uso das variaveis
  fclose(matriz1);
  free(matrizUM);
  return 0;
}