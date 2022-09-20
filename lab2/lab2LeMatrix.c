/* Programa que le um arquivo binario com dois valores inteiros (indicando as dimensoes de uma matriz) 
 * e uma sequencia com os valores da matriz (em float)
 * Entrada: nome do arquivo de entrada
 * Saida: valores da matriz escritos no formato texto (com 6 casas decimais) na saida padrao 
 * */

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[]) {
   float *matriz; //matriz que será carregada do arquivo
   int linhasMatriz1, colunasMatriz1; //dimensoes da matriz
   int linhasMatriz2, colunasMatriz2; //dimensoes da matriz
   long long int tamMatriz1; //qtde de elementos na matriz
   long long int tamMatriz2; //qtde de elementos na matriz
   FILE * matriz1; //descritor do arquivo de entrada
   FILE * matriz2; //descritor do arquivo de entrada
   size_t retMatriz1; //retorno da funcao de leitura no arquivo de entrada
   size_t retMatriz2; //retorno da funcao de leitura no arquivo de entrada
   
   //recebe os argumentos de entrada
   if(argc < 4) {
      fprintf(stderr, "Digite: %s <o primeiro arquivo entrada> <o segundo arquivo entrada> <arquivo de saida>\n", argv[0]);
      return 1;
   }
   
   //abre o arquivo para leitura binaria
   matriz1 = fopen(argv[1], "rb");
   if(!matriz1) {
      fprintf(stderr, "Erro de abertura do arquivo 1\n");
      return 2;
   }
      //abre o arquivo para leitura binaria
   matriz2 = fopen(argv[2], "rb");
   if(!matriz2) {
      fprintf(stderr, "Erro de abertura do arquivo 2\n");
      return 2;
   }

   //le as dimensoes da matriz
   retMatriz1 = fread(&linhasMatriz1, sizeof(int), 1, matriz1);
   if(!retMatriz1) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   retMatriz1 = fread(&colunasMatriz1, sizeof(int), 1, matriz1);
   if(!retMatriz1) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
      //le as dimensoes da matriz
   retMatriz2 = fread(&linhasMatriz2, sizeof(int), 1, matriz2);
   if(!retMatriz2) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   retMatriz2 = fread(&colunasMatriz2, sizeof(int), 1, matriz2);
   if(!retMatriz2) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   tamMatriz1 = linhasMatriz1 * colunasMatriz1; //calcula a qtde de elementos da matriz
   tamMatriz2 = linhasMatriz2 * colunasMatriz2; //calcula a qtde de elementos da matriz

   //aloca memoria para a matriz
   matriz = (float*) malloc(sizeof(float) * tamMatriz1);
   matriz = (float*) malloc(sizeof(float) * tamMatriz1);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arquivo
   retMatriz1 = fread(matriz, sizeof(float), tamMatriz1, matriz1);
   if(retMatriz1 < tamMatriz1) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }

      //carrega a matriz de elementos do tipo float do arquivo
   retMatriz2 = fread(matriz, sizeof(float), tamMatriz1, matriz2);
   if(retMatriz2 < tamMatriz1) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }

   //imprime a matriz na saida padrao
   for(int i=0; i<linhasMatriz1; i++) { 
      for(int j=0; j<colunasMatriz1; j++)
        fprintf(stdout, "%.6f ", matriz[i*colunasMatriz1+j]);
      fprintf(stdout, "\n");
   }

   //finaliza o uso das variaveis
   fclose(matriz1);
   free(matriz);
   return 0;
}
