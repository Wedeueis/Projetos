package banco.controller;

import banco.Request;
import banco.Response;
import banco.model.Transacao;
import banco.model.TransacaoDAO;
import java.util.Iterator;
import java.util.List;

public class Extrato implements Acao{
    @Override
    public Response executa(Request req) throws Exception{
        Response resp = new Response();
        try{
            TransacaoDAO dao = new TransacaoDAO();
            List<Transacao> transacoes = dao.listarTransacoes(req.getConta_origem());
            String extrato  = "Data            Descrição                    Tipo  Valor\n";
            for (Iterator<Transacao> i = transacoes.iterator(); i.hasNext();) {
                Transacao t = i.next();
                String linha = ""; 
                switch(t.getType()){
                    case 0:{
                        linha = t.getData() +"  Saque                            D     "+ t.getValor() + 
                                "\n";
                        break;
                    }case 1:{
                        linha = t.getData() +"  Depósito                        C     "+ t.getValor()+ 
                                "\n";
                        break;
                    }case 2:{
                        linha = t.getData() +"  Transferência enviada   D     "+ 
                                t.getValor() + "\n";
                        break;
                    }case 3:{
                        linha = t.getData() +"  Transferência recebida  C     "+ 
                                t.getValor() + "\n";
                        break;
                    }case 4:{
                        linha = t.getData() +"  Ted enviado                  D     "+ 
                                t.getValor() + "\n";
                        break;
                    }case 5:{
                        linha = t.getData() +"  Ted recebido                 C     "+ 
                                t.getValor() + "\n";
                        break;
                    }
                }
                extrato += linha;
            }
            resp.setStatus(0);
            resp.setContent(extrato);
        }catch(Exception e){
           e.printStackTrace();
           resp.setStatus(1);
           resp.setContent("Solicitação de extrato cancelada: erro ao "
                   + "acessar banco de dados.");  
        }
        return resp;
    }
}
