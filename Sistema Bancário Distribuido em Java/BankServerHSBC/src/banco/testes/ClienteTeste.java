package banco.testes;

import java.rmi.Naming;
import banco.IService;

public class ClienteTeste {
    public static void main(String args[]){
        try{
            String location = "rmi://127.0.0.1:" + 8001 + "/Login";
            IService login = (IService) Naming.lookup(location);
            login.logar(1, 1);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
    
}
