package banco.controller;

import banco.Request;
import banco.Response;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import banco.IService;
import java.sql.Date;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;


public class Controller extends UnicastRemoteObject implements IService {
    public Controller() throws RemoteException{
        super();
    }
    
    @Override
    public Response processar(Request req){
        String opcao = req.getOperacao();
        String nomeDaClasse = "banco.controller." + opcao;
        ZonedDateTime date = ZonedDateTime.now();
        System.out.println(DateTimeFormatter.ofPattern("dd/MM/yyyy - "
                + "HH:mm").format(date) + " - Iniciando operação: " + opcao);
        try {
            Class<?> classe = Class.forName(nomeDaClasse);
            Acao acao = (Acao) classe.newInstance();
            Response resp = acao.executa(req);
            System.out.println("Operação "+opcao+" encerrada.\n");           
            return resp;
        } catch (Exception e) {
            throw new RuntimeException("Erro: ",e);
        }
    }
    
    @Override
    public Boolean logar(Integer conta, Integer password) throws RemoteException {
        try{
            ZonedDateTime date = ZonedDateTime.now();
            System.out.println(DateTimeFormatter.ofPattern("dd/MM/yyyy - "
                + "HH:mm").format(date) + " - Iniciando solicitação de login");
            System.out.println("Autenticando usuário...");
            Login login = new Login();
            Boolean resp = login.executa(conta, password);
            System.out.println();
            return resp;
        }catch(Exception e){
            System.out.println("Erro no servidor de login.");
            e.printStackTrace();
            throw new RuntimeException(e);
        }
        
    }

    @Override
    public Integer cadastrar(String cliente, Integer senha, String cpf, 
            Date dataDeNascimento) throws RemoteException {
        try{
            ZonedDateTime date = ZonedDateTime.now();
            System.out.println(DateTimeFormatter.ofPattern("dd/MM/yyyy - "
                + "HH:mm").format(date) + " - Iniciando solicitação de Cadastro");
            System.out.println("Cadastrando usuário...");
            Cadastrar cadastro = new Cadastrar();
            Integer resp = cadastro.executa(cliente, senha, cpf, dataDeNascimento);
            System.out.println();
            return resp;
        }catch(Exception e){
            System.out.println("Erro no servidor de cadastro.");
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

}
