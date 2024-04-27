// ケーキを管理するテーブルを表すプログラムTable.java
public class Table {
    private final String[] buffer;
    private int tail;  // 次にputする場所
    private int head;  // 次にtakeする場所
    private int count; // buffer内のケーキ数

    public Table(int count) {
        this.buffer = new String[count];
        this.head = 0;
        this.tail = 0;
        this.count = 0;
    }

    // ケーキを置く：コックの操作
    public synchronized void put(String cake) throws
    InterruptedException {
	//空きがないと置けない
        while (count >= buffer.length) {
            wait();
        }
        buffer[tail] = cake;
        tail = (tail + 1) % buffer.length;
        count++;
        notifyAll();
        System.out.println(Thread.currentThread().getName() + " puts " + cake);
    }

    // ケーキを取る：客の操作
    public synchronized String take() throws InterruptedException {
	//ケーキがないと取れない
        while (count <= 0) {
            wait();
        }
        String cake = buffer[head];
        head = (head + 1) % buffer.length;
        count--;
        notifyAll();
        System.out.println(Thread.currentThread().getName() + " takes " + cake);
        return cake;
    }
}
