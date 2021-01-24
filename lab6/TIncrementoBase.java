/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 6 */
/* Codigo: Acessando variável compartilhada em um programa multithreading Java */
/* -------------------------------------------------------------------*/

import java.util.Arrays;

//classe da estrutura de dados (recurso) compartilhado entre as threads
class S {
  //recurso compartilhado
  private int r;
    private int a[];
    private int b[];
    private int c[];
  //construtor
  public S() { 
     this.r = 0;
      this.a = new int[]{10, 20, 30, 40, 50, 60};
      this.b = new int[]{10, 20, 30, 40, 50, 60};
      this.c = new int[6];
  }

  //operacao de escrita sobre o recurso compartilhado
  public void inc(int id) {

      int i = 0;
      while (i< this.a.length-3){
          if (id == 0){
              this.c[i] = this.a[i]+this.b[i];
          }else{
              this.c[i+3] = this.a[i+3]+this.b[i+3];
          }
          i++;
      }
  }
  //operacao de leitura sobre o recurso compartilhado
  public String get() {
      int[] x = this.c;
     return Arrays.toString(x);
  }

    // ou...

  /*public synchronized void inc() {
     this.r++; 
  }

  public synchronized int get() { 
      return this.r; 
  }*/
  
}

//classe que estende Thread e implementa a tarefa de cada thread do programa 
class T extends Thread {

    //identificador da thread
   private int id;
   //objeto compartilhado com outras threads
   S s;
  
   //construtor
   public T(int tid, S s) {
      this.id = tid;
      this.s = s;
   }

   //metodo main da thread
   public void run() {
      System.out.println("Thread " + this.id + " iniciou!");

         this.s.inc(this.id);

      System.out.println("Thread " + this.id + " terminou!"); 
   }
}

//classe da aplicacao
class TIncrementoBase {
   static final int N = 2;

   public static void main (String[] args) {
      //reserva espaço para um vetor de threads
      Thread[] threads = new Thread[N];
       int[] array1 = {10, 20, 30, 40, 50, 60};
       int[] array2 = {10, 20, 30, 40, 50, 60};

      //cria uma instancia do recurso compartilhado entre as threads
      S s = new S();
      //cria as threads da aplicacao
      for (int i=0; i<threads.length; i++) {
         threads[i] = new T(i, s);
      }

      //inicia as threads
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //espera pelo termino de todas as threads
      for (int i=0; i<threads.length; i++) {
         try { threads[i].join(); } catch (InterruptedException e) { return; }
      }

      System.out.println("Valor de s = " + s.get());
   }
}
