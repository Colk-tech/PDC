// Helper.java
// Helperクラス
// Hostクラスの下請け作業を担当。
// 文字列を指定された回数表示する。
public class Helper {

    public void handler(int count, char c) { // 指定した回数だけ文字列を表示する
        System.out.println("        handle(" + count + ", " + c + ") BEGIN");
        for (int i = 0; i < count; i++) {
            System.out.print(c);
		try {
		    Thread.sleep(100); // 100ミリ秒停止
		} catch (InterruptedException e) {
		}
        }

        System.out.println();
        System.out.println("        handle(" + count + ", " + c + ") END");
    }
}
