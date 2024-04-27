// ServerThread.java
// RequestキューからRequestオブジェクトを取り出し、処理する。

import java.util.Random;

public class ServerThread extends Thread {
    private final Random random;
    private final RequestQueue requestQueue;

    // コンストラクタ
    public ServerThread(RequestQueue reqQ, String name, long seed) {
        super(name);
        this.requestQueue = reqQ;
        this.random = new Random(seed);
    }

    //スレッドとして実行する処理
    public void run() {
        for (int i = 0; i < 10000; i++) {
            Request req = requestQueue.getRequest();
            // スレッドの名前とリクエスト番号を表示する
            System.out.println( this.getName() + " handles  " + req);

            try {
                // リクエストの処理にかかる時間を乱数で変更する
                Thread.sleep(random.nextInt(1000));
            } catch (InterruptedException e) {
            }
        }
    }
}

