# Trabalho de Computação Concorrente
**Uma implementação em C da regra de integração trapezoidal numérica**


---
## Rodando o projeto
````git
$ git clone https://github.com/AdeLuigi/computacao-concorrente.git
$ cd conceitos-basicos-reactjs/Trabalho1
$ gcc numerical_conc.c -o numerical -Wall -lpthread
````

**Neste momento o programa já deve estar pronto para rodar**
````git
$./numerical <numero-de-threads>
````

**A primeira pergunta é o número de subintervalos**
````git
Enter the no. of sub-intervals: 
````

**A segunda pergunta é o limite inicial**
````git
Enter the initial limit: 
````

**A última pergunta é o limite final**
````git
Enter the final limit: 
````
**Colocando os válores como entrada**
```
Enter the no. of sub-intervals: 2000000000

Enter the initial limit: 0

Enter the final limit: 12
```

**Obtivemos o resultado**
```
values are 0.000000 and 12.000000
values are 0.000000 and 12.000000
values are 0.000000 and 12.000000
values are 0.000000 and 12.000000

The integral is: 576.000000
Time = 7.657737s
```

## O que você verá implementado?
* Uso da biblioteca pthread para criação e manupulação das threads
---

## Para uma maior compreensão do código, iremos explica-lo separando por partes

**function**
Essa função é responsável por receber um valor e retornar o quadrado deste valor

**Variáveis Globais**
As variáveis globais são constituídas por:
```
pthread_mutex_t mutexsum;
double sum_conc = 0.0, h;
double sum_seq = 0.0;
float *arr;
int nthreads;
```
**Estrutura do Dado**
Criamos uma struck para armazenar a dimensão, o id e o X e Y do dado

struct parametros {
    long long int id;
    long long int dimensao;
    double x;
    double y;
};

**Entrando com os dados**
```
  printf("\nEnter the no. of sub-intervals and threads: ");
  scanf("%lld",&dim);
  printf("\nEnter the initial limit: ");
  scanf("%lf",&a1);
  printf("\nEnter the final limit: ");
  scanf("%lf",&b1);
```
**Alocação dos dados**
```
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
```
**Solução sequencial do problema**
```
start1 = clock();

   for(int i=0;i<dim;i++){
     x = a1+i*h;
     sum_seq=sum_seq+function(x);
   }
   integral_seq=(h/2)*(function(a1)+function(b1)+2*sum_seq);


 end1 = clock();
time1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
```
**Criação das threads**
```
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
```
**Calculo da integral numerica e liberação da memória alocada dinamicamente**
```
integral_conc=(h/2)*(function(a1)+function(b1)+2*sum_conc);


pthread_mutex_destroy(&mutexsum);

free(tid);
free(args);
free(arr);


end2 = clock();
time2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
```

**Saída do programa**
```
printf("\nThe Sequencial Integral is: %lf\n",integral_seq);
printf("\nThe Concorrency Integral is: %lf\n",integral_conc);


printf("\nTime_Seq = %lfs\n", time1);
printf("\nTime_Conc = %lfs\n", time2);
```