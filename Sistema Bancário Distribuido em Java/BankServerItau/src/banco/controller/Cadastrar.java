/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco.controller;

import banco.model.Conta;
import banco.model.ContaDAO;
import java.sql.Date;

/**
 *
 * @author camila
 */
public class Cadastrar {
    public int executa(String cliente, int senha, String cpf, 
        Date dataDeNascimento) throws Exception{
        ContaDAO dao = new ContaDAO();
        Conta conta = new Conta();
        
        //Seta os valores passados no cliente que será inserido no banco
        conta.setCliente(cliente);
        conta.setSenha(senha);
        conta.setCpf(cpf);
        conta.setDataDeNascimento(dataDeNascimento);
        conta.setSaldo(0.0);
        
        try{
            dao.inserirConta(conta);  
            return dao.buscarConta(cpf).getNumero();
            
        }catch(Exception e){
            e.printStackTrace();
            return -1;
        }
    }
}
