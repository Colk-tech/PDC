// リクエストを表すプログラムRequest.java
public class Request {
    private final String name; // Stringは変化しないものとしてfinalで定義

    public Request(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public String toString() {
        return "[ Request " + name + " ]";
    }
}
