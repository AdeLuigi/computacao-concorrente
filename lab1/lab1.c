/* Disciplina: Computacao Concorrente */
/* Nome.: Ademário Vitor*/
/* DRE 118143148 */
/* Laboratório: 1 */
/* Codigo: "Quadrado de cada um dos 10000 elementos de um array */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <stdbool.h>

#define NTHREADS  2 //total de threads a serem criadas

#define dezmil 10000

float vetor[dezmil]; // variável global que será acessada por cada thread
float vetorVerificacao[dezmil];

//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int idThread, nThreads;
} t_Args;

//funcao executada pelas threads
void *aumaDezPorcento (void *arg) {
  t_Args *args = (t_Args *) arg;

  /* Utilizei a seguinte lógica, a thread 0 ficará responsável por fazer os quadrados da posição 0 até a 4999 e a thread 1 vai fazer os quadrados da posição 5000 até 9999, completando assim os 10000 elementos */
  if(args->idThread == 0){
    for (size_t i = 0; i < 5000; i++)
    {
      vetor[i] = i*1.1;
      vetorVerificacao[i] = i;
    }
    
  }else{
    for (size_t i = 5000; i < 10000; i++)
    {
      vetor[i] = i*1.1;
      vetorVerificacao[i] = i;
    }
  }

  free(arg); //aqui pode liberar a alocacao feita na main

  pthread_exit(NULL);
}

bool fequal(float a, float b, float epsilon)
{
 return a-b < epsilon;
}

void verifica(){
  for (int i = 0; i < dezmil; i++)
  {
    if (!fequal(vetor[i], vetorVerificacao[i]*1.1, 0.00001 )){
    printf("\n calculo incorreto");
    return ;
    }
  }
  printf("\n calculo correto \n");
  return ;
}

//funcao principal do programa
int main() {
  pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
  int thread; //variavel auxiliar
  t_Args *arg; //receberá os argumentos para a thread

  for(thread=0; thread<NTHREADS; thread++) {
    arg = malloc(sizeof(t_Args));
    if (arg == NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
    }
    arg->idThread = thread; 
    arg->nThreads = NTHREADS; 
    
    // printf("--Cria a thread %d\n", thread);
    if (pthread_create(&tid_sistema[thread], NULL, aumaDezPorcento, (void*) arg)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  //--espera todas as threads terminarem
  for (thread=0; thread<NTHREADS; thread++) {
    if (pthread_join(tid_sistema[thread], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }

  // for (size_t i = 0; i < dezmil; i++)
  // {
  //   printf("%lf ",vetor[i]);//verificação de erros
  // }
  verifica();

  printf("--Thread principal terminou\n");
  pthread_exit(NULL);
}