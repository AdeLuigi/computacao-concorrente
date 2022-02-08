/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Implementação e uso de sincronização por barreira */
// Aluno: Ademario Vitor

/***** Condicao logica da aplicacao: a cada iteracao, as threads fazem uma parte do processamento e só podem continuar depois que todas as threads completaram essa iteração. ****/

#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

#define NTHREADS 5
#define PASSOS 5

/* Variaveis globais */
int bloqueadas = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
int dimensao, * vetor; // dimensao passada pelo usuário e vetor

//funcao barreira
void barreira(int nthreads) {
  pthread_mutex_lock( & x_mutex); //inicio secao critica
  if (bloqueadas == (nthreads - 1)) {
    //ultima thread a chegar na barreira
    pthread_cond_broadcast( & x_cond);
    bloqueadas = 0;
  } else {
    bloqueadas++;
    pthread_cond_wait( & x_cond, & x_mutex);
  }
  pthread_mutex_unlock( & x_mutex); //fim secao critica
}

//funcao das threads
void * tarefa(void * arg) {
  int id = * (int * ) arg;
  long int somatorio = 0;

  for (int passo = 0; passo < dimensao; passo++) {

    for (int i = 0; i < dimensao; i++) {
      somatorio += * (vetor + i);
    }
    barreira(dimensao);

    vetor[id] = (rand() % 10);
    barreira(dimensao);

  }
  pthread_exit((void * ) somatorio);
}

/* Funcao principal */
int main(int argc, char * argv[]) {
  pthread_t threads[NTHREADS];
  int id[NTHREADS];
  long int somatorio;
  long int * resultado;

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init( & x_mutex, NULL);
  pthread_cond_init( & x_cond, NULL);

  if (argc < 2) {
    printf("Insira o %s a dimensao do vetor\n", argv[0]);
    exit(1);
  }

  dimensao = atoi(argv[1]);
  resultado = (long int * ) malloc(sizeof(long int) * dimensao);

  //alocaca memorias
  vetor = (int * ) malloc(sizeof(int) * dimensao);
  if (vetor == NULL) {
    printf("ERRO--malloc\n");
    return 2;
  }

  //inicia o vetor
  for (int i = 0; i < dimensao; i++) {
    *(vetor + i) = rand() % 10;
  }

  /* Cria as threads */
  for (int i = 0; i < NTHREADS; i++) {
    id[i] = i;
    pthread_create( & threads[i], NULL, tarefa, (void * ) & id[i]);
  }

  /* Espera todas as threads completarem */
  for (int i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], (void ** ) & somatorio);
    resultado[i] = somatorio;
  }

  //verifica se os retornos estão iguais 
  for (int i = 1; i < dimensao; i++) {
    if (resultado[i] != resultado[0]) {
      printf("ERRO-- resultados não são iguais\n");
      break;
    }
    if (i == (dimensao - 1))
      printf("Deu bom, resultados iguais, resultado = %ld\n", resultado[0]);
  }

  printf("FIM.\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy( & x_mutex);
  pthread_cond_destroy( & x_cond);
  return 0;
}