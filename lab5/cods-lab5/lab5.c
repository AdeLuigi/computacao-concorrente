#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int minhaVez = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
#define NTHREADS  4


void *volteSempre(){
    pthread_mutex_lock(&x_mutex);
    while (minhaVez < 3)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    minhaVez++;
    printf("volte sempre");
    printf("\n");
    pthread_mutex_unlock(&x_mutex); 



    pthread_exit(NULL);
}

void *fiqueAVontade(){
    pthread_mutex_lock(&x_mutex);
    while (minhaVez < 1)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    minhaVez++;
    printf("fique a vontade");
    printf("\n");
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex); 

    pthread_exit(NULL);

}

void *sentesePorFavor(){
    pthread_mutex_lock(&x_mutex);
    while (minhaVez < 1)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    minhaVez++;
    printf("sente-se, por favor");
    printf("\n");
    pthread_cond_broadcast(&x_cond);

    pthread_mutex_unlock(&x_mutex); 
    
    pthread_exit(NULL);

    
}

void *sejaBemVindo(){
    pthread_mutex_lock(&x_mutex);
    minhaVez++;
    printf("seja bem vindo");
    printf("\n");
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
    
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&x_mutex,NULL);
    pthread_cond_init(&x_cond,NULL);
    pthread_t threads[NTHREADS];

    pthread_create(&threads[0],NULL,*volteSempre,NULL);
    pthread_create(&threads[1],NULL,*fiqueAVontade,NULL);
    pthread_create(&threads[2],NULL,*sentesePorFavor,NULL);
    pthread_create(&threads[3],NULL,*sejaBemVindo,NULL);
    
    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
        printf("\n%d",minhaVez);


    return 0;
}
