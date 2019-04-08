package banco;

import banco.controller.Controller;
import banco.model.DBManager;
import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class BankServer {
    public static final String NAME = "ITAÚ";
    public static final int NUMBER = 1;
    public static final String IP = "localhost";
    public static final String CENTRAL_BANK_ADRESS = "localhost:8000";
    
    
    public static void main(String args[]) {           
        try{         
            int port = registrar();
            //System.setProperty("java.rmi.server.hostname", "172.31.6.246");
            LocateRegistry.createRegistry(port);
            IService controller = new Controller();
            System.out.println("BANCO " + NAME);
            System.out.println("SERVER - servidor iniciado...");          
            String location = "rmi://127.0.0.1:" + port + "/Service";
            Naming.rebind(location, controller);           
            System.out.println("SERVER - verificando banco de dados...");
            DBManager.init();
            System.out.println("SERVER - provedor de serviços registrado.");
            System.out.println();
        }
        catch(Exception ex){
            System.out.println("SERVER - erro ao inicializar o servidor");
            ex.printStackTrace();
        }
    }
    
    private static int registrar(){
        try{        
            String location = "rmi://"+CENTRAL_BANK_ADRESS+"/CentralBank";
            IBinder binder = (IBinder) Naming.lookup(location);
            Bank bank = new Bank(NAME, NUMBER,-1,IP);
            return binder.registry(bank);           
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
}
