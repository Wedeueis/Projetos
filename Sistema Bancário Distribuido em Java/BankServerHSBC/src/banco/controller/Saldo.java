package banco.controller;

import banco.model.Conta;
import banco.model.ContaDAO;
import banco.Request;
import banco.Response;

public class Saldo implements Acao{
     @Override
     public Response executa(Request req) throws Exception{
         Response resp = new Response();
         try{
            ContaDAO dao = new ContaDAO();
            int numConta = req.getConta_origem();
            Conta conta = dao.buscarConta(numConta);
            Double saldo = conta.getSaldo();
            resp.setStatus(0);
            resp.setContent(saldo.toString());
         }catch(Exception e){
            e.printStackTrace();
            resp.setStatus(1);
            resp.setContent("Solicitação de saldo cancelada: erro ao acessar "
                    + "banco de dados.");           
         }
         return resp;
     }
}
