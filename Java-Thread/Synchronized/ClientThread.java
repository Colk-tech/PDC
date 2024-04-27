// ClientThread.java
// Accountに100万回1を足す。

public class ClientThread extends Thread {
    private Account acc;

    public void setAccount(Account a) {
        acc = a;
    }

    public Account getAccount() {
        return acc;
    }

    //スレッドとして実行する処理
    public void run() {
        for (int i = 0; i < 1000000; i++) {
            this.getAccount().Deposit(1);
	}
    }
}

