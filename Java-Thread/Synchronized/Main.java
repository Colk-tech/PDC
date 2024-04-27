// Main.java
// 加算するスレッドを2つ生成する。
public class Main {
    public static void main(String[] args) {
        Account acc = new Account();

	ClientThread c1= new ClientThread();
	ClientThread c2= new ClientThread();

	c1.setAccount(acc);
        c2.setAccount(acc);

	c1.start();
        c2.start();


	try {
		c1.join();
		c2.join();
	} catch(InterruptedException e){
	}
	acc.showBalance();
    }
}
