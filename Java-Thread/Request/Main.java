// Main.java
// クライアント役とサーバ役のスレッドを生成する。
public class Main {
    public static void main(String[] args) {
        RequestQueue requestQueue = new RequestQueue();

	ClientThread c1= new ClientThread(requestQueue, "Alice", 3141592L); // 数値は乱数の種
        ServerThread s1= new ServerThread(requestQueue, "Bobby", 6535897L);

	c1.start();
        s1.start();

	try {
		c1.join();
		s1.join();
	} catch(InterruptedException e){
	}
    }
}
