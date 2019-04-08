package banco;

import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class CentralBank {
    public static final int RMI_PORT = 8000;
    public static void main(String[] args) {
        try{
            //System.setProperty("java.rmi.server.hostname", "172.31.6.246");
            LocateRegistry.createRegistry(RMI_PORT);
            IBinder binder = new Binder();
            System.out.println("SERVER - Banco Central iniciado...");

            String location = "rmi://localhost:" + RMI_PORT + "/CentralBank";
            Naming.rebind(location, binder);

            System.out.println("SERVER - serviço cosultas registrado.");
        }
        catch(Exception ex){
            System.out.println("Erro no servidor do Banco Central");
            ex.printStackTrace();
        }
    }
    
}
