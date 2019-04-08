package banco.testes;

import banco.model.DBManager;
import banco.model.Transacao;
import banco.model.TransacaoDAO;
import java.sql.Date;
import java.sql.Time;

public class TesteTransacaoDB {
    public static void main(String args[]){
        TransacaoDAO dao = new TransacaoDAO();
        DBManager.init();
        Transacao t1 = new Transacao();
        t1.setType(2);
        t1.setConta_origem(1);
        t1.setConta_destino(2);
        t1.setBanco_origem(341);
        t1.setBanco_destino(341);
        t1.setData(Date.valueOf("2017-07-29"));
        t1.setHorario(Time.valueOf("19:43:00"));     
        t1.setValor(1200.00);
        dao.inserirTransacao(t1);
        
        Transacao t2 = dao.buscarTransacao(1);
        System.out.println(t2.getId());
        System.out.println(t2.getConta_origem());
        System.out.println(t2.getConta_destino());
        System.out.println(t2.getBanco_origem());
        System.out.println(t2.getBanco_destino());
        System.out.println(t2.getData());
        System.out.println(t2.getHorario());
        System.out.println(t2.getValor());
        dao.deletarTransacao(t2);
        
        
    }

}
