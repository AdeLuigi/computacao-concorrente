/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Comunicação entre threads usando variável compartilhada e sincronização com semáforos */

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <semaphore.h>

#include <unistd.h>

#define NTHREADS 2

// Variaveis globais
int x = 0; //variavel compartilhada entre as threads

// Variaveis globais
sem_t slotCheio, slotVazio; //condicao
sem_t mutexProd, mutexCons; //exclusao mutua
int Buffer[NTHREADS];

//funcao executada pela thread 2
void Insere(int item) {
  static int in = 0;
  //aguarda slot vazio
  sem_wait( & slotVazio);
  //exclusao mutua entre produtores
  sem_wait( & mutexProd);
  Buffer[in] = item;
  in = (in + 1) % NTHREADS;
  sem_post( & mutexProd);
  //sinaliza um slot cheio
  sem_post( & slotCheio);
}

//funcao executada pela thread 2
int Retira(void) {
  int item;
  static int out = 0;
  //aguarda slot cheio
  sem_wait( & slotCheio);
  //exclusao mutua entre consumidores
  sem_wait( & mutexCons);
  item = Buffer[out];
  out = (out + 1) % NTHREADS;
  sem_post( & mutexCons);
  //sinaliza um slot vazio
  sem_post( & slotVazio);
  return item;
}

//funcao executada pela thread 1
void * produtor(void * arg) {
	sleep(1);
  int elemento;
  while (1) {
    //produz um elemento....
    Insere(elemento);
		printf("insere");

  }
  pthread_exit(NULL);
}
void * consumidor(void * arg) {
	    sleep(1);
  int elemento;
  while (1) {
    elemento = Retira();
		printf("consumindo");
    //consome o elemento....
  }
  pthread_exit(NULL);
}

//funcao principal
int main(int argc, char * argv[]) {
  pthread_t tid[NTHREADS];
  int * id[2], t;

  for (t = 0; t < NTHREADS; t++) {
		Buffer[t] = 0;
    if ((id[t] = malloc(sizeof(int))) == NULL) {
      pthread_exit(NULL);
      return 1;
    }
    * id[t] = t + 1;
  }

  //inicia os semaforos
  sem_init( & mutexCons, 0, 1);
  sem_init( & mutexProd, 0, 1);
  sem_init( & slotCheio, 0, 0);
  sem_init( & slotVazio, 0, NTHREADS);

  //cria as tres threads
  if (pthread_create( & tid[1], NULL, consumidor, (void * ) id[1])) {
    printf("--ERRO: pthread_create()\n");
    exit(-1);
  }
  if (pthread_create( & tid[0], NULL, produtor, (void * ) id[0])) {
    printf("--ERRO: pthread_create()\n");
    exit(-1);
  }

  //--espera todas as threads terminarem
  for (t = 0; t < NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
      printf("--ERRO: pthread_join() \n");
      exit(-1);
    }
    free(id[t]);
  }
  pthread_exit(NULL);
}