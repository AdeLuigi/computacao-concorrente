/********************************************************************* 
Trab 1
aluno: Ademario Vitor
DRE 118143148
    
***********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>




 /*-----------------------------------------Global Variables-----------------------------------------------*/

pthread_mutex_t mutexsum;
double sum_conc = 0.0, h;
double sum_seq = 0.0;
float *arr;
int nthreads;


/* Define the function to be integrated here: */
#define function(x) (x*x)



/*---------------------------------------------Data Struct----------------------------------------------*/


struct parametros {
    int id;
    long long int dimensao;
    double x;
    double y;
};


/*---------------------------------------------Thread Function----------------------------------------------*/

void *calcularTrapezoidal(void * arg) {
    struct parametros *tArgs = (struct parametros *) arg;
    long long int tamBLoco = tArgs ->dimensao/nthreads; // tamanho do bloco de cada thread
    long long int ini = tArgs->id*tamBLoco; //Elemento inicial do bloco da thread
    long long int final;
    double tmp = 0.0;
    if(tArgs->id == nthreads-1) {
        final = tArgs->dimensao;
    }
    else{
        final = ini + tamBLoco;
    }
    
    //printf("\nTHREAD %d - INICIAL %lld\n",tArgs->id, ini);
    //printf("\nTHREAD %d - FINAL %lld\n",tArgs->id, final);
     
    for(long long int i = ini; i < final; i++) {

        
        tmp += function(arr[i]);
    }

    pthread_mutex_lock(&mutexsum);
        
        sum_conc += tmp;
        pthread_mutex_unlock(&mutexsum);

    pthread_exit(NULL);

  }

 
/*Program begins*/
int main(int argc, char** argv){
  struct parametros *args;
  pthread_t *tid;
  long long int dim;
  clock_t start1, end1, start2, end2;
  double  time2, time1;;
  double integral_conc, integral_seq ,a1,b1, x;

    if(argc < 2) {
        fprintf(stderr,"ERRO-Invalid number argument <Name> <nthreads>");
        return 3;
    }

    nthreads = atoi(argv[1]);
    



  /*Ask the user for necessary input */
  printf("\nEnter the no. of sub-intervals: ");
  scanf("%lld",&dim);
  printf("\nEnter the initial limit: ");
  scanf("%lf",&a1);
  printf("\nEnter the final limit: ");
  scanf("%lf",&b1);


  h = fabs(b1-a1)/dim;

/*--------------------------------------------Data Allocation------------------------------------------------*/
args =(struct parametros *) malloc(sizeof(struct parametros) *nthreads);
    if(args == NULL) {
        fprintf(stderr, "ERRO-malloc\n");
    return 2;
    }

tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if(tid == NULL) {
        fprintf(stderr, "ERRO--malloc\n");
    return 2;
}

arr = (float *) malloc(sizeof(float)*dim);
    if(arr == NULL) {
        fprintf(stderr, "ERRO-malloc\n");
}

for(int i = 0; i < dim; i++) {
        arr[i] = a1 + i*h;
    
    }

/*--------------------------------------------Sequential Solution--------------------------------------------*/
start1 = clock();

   for(int i=0;i<dim;i++){
     x = a1+i*h;
     sum_seq=sum_seq+function(x);
   }
   integral_seq=(h/2)*(function(a1)+function(b1)+2*sum_seq);


 end1 = clock();
time1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;



/*--------------------------------------------Concurrent Solution--------------------------------------------*/
start2 = clock();


      
      pthread_mutex_init(&mutexsum, NULL);


/*---------------------------------------Theads Creation-------------------------------------*/

for(long long int i = 0; i < nthreads; i++) {
    (args + i)->dimensao = dim;
    (args + i)->id = i;

    (args + i)->x = a1;
    (args + i)->y= b1;

    if(pthread_create((tid + i), NULL, calcularTrapezoidal, (void*)(args+i))) {
        fprintf(stderr, "ERRO--pthread_create\n");
        return 3;
    }
}

/*---------------------------------------Waiting for the threads--------------------------------*/
for(long long int i = 0; i < nthreads; i++) {
    if(pthread_join(*(tid + i), NULL)) {
        fprintf(stderr, "ERRO--pthread_join\n");
        return 3;
    }

}

/*---------------------------------------Calculate Numerical Integral--------------------------------*/

integral_conc=(h/2)*(function(a1)+function(b1)+2*sum_conc);


pthread_mutex_destroy(&mutexsum);

free(tid);
free(args);
free(arr);


end2 = clock();
time2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;


/*-------------------------------------------------Print the answer--------------------------------------- */
printf("\nThe Sequencial Integral is: %lf\n",integral_seq);
printf("\nThe Concorrency Integral is: %lf\n",integral_conc);


printf("\nTime_Seq = %lfs\n", time1);
printf("\nTime_Conc = %lfs\n", time2);

/*-------------------------------------------------Print performance Gain--------------------------------------- */

printf("\nThe Performance Gain Are: %lf*100\n",time1/time2);

return 0;

}