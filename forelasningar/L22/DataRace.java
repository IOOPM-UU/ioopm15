public class DataRace extends Thread {
    private final Cell c;
    public boolean done = false;
    DataRace(final Cell c) {
        this.c = c;
    }
    public void run() {
        for (int i = 0; i < 10000; ++i) {
            c.inc();
        }
        this.done = true;
    }
    public static void main(String[] args) {
        Cell c = new Cell();
        DataRace d1 = new DataRace(c); d1.start(); 
        DataRace d2 = new DataRace(c); d2.start();
        DataRace d3 = new DataRace(c); d3.start();
        DataRace d4 = new DataRace(c); d4.start();
        while (d1.done == false);
        while (d2.done == false);
        while (d3.done == false);
        while (d4.done == false);
        System.out.println(c.value);
    }
}

class Cell {
    int value = 0;
    public void inc() {
        this.value = this.value + 1;
    }
}
