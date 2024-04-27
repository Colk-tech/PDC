// Main.java
// MyThreadクラスのスレッドを起動する
public class Main {
    public static void main(String[] args) {

        MyThread t = new MyThread();

        t.start();

        for (int i = 0; i < 100; i++) {
            System.out.print("Ping! ");
        }
        System.out.println();

        try {
           t.join();
           System.out.println("Thread t joined.");
        } catch(InterruptedException e){
        }
    }
}
