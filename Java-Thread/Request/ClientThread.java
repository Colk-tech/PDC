// リクエストを出すプログラムClientThread.java
import java.util.Random;

public class ClientThread extends Thread {
    private final Random random;
    private final RequestQueue requestQueue;

    public ClientThread(RequestQueue reqQ, String name, long seed) {
        super(name);
        this.requestQueue = reqQ;
        this.random = new Random(seed);
    }

    public void run() {
        for (int i = 0; i < 10000; i++) {
            Request req = new Request("No." + i);
            // スレッドの名前とリクエスト番号を表示する
           System.out.println( this.getName() + " requests " + req);
            requestQueue.putRequest(req);

            try {
                Thread.sleep(random.nextInt(1000)); 
                // リクエストを出すタイミングを乱数で変更する
            } catch (InterruptedException e) {
            }
        }
    }
}
