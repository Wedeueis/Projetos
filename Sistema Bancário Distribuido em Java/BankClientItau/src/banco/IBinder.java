package banco;

import java.rmi.Remote;
import java.rmi.RemoteException;


public interface IBinder extends Remote{
    public Bank consult(int number) throws RemoteException;
    public int registry(Bank bank) throws RemoteException;
}
