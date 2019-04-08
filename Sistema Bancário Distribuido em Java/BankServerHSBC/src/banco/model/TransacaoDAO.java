package banco.model;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class TransacaoDAO {
    private Connection connection;
    public TransacaoDAO(){
        this.connection = DBManager.getConnection();
    }
    
    public void inserirTransacao(Transacao transacao){
       String sql = "INSERT INTO transacoes (type, conta_origem, conta_destino,"
                + "banco_origem, banco_destino, data, horario, valor) VALUES (?,?,?,?,?,?,?,?);";
        System.out.println("Registrando nova transação...");
        try{
          PreparedStatement stmt = connection.prepareStatement(sql);
          
          //seta valores
          stmt.setInt(1, transacao.getType());
          stmt.setInt(2, transacao.getConta_origem());
          stmt.setInt(3, transacao.getConta_destino());
          stmt.setInt(4, transacao.getBanco_origem());
          stmt.setInt(5, transacao.getBanco_destino());
          stmt.setDate(6, transacao.getData());
          stmt.setTime(7, transacao.getHorario());
          stmt.setDouble(8, transacao.getValor());
          
          //executa
          stmt.execute();
          stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }
    
    public Transacao buscarTransacao(Integer id){
        Transacao transacao = null;
        String sql = "SELECT * FROM transacoes WHERE id = ?;";
        System.out.println("Buscando transação...");
        
        try{
            PreparedStatement stmt = connection.prepareStatement(sql);
            stmt.setInt(1, id);
            ResultSet rs = stmt.executeQuery();
            
            if(rs.next()){
                transacao = new Transacao();
                transacao.setId(rs.getInt("id"));
                transacao.setType(rs.getInt("type"));
                transacao.setConta_origem(rs.getInt("conta_origem"));
                transacao.setConta_destino(rs.getInt("conta_destino"));
                transacao.setBanco_origem(rs.getInt("banco_origem"));
                transacao.setBanco_destino(rs.getInt("banco_destino"));
                transacao.setData(rs.getDate("data"));
                transacao.setHorario(rs.getTime("horario"));
                transacao.setValor(rs.getDouble("valor"));               
            }
            
            rs.close();
            stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
        return transacao;
    }
    
    public void alterarTransacao(Transacao transacao){
        String sql = "UPDATE transacoes SET type=?, conta_origem=?, conta_destino=?,"
             + "banco_origem=?, banco_destino=?, data=?, horario=?, valor=? WHERE id=?;";
        System.out.println("Atualizando transação...");
        try{
          PreparedStatement stmt = connection.prepareStatement(sql);
          
          //seta valores
          stmt.setInt(1, transacao.getType());
          stmt.setInt(2, transacao.getConta_origem());
          stmt.setInt(3, transacao.getConta_destino());
          stmt.setInt(4, transacao.getBanco_origem());
          stmt.setInt(5, transacao.getBanco_destino());
          stmt.setDate(6, transacao.getData());
          stmt.setTime(7, transacao.getHorario());
          stmt.setDouble(8, transacao.getValor());
          stmt.setInt(9, transacao.getId());
          
          //executa
          stmt.execute();
          stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }
    
    public void deletarTransacao(Transacao transacao){
        String sql = "DELETE FROM transacoes WHERE id=?;";
        System.out.println("Deletando transação...");
        try{
            PreparedStatement stmt = connection.prepareStatement(sql);
             //seta valores
            stmt.setInt(1, transacao.getId());
                     //executa
          stmt.execute();
          stmt.close();
            
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
    
    public List<Transacao> listarTransacoes(int conta){
        List<Transacao> transacoes = new ArrayList();
        System.out.println("Listando transações...");
        try{
            PreparedStatement stmt = connection.prepareStatement("select * from "
                    + "transacoes order by data;");
            ResultSet rs = stmt.executeQuery();
            while(rs.next()) {
                if( (rs.getInt("type")==0 && rs.getInt("conta_origem") == conta) ||
                    (rs.getInt("type")==1 && rs.getInt("conta_destino") == conta) ||
                    (rs.getInt("type")==2 && rs.getInt("conta_origem") == conta) ||
                    (rs.getInt("type")==3  && rs.getInt("conta_destino")== conta ) ||
                    (rs.getInt("type")==4 && rs.getInt("conta_origem")== conta )  ||
                    (rs.getInt("type")==5 && rs.getInt("conta_destino")== conta)  ) {
                    Transacao transacao = new Transacao();
                    transacao.setId(rs.getInt("id"));
                    transacao.setBanco_origem(rs.getInt("banco_origem"));
                    transacao.setBanco_destino(rs.getInt("banco_destino"));
                    transacao.setConta_origem(rs.getInt("conta_origem"));
                    transacao.setConta_destino(rs.getInt("conta_destino"));
                    transacao.setData(rs.getDate("data"));
                    transacao.setHorario(rs.getTime("horario"));
                    transacao.setType(rs.getInt("type"));
                    transacao.setValor(rs.getDouble("valor"));
                    transacoes.add(transacao);
                }
            }
            rs.close();
            stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
        return transacoes;
    }
}
