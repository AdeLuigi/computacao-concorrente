#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include "timer.h"


float **mat1; //primeira matriz
float **mat2; //segunda matriz
float **mat_result; // matriz que armazenará o resultado da multiplicação
int nThreads; // numero de threads

struct parametros {
    int id;
    int dimensao;
};

void *multiplicador(void * myArg) {
    struct parametros *tArgs = (struct parametros *) myArg;
    printf("Thread %d\n", tArgs->id);
    double resultado;

    for(int i= tArgs->id; i < tArgs->dimensao; i+=nThreads){
        for(int j = tArgs->id; j< tArgs->dimensao; j +=nThreads){
            resultado = 0;
            for(int k = 0; k < tArgs->dimensao; k++)
                resultado = resultado + mat1[i][k]*mat2[k][j];

        mat_result[i][j] = resultado;  
        }
    }
    pthread_exit(NULL);
}


//fluxo principal

int main(int argc, char** argv) {
    for (int i = 0; i < 5; i++) {
    
    int dimensao; //dimensao das duas matrizes
    pthread_t *tid; //contabilização de threads do sistema
    struct parametros *args; //estrutura de dados com id e dimensao

    //calculo de tempo

    double inicio, fim, delta, total = 0;

    GET_TIME(inicio);

//usuário irá digitar o número de linha e colunas da matriz quadrada, além do número de threads
    if(argc < 3){
     {printf("Digite: %s <dimensao da matriz> <numero de threads>\n", argv[0]);
     return 1; 
    }
    }

    dimensao = atoi(argv[1]);
    nThreads = atoi(argv[2]);
    if(nThreads > dimensao) nThreads = dimensao;


    // alocação de memória nas linhas das matrizes
    mat1 = (float**)malloc(sizeof(float*) * dimensao);
    if(mat1 == NULL) {printf("ERRO--malloc"); return 2;}
    
    mat2 = (float**)malloc(sizeof(float*) * dimensao);
    if(mat2 == NULL) {printf("ERRO--malloc"); return 2;}

    mat_result = (float**)malloc(sizeof(float*) * dimensao);
    if(mat_result == NULL) {printf("ERRO--malloc"); return 2;}

    //alocação de memória nas colunas das matrizes
    for(int i = 0; i < dimensao; i++) {
        mat1[i] = (float*)malloc(sizeof(float) * dimensao);
        mat2[i] = (float*)malloc(sizeof(float) * dimensao);
        mat_result[i] = (float*)malloc(sizeof(float) * dimensao);

        //Checando alguma nullpointerexception após a alocação de memória
        if(mat1[i] == NULL) {printf("ERRO--malloc"); return 2;}
        if(mat2[i] == NULL) {printf("ERRO--malloc"); return 2;}
        if(mat_result[i] == NULL) {printf("ERRO--malloc"); return 2;}

    }
 

        

    //inicialização das estruturas de dados de entrada e saida
    for(int i = 0; i < dimensao; i++)
        for(int j = 0; j < dimensao; j++) {
            mat1[i][j] = 1;
            mat2[i][j] = 1;
            mat_result[i][j] = 0;
        }

    GET_TIME(fim);
    delta = fim - inicio;
    total +=delta;
    printf("Tempo inicialização: %lf\n", delta);

    
    //alocando estruturas2

    GET_TIME(inicio);

    tid =  (pthread_t*)malloc(sizeof(pthread_t) * nThreads);
    if(tid == NULL){printf("ERRO--malloc"); return 2;}
    args =  (struct parametros *)malloc(sizeof(struct parametros) * nThreads);
    if(args == NULL){printf("ERRO--malloc"); return 2;}


    //criacao das threads

    for(int i = 0; i < nThreads; i++) {
        (args + i)->id = i;
        (args+i)->dimensao = dimensao;
        if(pthread_create((tid+i), NULL, multiplicador, (void*) (args+i))) {
            puts("Erro -- pthread create");
            return 3;
        }
    }

    //espera pelo termino das threads

    for(int i = 0; i< nThreads; i++) {
        pthread_join(tid[i], NULL);
    }

    GET_TIME(fim);
    delta = fim - inicio;
    total +=delta;

    printf("Tempo Multiplicacao: %lf\n", delta);



    //exibição dos resultados
    GET_TIME(inicio);


    //  puts("Matriz de saída");
    // for(int i = 0; i < dimensao; i++) {
    //      for (int j = 0; j < dimensao; j++) {
    //         printf("%.1f ", mat_result[i][j]);
    //         printf(" ");
    //    }
    //      printf("\n");
    //   }


    //liberar memória

    for(int i =0; i < dimensao; i++) {
        free(mat1[i]);
        free(mat2[i]);
        free(mat_result[i]);
    }
        free(mat1);
        free(mat2);
        free(mat_result);


    GET_TIME(fim);
    delta = fim - inicio;
    total +=delta;

    printf("Tempo finalizacao: %lf\n", delta);
    printf("Tempo total %.3lf\n", total);

    }
    return 0;


    

}