package banco.model;

import banco.Request;
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.Statement;
import java.sql.Time;
import java.util.Calendar;


public class DBManager {
    
    public static Connection getConnection(){
        System.out.println("Conectando com o banco de dados...");
        try {
            // db parameters
            String url = "jdbc:sqlite:Bank.db";
            // create a connection to the database
            return DriverManager.getConnection(url);
            
        } catch(Exception e){
            e.printStackTrace();
            throw new RuntimeException(e);
        }
      }
    
    public static void init(){
        createContasTable();
        createTransacaoTable();
    }
    
    public static void registerTransaction(Request req){
        TransacaoDAO tdao = new TransacaoDAO();
        Transacao t = new Transacao();
        if(req.getBanco_origem() != null){
            t.setBanco_origem(req.getBanco_origem());
        }
        if(req.getBanco_destino()!=null){
            t.setBanco_destino(req.getBanco_destino());
        }
        if(req.getConta_origem()!=null){
            t.setConta_origem(req.getConta_origem());
        }
        if(req.getConta_destino()!=null){
            t.setConta_destino(req.getConta_destino()); 
        }               
        t.setValor(req.getValor());
        Date date = new Date(Calendar.getInstance().getTime().getTime());
        Time horario = new Time(Calendar.getInstance().getTime().getTime());
        t.setData(date);
        t.setHorario(horario);
        switch(req.getOperacao()){
            case "Saque":{
                t.setType(0);
                break;
            }case "Deposito":{
                t.setType(1);
                break;
            }case "Transferencia Env":{
                t.setType(2);            
                break;
            }case "Transferencia Rec":{
                t.setType(3);              
                break;
            }case "TEDCliente":{
                t.setType(4);
                break;
            }case "TEDBanco":{
                t.setType(5);
                break;
            }             
        }
        tdao.inserirTransacao(t);
    }
    
    private static void createContasTable(){
        String sql = "CREATE TABLE IF NOT EXISTS contas (numero integer PRIMARY KEY," +
             "cliente text NOT NULL, senha integer NOT NULL, saldo double NOT NULL," +
             "cpf varchar(14) NOT NULL, data_nascimento data NOT NULL);";
        try{
            Connection conn = getConnection();
            Statement stmt = conn.createStatement();
            stmt.execute(sql);
            stmt.close();
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
    
    private static void createTransacaoTable(){
        String sql = "CREATE TABLE IF NOT EXISTS transacoes (id integer PRIMARY KEY," +
                      "type integer NOT NULL, conta_origem integer NOT NULL, "
                      + "conta_destino integer NOT NULL, banco_origem integer NOT NULL, "
                      + "banco_destino integer NOT NULL, data data NOT NULL,"
                      + "horario time NOT NULL, valor double NOT NULL);";
        try{
            Connection conn = getConnection();
            Statement stmt = conn.createStatement();
            stmt.execute(sql);
            stmt.close();
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
}
