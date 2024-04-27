// Main.java
// Printerクラスのスレッドを2つ起動する
public class Main {
    public static void main(String[] args) {

	Thread printer1 = new Printer("Ping! ");
	Thread printer2 = new Printer("Pong.. ");

	printer1.start();
	printer2.start();

        try {
           printer1.join();
           System.out.println("Printer1 joined.");
           printer2.join();
           System.out.println("Printer2 joined.");
        } catch(InterruptedException e){
        }

    }
}
