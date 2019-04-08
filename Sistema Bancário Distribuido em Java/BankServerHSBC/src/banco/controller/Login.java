package banco.controller;

import banco.model.Conta;
import banco.model.ContaDAO;

public class Login {
    public Boolean executa(int numero, int password) throws Exception{
        ContaDAO dao = new ContaDAO();
        Conta conta = dao.buscarConta(numero);
        if(conta==null){
            System.out.println("Solicitação de login indeferida: número de "
                    + "conta inválido.");
            return false;
        }else if(conta.getSenha().equals(password)){
             System.out.println(conta.getCliente()+", conta "+ conta.getNumero()
                     + " se logou.");
             return true;
        }else{
             System.out.println("Solicitação de login indeferida: "
                     + "senha incorreta.");
             return false;
        }
    }
}
