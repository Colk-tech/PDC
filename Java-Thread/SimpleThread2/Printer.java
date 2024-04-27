// Printer.java
// スレッドとして実行されるクラス
// Threadクラスのサブクラスとして生成
// 引数として文字列を受け取る
public class Printer extends Thread {

    private String message;

    public Printer(String message) {
        this.message = message;
    }

    public void run() {
        for (int i = 0; i < 100; i++) {
            System.out.print(message);
        }
        System.out.println();
    }
}
