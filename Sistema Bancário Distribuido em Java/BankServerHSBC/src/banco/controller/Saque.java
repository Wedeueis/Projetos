package banco.controller;

import banco.Request;
import banco.Response;
import banco.model.Conta;
import banco.model.ContaDAO;
import banco.model.DBManager;

public class Saque implements Acao{
    @Override
    public Response executa(Request req) throws Exception{
        Response resp = new Response();
        try{
           ContaDAO dao = new ContaDAO();
           Conta conta = dao.buscarConta(req.getConta_origem());
           if(conta.getSaldo()>=req.getValor()){
                conta.setSaldo(conta.getSaldo()-req.getValor());
                dao.alterarConta(conta);
                DBManager.registerTransaction(req);  
                resp.setStatus(0);
                resp.setContent(conta.getSaldo().toString());
           }else{
                resp.setStatus(1);
                resp.setContent("Solicitação de saque indefereida: "
                        + "\nsaldo insuficiente!");
           }          
        }catch(Exception e){
           e.printStackTrace();
           resp.setStatus(1);
           resp.setContent("Solicitação de saque cancelada: \nerro ao "
                   + "acessar banco de dados.");           
        }
        return resp;
    }
}
