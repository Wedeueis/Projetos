/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco.view;

import banco.Bank;
import banco.BankClient;
import static banco.BankClient.BANKNUMBER;
import static banco.BankClient.CENTRAL_BANK_ADRESS;
import banco.IBinder;
import banco.IService;
import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXPasswordField;
import com.jfoenix.controls.JFXTextField;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;

/**
 *
 * @author camila
 */
public class LoginController {
    
    @FXML
    private JFXPasswordField passwordField;

    @FXML
    private JFXTextField accountField;

    @FXML
    private JFXButton signInField;

    @FXML
    private JFXButton SignUpField;
 
    // Referencia para a aplicacao principal
    private BankClient bankClient;
    
    public static IService service;

    public static Integer account;

    @FXML
    private void initialize(){
        try{
            Bank bank = consultar();
            Registry registry = LocateRegistry.getRegistry(bank.getIp(), bank.getPort());
            if(registry == null){
                System.out.println("Client parou: serviço rmi indisponivel");
                throw new RemoteException();
            }
            String location = "rmi://"+bank.getIp() +":"+ bank.getPort() + "/Service";
            service = (IService) Naming.lookup(location);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }

    @FXML
    private void handleSignIn(){
        try{
            String menssErro = "";
            
            //Valida conta do cliente
            if(accountField.getText() == null || accountField.getText().length() == 0){
                menssErro += "Insira o número da sua conta!\n";
            }else {
                //Tenta converter o número da conta em um inteiro
                try{
                   Integer.parseInt(accountField.getText());
                }catch (NumberFormatException e) {
                   menssErro += "Número de conta inválido! Este campo só deve conter números!\n"; 
                }   
            }
            //Valida senha do cliente
            if(passwordField.getText() == null || passwordField.getText().length() != 4){
                menssErro += "A senha não deve ser nula e deve ter 4 dígitos!\n";
            }else {
                //Tenta converter o número da conta em um inteiro
                try{
                   Integer.parseInt(passwordField.getText());
                }catch (NumberFormatException e) {
                   menssErro += "Senha inválida! A senha deve conter 4 dígitos numéricos!\n"; 
                }   
            }
            
            /**
             * Verifica se existem erros na mensagem
             * Em caso positivo mostra um alerta
             * Em caso negativo tenta realizar o login
             */
            Alert alert = new Alert(Alert.AlertType.ERROR);
            if (menssErro.length() != 0) {
                // Mostra a mensagem de erro.
                alert.setTitle("Campos Inválidos");
                alert.setHeaderText("Corrija os campos inválidos para prosseguir com o Login!");
                alert.setContentText(menssErro);
                alert.showAndWait();
            }else{
                account = Integer.parseInt(accountField.getText());
                Integer password = Integer.parseInt(passwordField.getText());           
                
                Boolean testeLogin = service.logar(account, password);
                
                //Verifica se os dados do login estão corretos
                if(!testeLogin){
                    alert.setTitle("Falha no Login!");
                    alert.setHeaderText("Dados não cadastrados");
                    alert.setContentText("Os dados inseridos não pertencem a nenhum\n"
                            + "cliente do banco!");
                    alert.showAndWait();
                }else{
                    //Redireciona para home quando login está correto
                    bankClient.showHome();
                }
            }
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
    
    @FXML
    private void handleSignUp(){
        bankClient.showCadastro();
    }
    
     /**
     *Chamado pela aplicação principal para dar uma referência de volta a si mesma
     */
    public void setBankClient(BankClient bankClient) {
        this.bankClient = bankClient;
    }
    
    private static Bank consultar(){
        try{
            String location = "rmi://"+CENTRAL_BANK_ADRESS+"/CentralBank";
            IBinder binder = (IBinder) Naming.lookup(location);
            return binder.consult(BANKNUMBER);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
}
