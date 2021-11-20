#include <stdio.h>
#include <pthread.h>

//Função que a thread irá executar

void * tarefa(void *arg){
    printf("Olá, sou a\n");
    pthread_exit(NULL); // Essa função é um retorno especial para funções concorrentes dentro da lib pthread.h, este NULL é o retorno mais genérico possível.
}


int main(void)
{
    pthread_t identificadorThread;

    if(pthread_create(&identificadorThread, NULL, tarefa, NULL)){//Função de criação de concorrência, essa função recebe 4 argumentos
        printf("Deu ruim em algo aaqui");//verificação de erros
    } 
    /* sendo eles: 
        -> 1° Identificador da thread (passando como endereço &)
        -> 2° Atributos para a thread (neste caso usamos NULL, pois não queremos passar nada)
        -> 3° Função que a thread irá executar
        -> 4° Argumentos que a função vai receber
    
    */

    printf("Olá, sou a thread principal\n");
    pthread_exit(NULL); //Precisamos chamar essa função para dar um exit na thread da main
    return 0;
}
