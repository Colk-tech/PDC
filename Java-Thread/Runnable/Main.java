// Main.java
// Threadクラスではないクラスのインスタンスを生成、
// Threadクラスを利用して起動
public class Main {
    public static void main(String[] args) {

	Runnable printer1 = new Printer("Ping! ");
	Runnable printer2 = new Printer("Pong.. ");

	Thread thread1= new Thread( printer1 );
        Thread thread2= new Thread( printer2 );

	thread1.start();
        thread2.start();

	try {
	   thread1.join();
	   System.out.println("Thread1 joined.");
	   thread2.join();
	   System.out.println("Thread2 joined.");
        } catch(InterruptedException e){
        }
    }
}
