// Read Write LockのメインプログラムMain.java
public class Main {
    public static void main(String[] args) {
        Data data = new Data(10);

        new ReaderThread(data).start();  // ReaderThreadを6つ作る
        new ReaderThread(data).start();
        new ReaderThread(data).start();
        new ReaderThread(data).start();
        new ReaderThread(data).start();
        new ReaderThread(data).start();

        new WriterThread(data, "ABCDEFGHIJKLMNOPQTSTUVWXYZ").start();
        new WriterThread(data, "abcdefghijklmnopqrstuvwxyz").start();
    }
}
