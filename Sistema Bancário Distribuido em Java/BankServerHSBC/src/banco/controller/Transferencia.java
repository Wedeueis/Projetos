package banco.controller;

import banco.Request;
import banco.Response;
import banco.model.Conta;
import banco.model.ContaDAO;
import banco.model.DBManager;

public class Transferencia implements Acao{
    @Override
    public Response executa(Request req) throws Exception{
        Response resp = new Response();
        try{
           ContaDAO dao = new ContaDAO();
           Conta conta1 = dao.buscarConta(req.getConta_origem());
           if(conta1.getSaldo()>=req.getValor()){
                Conta conta2 = dao.buscarConta(req.getConta_destino());
                if(conta2!=null){
                    conta2.setSaldo(conta2.getSaldo()+req.getValor());
                    dao.alterarConta(conta2);
                    req.setOperacao("Transferencia Rec");
                    DBManager.registerTransaction(req); 
                    conta1.setSaldo(conta1.getSaldo()-req.getValor());
                    dao.alterarConta(conta1);
                    req.setOperacao("Transferencia Env");
                    DBManager.registerTransaction(req);         
                    resp.setStatus(0);
                    resp.setContent(req.getValor().toString());
                }else{
                    resp.setStatus(1);
                    resp.setContent("Solicitação de transferência cancelada: "
                            + "\nconta de destino não existe.");
                }
                
           }else{
                resp.setStatus(1);
                resp.setContent("Solicitação de transferência indeferida: "
                        + "\nsaldo insuficiente!");
           }          
        }catch(Exception e){
           e.printStackTrace();
           resp.setStatus(1);
           resp.setContent("Solicitação de transferência cacelada : "
                   + "\nerro ao acessar banco de dados.");           
        }
        return resp;
    }
}
