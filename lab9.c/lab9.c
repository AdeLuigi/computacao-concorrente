#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>
#define NTHREADS 5

/* Variaveis globais */
pthread_mutex_t x_mutex;
pthread_cond_t xx_cond, x_cond;
int controlT1 = 0;
int controlT2T3T4 = 0;
sem_t condt1, condt2;

void * T1(void * arg) {

   printf("Seja bem-vindo!\n");
    sem_post(&condt1); //permite que todas as outras executem

    pthread_exit(NULL);

}

void * T2(void * arg) {

    sem_wait(&condt1); // espera bem_vindo executar
    printf("Sente-se por favor.\n");

    controlT1++;

    if(controlT1==3){
        sem_post(&condt2);
    }

    sem_post(&condt1);
    
    pthread_exit(NULL);
}

void * T3(void * arg) {

    sem_wait(&condt1); // espera bem_vindo executar
    printf("Fique a vontade.\n");
    
    controlT1++;

    if(controlT1==3){
        sem_post(&condt2);
    }

    sem_post(&condt1); //permite que todas as outras executem
    
    pthread_exit(NULL);

}
void * T4(void * arg) {

    sem_wait(&condt1);
    printf("Aceita um copo d’agua?\n");

    controlT1++;
    if(controlT1==3){
        sem_post(&condt2);
    }

    sem_post(&condt1);
    
    pthread_exit(NULL);
}

void * T5(void * arg) {

    sem_wait(&condt2); // espera todas as outras executar

    printf("Volte sempre!\n");

  pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
   int i;
   pthread_t threads[NTHREADS];

   /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  sem_init(&condt1, 0, 0);
  sem_init(&condt2, 0, 0);

   /* Cria as threads */
   pthread_create( & threads[0], NULL, T5, NULL);
   pthread_create( & threads[1], NULL, T3, NULL);
   pthread_create( & threads[2], NULL, T2, NULL);
   pthread_create( & threads[4], NULL, T4, NULL);
   pthread_create( & threads[3], NULL, T1, NULL);

   /* Espera todas as threads completarem */
   for (i = 0; i < NTHREADS; i++) {
      pthread_join(threads[i], NULL);
   }

   /* Desaloca variaveis e termina */
    sem_destroy(&condt1);
    sem_destroy(&condt2);
   return 0;
}