// Account.java
// 口座オブジェクト

public class Account {
    private int balance;

    public  Account(){
	balance=0;
    }

    public void Deposit(int money) {
        balance += money;
    }

    public void showBalance() {
        System.out.println("Current Balance is " + balance);
    }
}
