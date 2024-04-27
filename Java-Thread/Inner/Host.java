// Host.java
// 匿名インナークラスを利用して、
// スレッドの上でhelperクラスを実行する。
public class Host {
    private final Helper helper = new Helper();

    public void request(final int count, final char c) {
        System.out.println("    request(" + count + ", " + c + ") BEGIN");
        Thread th=new Thread() { // スレッド生成
            public void run() {
                helper.handler(count, c);
            }
        };
        th.start(); // スレッドの起動
        System.out.println("    request(" + count + ", " + c + ") END");

        try {
          th.join();
        } catch(InterruptedException e){
        }
    }
}
