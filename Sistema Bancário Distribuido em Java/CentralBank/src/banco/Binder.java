package banco;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;


public class Binder extends UnicastRemoteObject implements IBinder{
    private Bank[] banks;
    private int registered;
    
    public Binder() throws RemoteException {
        super();
        banks = new Bank[10];
        for(int i=0; i<10; i++)
            banks[i] = null;
        registered = 0;
    }
    
    @Override
    public Bank consult(int number) throws RemoteException{
        try(PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ConsultLog.txt", true)))) {
            ZonedDateTime date = ZonedDateTime.now();
            out.println(DateTimeFormatter.ofPattern("dd/MM/yyyy - HH:mm").format(date) + 
                    " consulta ao banco número "+ number + ".");
        }catch (IOException e) {
            System.err.println(e);
        }
        if(number>10){
            return new Bank("", -1, -1, "");
        }else{
            return banks[number-1];
        }
    }
    
    @Override
    public int registry(Bank bank) throws RemoteException{
       if(banks[bank.getNumber()-1] == null){
           registered++;
           bank.setPort(8000+registered);
           banks[bank.getNumber()-1] = bank;
           System.out.println("Banco "+bank.getName()+" de número "+bank.getNumber()+
                   " registrado com sucesso no ip "+bank.getIp()+" e porta "+ bank.getPort()+".");
           return bank.getPort();
       }
       System.out.println("Banco "+bank.getName()+" de número "+bank.getNumber()+
                   " já registrado no ip "+bank.getIp()+" e porta "+ 
                   banks[bank.getNumber()-1].getPort()+".");
       return banks[bank.getNumber()-1].getPort();
    }
}
