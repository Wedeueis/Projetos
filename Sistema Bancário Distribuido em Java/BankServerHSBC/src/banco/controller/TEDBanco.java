package banco.controller;

import banco.Request;
import banco.Response;
import banco.model.Conta;
import banco.model.ContaDAO;
import banco.model.DBManager;

public class TEDBanco implements Acao {
    @Override
    public Response executa(Request req) throws Exception{
        Response resp = new Response();
        try{
           ContaDAO dao = new ContaDAO();
           int numConta = req.getConta_destino();
           Conta conta = dao.buscarConta(numConta);
           conta.setSaldo(conta.getSaldo()+req.getValor());
           dao.alterarConta(conta);         
           DBManager.registerTransaction(req);          
           resp.setStatus(0);
        }catch(Exception e){
           e.printStackTrace();
           resp.setStatus(1);
           resp.setContent("Solicitação de recebimento de TED cancelada: "
                   + "\nerro ao acessar banco de dados.");           
        }
        return resp;
    }
}
