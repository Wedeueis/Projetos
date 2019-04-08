/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco.view;

import banco.BankClient;
import static banco.view.LoginController.service;
import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXPasswordField;
import com.jfoenix.controls.JFXTextField;
import java.sql.Date;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

/**
 *
 * @author camila
 */
public class CadastroController {

    @FXML
    private JFXTextField cpfTextField;

    @FXML
    private JFXTextField nomeTextField;

    @FXML
    private JFXTextField nascimentoTextField;

    @FXML
    private JFXPasswordField senhaTextField;

    @FXML
    private JFXPasswordField confSenhaTextField;

    @FXML
    private JFXButton cadastrarButton;   
    
    @FXML
    private JFXButton voltarButton;     
    
    // Referencia para a aplicacao principal
    private BankClient bankClient;    
    
        
    @FXML
    private void handleCadastrar(){
        try{
            String menssErro = "";
            
            //Valida nome do cliente
            if (nomeTextField.getText() == null || nomeTextField.getText().length() == 0) {
                menssErro += "Insira seu Nome!\n"; 
            }
            //Valida cpf do cliente
            if(cpfTextField.getText() == null || cpfTextField.getText().length() == 0){
                menssErro += "Insira seu CPF!\n";
            }
            //Valida senha do cliente
            if(senhaTextField.getText() == null || senhaTextField.getText().length() != 4){
                menssErro += "A senha não deve ser nula e deve ter 4 dígitos!\n";
            }else {
                //Tenta converter a senha em um inteiro
                try{
                   Integer.parseInt(senhaTextField.getText());
                }catch (NumberFormatException e) {
                   menssErro += "Senha inválida! A senha deve conter 4 dígitos numéricos!\n"; 
                }   
            }
            //Valida confSenha do cliente
            if(confSenhaTextField.getText() == null || confSenhaTextField.getText().length() != 4){
                menssErro += "A confirmação de senha não deve ser nula e deve ter 4 dígitos!\n";
            }else {
                //Tenta converter a senha em um inteiro
                try{
                   Integer.parseInt(confSenhaTextField.getText());
                }catch (NumberFormatException e) {
                   menssErro += "Confirmação de senha inválida! A confirmação de senha deve conter 4 dígitos numéricos!\n"; 
                }   
            }  
            //Valida nascimento do cliente
            if(nascimentoTextField.getText() == null || nascimentoTextField.getText().length() == 0){
                menssErro += "Insira sua data de nascimento no formato indicado "
                        + "(YYYY-MM-DD)\n";
            }else{
                //Tenta converter a data para o formato Date
                try{
                   Date.valueOf(nascimentoTextField.getText()); 
                }catch (Exception e) {
                   menssErro += "A data de nascimento deve ser inserida no formato YYYY-MM-DD!\n"; 
                } 
            }
            
            /**
             * Verifica se existem erros na mensagem
             * Em caso positivo mostra um alerta
             * Em caso negativo tenta realizar o cadastro
             */
            if (menssErro.length() != 0) {
                // Mostra a mensagem de erro.
                Alert alert = new Alert(AlertType.ERROR);
                alert.setTitle("Campos Inválidos");
                alert.setHeaderText("Corrija os campos inválidos para prosseguir com o Cadastro!");
                alert.setContentText(menssErro);
                alert.showAndWait();
            }else{
                String cliente = nomeTextField.getText();
                String cpf = cpfTextField.getText();
                Integer senha = Integer.parseInt(senhaTextField.getText());  
                Integer confSenha = Integer.parseInt(confSenhaTextField.getText());
                Date nascimento = Date.valueOf(nascimentoTextField.getText()); 
                
                Integer numConta = -1;

                //Verifica se as senha e confirmação de senha são iguais
                if(!senha.equals(confSenha)){
                    // Mostra a mensagem de erro.
                    Alert alert = new Alert(AlertType.ERROR);
                    alert.setTitle("Senha inválida");
                    alert.setHeaderText("As senhas inseridas não são iguais!!");
                    alert.setContentText("A senha e confirmação de senha devem ser iguais,\n"
                            + "conter apenas números e ter obrigatoriamente\n"
                            + "4 dígitos");
                    alert.showAndWait();                    
                }else{
                    numConta = service.cadastrar(cliente, senha, cpf, nascimento);   
                    Alert alert = new Alert(AlertType.INFORMATION);                    
                    
                    //Mostra o número da conta em caso de cadastro realizado com sucesso
                    if(numConta != -1){
                        alert.setTitle("Cadastrado com sucesso!");
                        alert.setHeaderText("Seu cadastro foi realizado com sucesso!");
                        alert.setContentText("Anote o número de sua conta para que possa acessá-la,\n"
                                + "sem ele seu acesso ao banco não será possível!!\n"
                                + "Número da conta: "+numConta);
                        alert.showAndWait(); 
                        bankClient.showLogin();
                    }else{
                        alert.setTitle("Falha no Cadastro!");
                        alert.setHeaderText("Ocorreu um erro inesperado ao "
                                + "\ntentar realizar o seu cadastro!");
                        alert.setContentText("Infelizmente seu cadastro\n"
                                + "não foi realizado com sucesso.\n"
                                + "Por favor tente novamente!");
                        alert.showAndWait();
                        bankClient.showLogin();                        
                    }
                }
            }
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
    
    @FXML
    private void handleVoltar(){
        bankClient.showLogin();
    }
    
    /**
    *Chamado pela aplicação principal para dar uma referência de volta a si mesma
    */
    public void setBankClient(BankClient bankClient) {
        this.bankClient = bankClient;
    }     
}
