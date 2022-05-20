/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Comunicação entre threads usando variável compartilhada e exclusao mutua com bloqueio */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

#define NTHREADS 2

int s = 0; //variavel compartilhada entre as threads
pthread_mutex_t mutex; //variavel de lock para exclusao mutua

//funcao executada pelas threads
void * ExecutaTarefa(void * threadid) {
    int i, tid = * (int * ) threadid;
    printf("Thread : %d esta executando...\n", tid);
    for (i = 0; i < 1000000; i++) {
        //--entrada na SC
        pthread_mutex_lock( & mutex);
        //--SC
        s++; //incrementa o contador de tarefas realizadas 
        //--saida da SC
        pthread_mutex_unlock( & mutex);
    }
    printf("Thread : %d terminou!\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
    pthread_t tid[NTHREADS];
    int t, id[NTHREADS];
    double ini, fim;

    GET_TIME(ini);

    int * vetor;
    vetor = malloc(10 * sizeof(int));

    //--inicilaiza o mutex (lock de exclusao mutua)

    pthread_mutex_init( & mutex, NULL);

    for (t = 0; t < NTHREADS; t++) {
        id[t] = t;
        if (pthread_create( & tid[t], NULL, ExecutaTarefa, (void * ) & id[t])) {
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }
    //--espera todas as threads terminarem
    for (t = 0; t < NTHREADS; t++) {
        if (pthread_join(tid[t], NULL)) {
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }
    pthread_mutex_destroy( & mutex);

    GET_TIME(fim);

    printf("Valor de s = %d\n", s);
    printf("Tempo = %lf\n", fim - ini);
    pthread_exit(NULL);
}