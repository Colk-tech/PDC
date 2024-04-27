// リクエストを保持しておくプログラムRequestQueue.java
import java.util.Queue;
import java.util.LinkedList;

public class RequestQueue {
    // 線形リストを利用してキューを定義
    private final Queue<Request> queue = new LinkedList<Request>();

    public synchronized Request getRequest() { // 排他的に処理
        while (queue.peek() == null) { // キューに何もなかったら何か入るのを待つ
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        return queue.remove(); // queueからRequestのインスタンスを1個取り出す
    }

    public synchronized void putRequest(Request req) { //排他的に処理
        queue.offer(req); // queueの最後にリクエストを1個追加する
        notifyAll(); // 待っているすべてのスレッドに通知する
    }
}
