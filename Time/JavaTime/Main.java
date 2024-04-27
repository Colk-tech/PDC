public class Main {
    public static void main(String[] args) {

	System.out.println("Main start:");
       	long start_time = System.currentTimeMillis();

        for (int i = 0; i < 10; i++) {
            System.out.print("Wow! "); // Wow!を出力
            try {
                Thread.sleep(10); // 一時停止:100ミリ秒
            } catch (InterruptedException e) {
            }
        }
	System.out.println();

       	long end_time = System.currentTimeMillis();

	// 実行時間の出力
      	System.out.println("elapsed time = " 
		+ (end_time - start_time) + "msec");
    }
}
