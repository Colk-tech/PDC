// MyThread.java
// スレッドとして実行されるクラス
// Threadのサブクラスとして作成
public class MyThread extends Thread {
    public void run() {
        for (int i = 0; i < 100; i++) {
            System.out.print("Pong.. ");
        }
        System.out.println();
    }
}
