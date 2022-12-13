#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>

#define BUFFERSIZE 10
#define P 2 //qtde de threads produtoras
#define C 2 //qtde de threads consumidoras

// Variaveis globais
sem_t mutexProd, mutexCons;//exclusao mutua
sem_t slotCheio, slotVazio;//condicao
int Buffer[BUFFERSIZE];

//inicializa o buffer
void IniciaBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    Buffer[i] = 0;
}

//imprime o buffer
void ImprimeBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    printf("%d ", Buffer[i]);
  printf("\n");
}

void Insere (int item, int id) {
    static int in=0;
    //exclusao mutua entre produtores
    sem_wait(&mutexProd);
		for (int i = 0; i < BUFFERSIZE; i++)
		{
			Buffer[i] = item;
		}
    in = 4;
    //
    printf("P[%d] inseriu\n", id);
    ImprimeBuffer(BUFFERSIZE);
    //
    sem_post(&mutexProd);
}

int Retira (int id) {
    int item;
    static int out=0;
    //exclusao mutua entre consumidores
    sem_wait(&mutexCons);
    item = Buffer[out];
  	Buffer[out] = 0;
    out = (out + 1) % BUFFERSIZE;
    //
    printf("C[%d] consumiu %d\n", id, item);
    ImprimeBuffer(BUFFERSIZE);
    //
    sem_post(&mutexCons);

    return item;
}

void *produtor(void * arg) {
    int elemento;
    int *id = (int *) arg;
    while(1) {
        //produz um elemento....
        elemento=1;
        Insere(elemento, *id);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumidor(void * arg) {
    int elemento;
    int *id = (int *) arg;
    while(1) {
        elemento = Retira(*id);
        //consome o elemento....
        sleep(1);
    }
    pthread_exit(NULL);
}

//funcao principal
int main(void) {
  //variaveis auxiliares
  int i;
 
  //identificadores das threads
  pthread_t tid[P+C];
  int *id[P+C];

  //aloca espaco para os IDs das threads
  for(i=0; i<P+C;i++) {
    id[i] = malloc(sizeof(int));
    if(id[i] == NULL) exit(-1);
    *id[i] = i+1;
  }

  //inicializa o Buffer
  IniciaBuffer(BUFFERSIZE);  

  //inicializa as variaveis de sinal
  sem_init(&mutexCons, 0, 1);
  sem_init(&mutexProd, 0, 1);

  //cria as threads produtoras
  for(i=0; i<P; i++) {
    if(pthread_create(&tid[i], NULL, produtor, (void *) id[i])) exit(-1);
  } 
  
  //cria as threads consumidoras
  for(i=0; i<C; i++) {
    if(pthread_create(&tid[i+P], NULL, consumidor, (void *) id[i+P])) exit(-1);
  } 

  pthread_exit(NULL);
  return 1;
}