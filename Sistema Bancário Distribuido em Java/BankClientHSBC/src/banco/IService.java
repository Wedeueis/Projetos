package banco;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.sql.Date;

public interface IService extends Remote{
    public Integer cadastrar(String cliente, Integer senha, String cpf, 
        Date dataDeNascimento) throws RemoteException;
    public Boolean logar(Integer conta, Integer password) throws RemoteException;
    public Response processar(Request req) throws RemoteException;
}
