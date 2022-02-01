/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Aluno: Ademario Vitor */
/* Codigo: Leitores e escritores usando monitores em Java */
/* -------------------------------------------------------------------*/

class LE {
    private int leit, escr;
    private int var_compart;

    //Construtor
    LE() {
        this.leit = 0; //leitores lendo (0 ou mais)
        this.escr = 0; //escritor escrevendo (0 ou 1)
        this.var_compart = 0; //variável compartilhada
    }

    //Entrada para leitores
    public synchronized void EntraLeitor (int id) {
        try {
            while (this.escr > 0) {
                System.out.println ("LeitorBloqueado("+id+")");
                wait();  //bloqueia pela condição lógica da aplicação
            }
            this.leit++;  //registra que há mais um leitor presente
            if (this.var_compart%2==0){ //verifica par ou impar
                System.out.println ("LeitorLendo("+id+"); -|- par = " + this.var_compart);
            }else {
                System.out.println ("LeitorLendo("+id+"); -|- impar = " + this.var_compart);
            }

        } catch (InterruptedException e) { }
    }

    //Saída para leitores
    public synchronized void SaiLeitor (int id) {
        this.leit--; //registra que um leitor saiu
        if (this.leit == 0)
            this.notify(); //libera algum escritor (caso exista escritor bloqueado)
        System.out.println ("LeitorSaindo("+id+")");
    }

    //Entrada para escritores
    public synchronized void EntraEscritor (int id) {
        try {
            while ((this.leit > 0) || (this.escr > 0)) {
                System.out.println ("EscritorBloqueado("+id+")");
                wait();  //bloqueia pela condição lógica da aplicação
            }
            this.escr++; //registra que há um escritor escrevendo
            System.out.println ("EscritorEscrevendo("+id+")");
            this.var_compart++; // Acrecescenta ++ na variavel compartilhada

        } catch (InterruptedException e) { }
    }

    //Saída para escritores
    public synchronized void SaiEscritor (int id) {
        this.escr--; //registra que o escritor saiu
        notifyAll(); //libera leitores e escritores (caso existam leitores ou escritores bloqueados)
        System.out.println ("EscritorSaindo("+id+")");
    }
}

//Leitor
class Leitor extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    LE monitor;//objeto monitor

    //Construtor
    Leitor (int id, int delayTime, LE m) {
        this.id = id;
        this.delay = delayTime;
        this.monitor = m;
    }

    //Método executado pela thread
    public void run () {
        for (;;) {
            this.monitor.EntraLeitor(this.id);
            this.monitor.SaiLeitor(this.id);

            try {
                sleep(this.delay);
            } catch (InterruptedException e) {
            }
        }
    }
}

//Escritor
class Escritor extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads

    //Construtor
    Escritor (int id, int delayTime, LE m) {
        this.id = id;
        this.delay = delayTime;
        this.monitor = m;
    }

    //Método executado pela thread
    public void run () {
        while (true) {
            this.monitor.EntraEscritor(this.id);
            this.monitor.SaiEscritor(this.id);
            try{
                sleep(this.delay);
            } catch (InterruptedException e) {
            }
        }
    }
}

//Leitor/Escritor
class LeitorEscritor extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads

    //Construtor
    LeitorEscritor (int id, int delayTime, LE m) {
        this.id = id;
        this.delay = delayTime;
        this.monitor = m;
    }

    //Método executado pela thread
    public void run () {
        while (true){
            this.monitor.EntraLeitor(id);
            this.monitor.SaiLeitor(this.id);
            try{
                sleep(this.delay); //atraso bobo
            } catch (InterruptedException e) {
            }

            this.monitor.EntraEscritor(this.id);
            this.monitor.SaiEscritor(id);
            try {
                sleep(this.delay); //atraso bobo
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

//Classe principal
class lab8 {
    static final int L = 4;
    static final int E = 3;
    static final int LE = 1;

    public static void main (String[] args) {
        int i;
        LE monitor = new LE();            //Monitor (objeto compartilhado entre leitores e escritores)
        Leitor[] l = new Leitor[L];       //Threads leitoras
        Escritor[] e = new Escritor[E];   //Threads escritoras
        LeitorEscritor[] le = new LeitorEscritor[3]; //Threads leitoras/escritoras

        for (i=0; i<L; i++) {
            l[i] = new Leitor(i+1, (i+1)*500, monitor);
            l[i].start();
        }
        for (i=0; i<E; i++) {
            e[i] = new Escritor(i+1, (i+1)*500, monitor);
            e[i].start();
        }
        for (i=0; i<LE; i++) {
            le[i] = new LeitorEscritor(i+1, (i+1)*500, monitor);
            le[i].start();
        }
    }
}