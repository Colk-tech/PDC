// Dataクラスを表すプログラムData.java
public class Data {
    private final char[] buffer;
    private final ReadWriteLock lock = new ReadWriteLock();

    public Data(int size) {
        this.buffer = new char[size];
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = '*';
        }
    }

    public char[] read() throws InterruptedException {// 読み出し with ロック操作
        lock.readLock();
        try {
            return doRead();
        } finally {
            lock.readUnlock();
        }
    }

    public void write(char c) throws InterruptedException { // 書き込み with ロック操作
        lock.writeLock();
        try {
            doWrite(c);
        } finally {
            lock.writeUnlock();
        }
    }

	// バッファの内容をコピって返す
    private char[] doRead() { // 読む処理
        char[] newbuf = new char[buffer.length];
        for (int i = 0; i < buffer.length; i++) {
            newbuf[i] = buffer[i];
        }
        slowly();
        return newbuf;
    }

	// バッファを文字cで埋め尽くす
    private void doWrite(char c) { // 書く処理
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = c;
            slowly();
        }
    }

    private void slowly() { // ゆっくり処理
        try {
            Thread.sleep(50);
        } catch (InterruptedException e) {
        }
    }
}
