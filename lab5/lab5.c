#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#define NTHREADS 5

/* Variaveis globais */
pthread_mutex_t x_mutex;
pthread_cond_t xx_cond, x_cond;
int controlT1 = 0;
int controlT2T3T4 = 0;

void * T1(void * arg) {

   pthread_mutex_lock( & x_mutex);
   printf("Seja bem-vindo!\n");
   controlT2T3T4++; // para passar no if da T2 e T3
   pthread_cond_broadcast( & xx_cond); //libera T2 e T3
   pthread_mutex_unlock( & x_mutex);

   pthread_exit(NULL);
}

void * T2(void * arg) {

   pthread_mutex_lock( & x_mutex);
   if (controlT2T3T4 < 1) {
      pthread_cond_wait( & xx_cond, & x_mutex); // espera a T1 finalizar
   }
   printf("Sente-se por favor.\n");
   controlT1++; // para liberar a T5
   if (controlT1 == 3) {
      pthread_cond_signal( & x_cond);
   }
   pthread_mutex_unlock( & x_mutex);

   pthread_exit(NULL);
}

void * T3(void * arg) {

   pthread_mutex_lock( & x_mutex);
   if (controlT2T3T4 < 1) {
      pthread_cond_wait( & xx_cond, & x_mutex);
   }
   printf("Fique a vontade.\n");
   controlT1++; // para passar no if da T5
   if (controlT1 == 3) {
      pthread_cond_signal( & x_cond);
   }
   pthread_mutex_unlock( & x_mutex);

   pthread_exit(NULL);
}
void * T4(void * arg) {

   pthread_mutex_lock( & x_mutex);
   if (controlT2T3T4 < 1) {
      pthread_cond_wait( & xx_cond, & x_mutex); // espera a T1 finalizar
   }
   printf("Aceita um copo d’agua?\n");
   controlT1++; // para liberar a T5
   if (controlT1 == 3) {
      pthread_cond_signal( & x_cond);
   }
   pthread_mutex_unlock( & x_mutex);

   pthread_exit(NULL);
}

void * T5(void * arg) {

   pthread_mutex_lock( & x_mutex);
   if (controlT1 < 3) {
      pthread_cond_wait( & x_cond, & x_mutex); // espera a T2 e T3
   }
   pthread_mutex_unlock( & x_mutex);

   printf("Volte sempre!\n");
   pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
   int i;
   pthread_t threads[NTHREADS];

   /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
   pthread_mutex_init( & x_mutex, NULL);
   pthread_cond_init( & xx_cond, NULL);
   pthread_cond_init( & x_cond, NULL);

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
   pthread_mutex_destroy( & x_mutex);
   pthread_cond_destroy( & xx_cond);
   pthread_cond_destroy( & x_cond);
   return 0;
}