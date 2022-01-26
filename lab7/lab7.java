/* Disciplina: Computacao Concorrente */
/* Aluno: Ademario Vitor Costa */
/* Laboratório: 7 */
/* -------------------------------------------------------------------*/

import java.util.ArrayList;
import java.util.Random;

//classe da estrutura de dados (recurso) compartilhado entre as threads
class S {
    //recurso compartilhado
    private int r;
    //construtor
    public S() {
        this.r = 0;
    }

    //operacao de escrita sobre o recurso compartilhado
  /*public void inc() {
     this.r++;
  }
  //operacao de leitura sobre o recurso compartilhado
  public int get() {
     return this.r;
  }*/

    // ou...

    public synchronized void inc() {
        this.r++;
    }

    public synchronized int get() {
        return this.r;
    }

}

//classe que estende Thread e implementa a tarefa de cada thread do programa
class T extends Thread {
    //identificador da thread
    private int id;
    private ArrayList<Integer>  vetor;
    private int somaTudo;
    private int Range;

    //objeto compartilhado com outras threads
    S s;

    //construtor
    public T(int tid, S s, ArrayList<Integer> vetor, int range) {
        this.id = tid;
        this.s = s;
        this.vetor = vetor;
        this.somaTudo = 0;
    }

    //metodo main da thread
    public void run() {
        //System.out.println("Thread " + this.id + " iniciou!");
        for (int i=0; i<100000; i++) {
            this.somaTudo += vetor.get(i);
        }
        //System.out.println("Thread " + this.id + " terminou!");
    }

    public int retornaSoma(){
        return somaTudo;
    }


}

//classe da aplicacao
class TIncrementoBase {
    static final int N = 2;
    static final int RANGE = 1000000;

    public static void main (String[] args) {
        //reserva espaço para um vetor de threads d
        Thread[] threads = new Thread[N];
        T[] objects = new T[N];
        ArrayList<Integer> vetor = new ArrayList<>(RANGE);
        Random rand = new Random();
        for (int i = 0 ; i < RANGE ; i++)
            vetor.add(rand.nextInt(99));
        //cria uma instancia do recurso compartilhado entre as threads
        S s = new S();

        //cria as threads da aplicacao
        for (int i=0; i<threads.length; i++) {
            objects[i] = new T(i, s, vetor, RANGE);
            threads[i] = new Thread(objects[i]);
        }

        //inicia as threads
        for (int i=0; i<threads.length; i++) {
            threads[i].start();
        }

        //espera pelo termino de todas as threads
        for (int i=0; i<threads.length; i++) {
            try { threads[i].join(); } catch (InterruptedException e) { return; }
        }

        System.out.println("Valor da soma = " + (objects[1].retornaSoma()+objects[0].retornaSoma()));
    }
}
