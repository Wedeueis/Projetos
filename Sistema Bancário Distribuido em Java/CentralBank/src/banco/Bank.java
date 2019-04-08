package banco;



public class Bank implements java.io.Serializable {
    private String name;
    private int number;
    private int port;
    private String ip;
    
    public Bank(String name, int number, int port, String ip){
        this.name = name;
        this.number = number;
        this.port = port;
        this.ip = ip;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }
}
