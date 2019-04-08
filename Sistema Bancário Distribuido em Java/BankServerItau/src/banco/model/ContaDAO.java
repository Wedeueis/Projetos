package banco.model;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class ContaDAO {
    private Connection connection;

    public ContaDAO(){
        this.connection = DBManager.getConnection();
    }

    public void inserirConta(Conta conta){
        String sql = "INSERT INTO contas (cliente, senha, saldo,"
                + "cpf, data_nascimento) VALUES (?,?,?,?,?);";
        System.out.println("Inserindo nova conta no banco...");
        try{
          PreparedStatement stmt = connection.prepareStatement(sql);

          //seta valores
          stmt.setString(1, conta.getCliente());
          stmt.setInt(2, conta.getSenha());
          stmt.setDouble(3, conta.getSaldo());
          stmt.setString(4, conta.getCpf());
          stmt.setDate(5, conta.getDataDeNascimento());

          //executa
          stmt.execute();
          stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }

    public Conta buscarConta(Integer numero){
        Conta conta = null;
        String sql = "SELECT * FROM contas WHERE numero = ?;";
        System.out.println("Buscando conta...");
        try{
            PreparedStatement stmt = connection.prepareStatement(sql);
            stmt.setInt(1, numero);
            ResultSet rs = stmt.executeQuery();

            if(rs.next()){
                conta = new Conta();
                conta.setNumero(rs.getInt("numero"));
                conta.setCliente(rs.getString("cliente"));
                conta.setSenha(rs.getInt("senha"));
                conta.setSaldo(rs.getDouble("saldo"));
                conta.setCpf(rs.getString("cpf"));
                conta.setDataDeNascimento(rs.getDate("data_nascimento"));
            }

            rs.close();
            stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
        return conta;
    }

    public Conta buscarConta(String cpf){
        Conta conta = null;
        String sql = "SELECT * FROM contas WHERE cpf = ?;";
        System.out.println("Buscando conta...");
        try{
            PreparedStatement stmt = connection.prepareStatement(sql);
            stmt.setString(1, cpf);
            ResultSet rs = stmt.executeQuery();

            if(rs.next()){
                conta = new Conta();
                conta.setNumero(rs.getInt("numero"));
                conta.setCliente(rs.getString("cliente"));
                conta.setSenha(rs.getInt("senha"));
                conta.setSaldo(rs.getDouble("saldo"));
                conta.setCpf(rs.getString("cpf"));
                conta.setDataDeNascimento(rs.getDate("data_nascimento"));
            }

            rs.close();
            stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
        return conta;
    }

    public void alterarConta(Conta conta){
        String sql = "update contas set cliente=?, senha=?, saldo=?, cpf=?, "
                + "data_nascimento=? where numero=?;";
        System.out.println("Alterando conta...");
        try{
            PreparedStatement stmt = connection.prepareStatement(sql);
            stmt.setString(1, conta.getCliente());
            stmt.setInt(2, conta.getSenha());
            stmt.setDouble(3, conta.getSaldo());
            stmt.setString(4, conta.getCpf());
            stmt.setDate(5, conta.getDataDeNascimento());
            stmt.setInt(6,conta.getNumero());

            stmt.execute();
            stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }

    public List<Conta> listarContas(){
        List<Conta> contas = new ArrayList();
        System.out.println("Listando contas...");
        try{
            PreparedStatement stmt = connection.prepareStatement("select * from "
                    + "contas order by numero");
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                Conta conta = new Conta();
                conta.setNumero(rs.getInt("numero"));
                conta.setCliente(rs.getString("cliente"));
                conta.setSenha(rs.getInt("senha"));
                conta.setSaldo(rs.getDouble("saldo"));
                conta.setCpf(rs.getString("cpf"));
                conta.setDataDeNascimento(rs.getDate("data_nascimento"));
                contas.add(conta);
            }
            rs.close();
            stmt.close();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
        return contas;
    }
}
