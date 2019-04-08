package banco.controller;

import banco.Bank;
import banco.BankServer;
import banco.IBinder;
import banco.IService;
import banco.Request;
import banco.Response;
import banco.model.Conta;
import banco.model.ContaDAO;
import banco.model.DBManager;
import java.rmi.Naming;

public class TEDCliente implements Acao {
    @Override
    public Response executa(Request req) throws Exception{
        Response resp = new Response();
        try{
            ContaDAO dao = new ContaDAO();
            Conta conta1 = dao.buscarConta(req.getConta_origem());
            if(conta1.getSaldo()>=req.getValor()){
                String centralBank = "rmi://"+BankServer.CENTRAL_BANK_ADRESS+
                        "/CentralBank";
                IBinder binder = (IBinder) Naming.lookup(centralBank);
                Bank bankDest = binder.consult(req.getBanco_destino());
                if(bankDest.getPort()!=-1){
                    String bankDestAdress = "rmi://"+ bankDest.getIp() +":"+ 
                            bankDest.getPort() + "/Service";
                    IService service = (IService)Naming.lookup(bankDestAdress);
                    req.setOperacao("TEDBanco");
                    Response tedResp = service.processar(req);
                    if(tedResp.getStatus() == 0){
                        conta1.setSaldo(conta1.getSaldo() - req.getValor());
                        dao.alterarConta(conta1);
                        req.setOperacao("TEDCliente");
                        DBManager.registerTransaction(req);         
                    }
                    return tedResp;
                }else{
                    resp.setStatus(1);
                    resp.setContent("Solicitação de envio de TED cancelada: "
                            + "\nfalha ao contatar banco de destino!");
                }
            }else{
                resp.setStatus(1);
                resp.setContent("Solicitação de envio de TED indeferida: \nsaldo "
                        + "insuficiente!");
            }          
        }catch(Exception e){
           e.printStackTrace();
           resp.setStatus(1);
           resp.setContent("Solicitação de envio de TED cancelada: \nerro ao "
                   + "acessar banco de dados.");           
        }
        return resp;
    }
}
