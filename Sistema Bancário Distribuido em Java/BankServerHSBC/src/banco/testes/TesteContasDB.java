package banco.testes;

import banco.model.Conta;
import banco.model.ContaDAO;
import banco.model.DBManager;
import java.sql.Date;
import java.util.Scanner;

public class TesteContasDB {
    public static void main(String args[]){
        ContaDAO dao = new ContaDAO();
        DBManager.init();
        Scanner leitura = new Scanner(System.in);
        Integer exit = 0;
        while(exit != 1){
            //MENU
            System.out.println("Ecolha uma das opções abaixo:\n\n"
                +"0 - Sair\n"
                +"1 - Inserir nova conta\n"
                +"2 - Buscar conta por número\n");

            Integer opcao = leitura.nextInt();
            leitura.nextLine(); //esvazia buffer

            switch (opcao){
                case 0: 
                    exit = 1;
                    break;
                    
                case 1:{
                    Conta conta = new Conta();
                    System.out.println("\nInsira o nome do Cliente:");
                    conta.setCliente(leitura.nextLine());
              
                    System.out.println("\nInsira a Senha da conta (Apenas números):");
                    conta.setSenha(leitura.nextInt());
                    leitura.nextLine(); //esvazia buffer

                    System.out.println("\nInsira o CPF do cliente:");
                    conta.setCpf(leitura.nextLine());

                    conta.setSaldo(0.0);
                    conta.setDataDeNascimento(Date.valueOf("1993-12-27"));

                    dao.inserirConta(conta);  
                    break;
                }
                
                case 2:{
                    System.out.println("\nInsira o número da conta:");
                    Integer numero = leitura.nextInt();
                    leitura.nextLine(); //esvazia buffer
                    
                    Conta conta = new Conta();
                    conta = dao.buscarConta(numero);
                    System.out.println("Número da conta: " + conta.getNumero()+ 
                            "\nCliente: " + conta.getCliente() +
                            "\nCPF: " + conta.getCpf() +
                            "\nSaldo: R$" + conta.getSaldo()+
                            "\nData de Nascimento: " + conta.getDataDeNascimento().toString());                                                   
                }
            }
        }
    }
}
