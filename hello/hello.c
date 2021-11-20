#include <stdio.h>
#include <pthread.h>

#define numeroThreads 10

int vetor[numeroThreads]; // variável global que será acessada por cada thread

//Função que a thread irá executar
void * tarefa(void *arg){

    int identificadorThread = * (int *) arg;
    vetor[identificadorThread] = identificadorThread;

    printf("Olá, sou a thread nova %d\n", identificadorThread);
    pthread_exit(NULL); // Essa função é um retorno especial para funções concorrentes dentro da lib pthread.h, este NULL é o retorno mais genérico possível.
}


int main(void)
{
    pthread_t identificadorThread[numeroThreads];
    int identificadorLocalThread[numeroThreads];
 
    for (size_t i = 0; i < numeroThreads; i++)
    {
        identificadorLocalThread[i] = i;
        if(pthread_create(&identificadorThread[i], NULL, tarefa, (void *)&identificadorLocalThread[i])){//Função de criação de concorrência, essa função recebe 4 argumentos
            printf("Deu ruim em algo aqui");//verificação de erros
        } 
        /* sendo eles: 
        -> 1° Identificador da thread (passando como endereço &)
        -> 2° Atributos para a thread (neste caso usamos NULL, pois não queremos passar nada)
        -> 3° Função que a thread irá executar
        -> 4° Argumentos que a função vai receber
    */
    }
    
    for (size_t i = 0; i < numeroThreads; i++)
    {
        if(pthread_join(identificadorThread[i], NULL)){//usaremos essa função para esperar todas as threads terminarem e assim executar a thread principal, que é a main
            printf("Deu ruim em algo aqui");//verificação de erros
        } 
    }

    for (size_t i = 0; i < numeroThreads; i++)
    {
        printf("%d ",vetor[i]);//verificação de erros
    }

    printf("\nOlá, sou a thread principal\n");
    pthread_exit(NULL); //Precisamos chamar essa função para dar um exit na thread da main
    return 0;
}
