/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Comunicação entre threads usando variável compartilhada e exclusao mutua com bloqueio */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
#include <math.h>

int * vetorEntradaGlobal;
float * vetorSaidaGlobalConcorrente;
float * vetorSaidaGlobalSequencial;


int s = 0; //variavel compartilhada entre as threads
pthread_mutex_t mutex; //variavel de lock para exclusao mutua

typedef struct {
    int threadId;
    int dim;
    int nthreads;
} t_objetoConcorrente;

int checaArrays(float vetorConcorrente[],float vetorSequencial[], int dim){
    for (int i = 0; i < dim; i++)
    {
        if(vetorConcorrente[i] != vetorSequencial[i]){
            return 0;
        }
    }
    return 1;  
}

int ehPrimo(long long int n) {
        if (n<=1){
            return 0;
        }   
        if (n==2){ 
            return 1;
        }
        if (n%2==0){ 
            return 0;
        }
        for (int i=3; i<sqrt(n)+1; i+=2){
            if(n%i==0){ 
                return 0;
            }
        }
    return 1;
}

void processaPrimosSequencial(int vetorEntrada[], int dim) {
    for(int i=0; i<dim; i++) {
        //printf("%d ", vetorEntrada[i]);
        if (ehPrimo(vetorEntrada[i])){
            vetorSaidaGlobalSequencial[i] = sqrt(vetorEntrada[i]);
        }else {
            vetorSaidaGlobalSequencial[i] = vetorEntrada[i];
        }
    }
}

//funcao executada pelas threads
void * processaPrimosConcorrente(void *dado) {

    t_objetoConcorrente *dados = (t_objetoConcorrente *) dado;
    for (int i = dados->threadId; i < dados->dim; i += dados->nthreads) {
        //--entrada na SC


            if (ehPrimo(vetorEntradaGlobal[i])){
                pthread_mutex_lock( & mutex);
                vetorSaidaGlobalConcorrente[i] = sqrt(vetorEntradaGlobal[i]);
                pthread_mutex_unlock( & mutex);
            }else {
                pthread_mutex_lock( & mutex);
                vetorSaidaGlobalConcorrente[i] = vetorEntradaGlobal[i];
                pthread_mutex_unlock( & mutex);
            }
        
    }

    pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
    int t, nthreads;
    long long int dim;
    double tempoInicioSequencial, tempoFinalSequencial;
    double tempoInicioConcorrente, tempoFinalConcorrente;
    t_objetoConcorrente *dados;

    GET_TIME(tempoInicioSequencial);

    if(argc<3) {
      printf("Digite: %s <dimensao do array> <numero de threads>\n", argv[0]);
      return 1;
    }

    dim = atoll(argv[1]);
    nthreads = atoi(argv[2]);

    pthread_t tid[nthreads];
    int id[nthreads];

    vetorEntradaGlobal = malloc(dim * sizeof(int));
    vetorSaidaGlobalSequencial = malloc(dim * sizeof(int));
    vetorSaidaGlobalConcorrente = malloc(dim * sizeof(int));

    srand ( time(NULL) );
    for (int index = 0; index < dim; index++)
    {
        vetorEntradaGlobal[index] = rand()%1000;
    }

    GET_TIME(tempoInicioSequencial);
    processaPrimosSequencial(vetorEntradaGlobal, dim );
    GET_TIME(tempoFinalSequencial);

    //--inicilaiza o mutex (lock de exclusao mutua)
    //pthread_mutex_init( & mutex, NULL);
    GET_TIME(tempoInicioConcorrente);
    for (t = 0; t < nthreads; t++) {
        dados = malloc(sizeof(t_objetoConcorrente));
        id[t] = t;

        dados->dim = dim;
        dados->threadId = id[t];
        dados->nthreads = nthreads;

        if (pthread_create( & tid[t], NULL, processaPrimosConcorrente, (void*) dados)) {
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }
    //--espera todas as threads terminarem
    for (t = 0; t < nthreads; t++) {
        if (pthread_join(tid[t], NULL)) {
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }
    GET_TIME(tempoFinalConcorrente);
    //pthread_mutex_destroy( & mutex);

    int vetoresSaoIguais = checaArrays(vetorSaidaGlobalConcorrente, vetorSaidaGlobalSequencial, dim);

    printf("Tempo sequencial = %lf\n", tempoFinalSequencial - tempoInicioSequencial);
    printf("Tempo concorrente = %lf\n", tempoFinalConcorrente - tempoInicioConcorrente);

    if (vetoresSaoIguais == 1)
    {
        printf("\n Os vetores são iguais");
    }else{
        printf("\n Os vetores são diferentes");
    }
    

    // for (int index = 0; index < dim; index++)
    // {
    //     printf("%d ", vetorEntradaGlobal[index]);
    // }
    // printf("\n");
    // for (int index = 0; index < dim; index++)
    // {
    //     printf("%f ", vetorSaidaGlobalSequencial[index]);
    // }

    // printf("\n");

    // for (int index = 0; index < dim; index++)
    // {
    //     printf("%f ", vetorSaidaGlobalConcorrente[index]);
    // }

    
    pthread_exit(NULL);
}