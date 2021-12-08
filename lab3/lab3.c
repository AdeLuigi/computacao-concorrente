

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"
#include<time.h>

long long int dimensao;
int nthreads; 
float *vetor; 
int limite1; 
int limite2;

void * tarefa(void * arg){
    long int id = (long int) arg;
    long int *count = 0;
    long int tamBloco = dimensao/nthreads;
    long int final;
    long int ini = id * tamBloco;

    count = (long int*) malloc(sizeof(long int));
    final = dimensao;
    for(long int i=ini; i<final;i++){
        if(limite1<vetor[i] && vetor[i]<limite2){
            (*count)++;
        }
    }
    pthread_exit((void *)count);
}

//fluxo principal
int main(int argc, char *argv[]){
    double ini, fim; 
    pthread_t *tid;
    int *retorno;
    srand((unsigned)time(NULL));
    int sequencial = 0;

    //recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
    if(argc<5){
        fprintf(stderr, "Digite: %s <dimensao do vetor> <limite1> <limite2> <numero de threads>\n", argv[0]);
        return 1;
    }
    dimensao = atoll(argv[1]);
    limite1 = atoi(argv[2]);
    limite2 = atoi(argv[3]);
    nthreads = atoi(argv[4]);

    //aloca o vetor de entrada
    vetor = (float*) malloc(sizeof(float)*dimensao);
    if(vetor == NULL){
        fprintf(stderr, "ERRO --- malloc(vetor)\n");
        return 2;
    }
    //iniizacao do vetor
    for(int i=0;i<dimensao;i++){
        vetor[i] = (rand()%1001 + (rand()%1000)/1000.0);
    }    

    //busca sequencial dos elementos
    GET_TIME(ini);
    for(int i=0; i<dimensao; i++){
        if(limite1<vetor[i] && vetor[i]<limite2){
            sequencial++;
        }
    }
    GET_TIME(fim);
    printf("tempo sequencial: %lf\n", fim-ini);

    GET_TIME(ini);
    //aloca
    tid = (pthread_t *) malloc(sizeof(pthread_t) *nthreads);

     //criar as threads
    for(long int i=0;i<nthreads;i++){
        if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
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
    printf("tempo concorrente: %lf\n", fim-ini);
    free(vetor);
    free(tid);
    return 0;
}

