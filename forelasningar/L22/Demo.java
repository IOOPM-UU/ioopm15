public class Demo extends Thread {
    private final int id; 
    Demo(final int id) {
        this.id = id;
    }
    public void run() {
        for (int i = 0; i < 10; ++i) {
            System.out.println(this.id);
        }
    }
    public static void main(String[] args) {
        new Demo(1).start();
        new Demo(2).start();
        new Demo(3).start();
        new Demo(4).start();
    }
}
