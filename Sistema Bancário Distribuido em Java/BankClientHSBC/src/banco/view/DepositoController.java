/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco.view;

import banco.BankClient;
import banco.Request;
import banco.Response;
import static banco.view.LoginController.account;
import static banco.view.LoginController.service;
import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXTextField;
import java.rmi.RemoteException;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;

/**
 *
 * @author camila
 */
public class DepositoController {
    @FXML
    private JFXTextField valorField;   
    
    @FXML
    private JFXButton depositarButton;  
    
    // Referencia para a aplicacao principal
    private BankClient bankClient;
    
    @FXML
    private void handleDepositar() {
        try{
            String menssErro = "";
            
            //Valida valor inserido
            if(valorField.getText() == null || valorField.getText().length() == 0){
                menssErro += "Insira o valor que deseja Depositar!\n";
            }else {
                //Tenta converter o número da conta em um inteiro
                try{
                   Double.parseDouble(valorField.getText());
                }catch (NumberFormatException e) {
                   menssErro += "Insira um valor como:\n"
                           + "100\n"
                           + "200.50\n"; 
                }   
            }
            
             /**
             * Verifica se existem erros no valor inserido
             * Em caso positivo mostra um alerta
             * Em caso negativo tenta realizar o depósito
             */
            Alert alert = new Alert(Alert.AlertType.ERROR);
            if (menssErro.length() != 0) {
                // Mostra a mensagem de erro.
                alert.setTitle("Valor Inválido");
                alert.setHeaderText("Insira um valor válido\n"
                        + "para prosseguir com o Depósito");
                alert.setContentText(menssErro);
                alert.showAndWait();
            }else{
                Request depReq = new Request();
                depReq.setOperacao("Deposito");
                depReq.setConta_destino(account);
                depReq.setValor(Double.parseDouble(valorField.getText()));
                Response depResp = service.processar(depReq);
                
                if(depResp.getStatus()== 1){
                    // Mostra a mensagem de erro.
                    alert.setTitle("Falha no Depósito");
                    alert.setHeaderText("Falha ao tentar realizar o Depósito");
                    alert.setContentText(depResp.getContent());
                    alert.showAndWait();
                }else{
                    Alert alert2 = new Alert(Alert.AlertType.INFORMATION);
                    // Mostra a mensagem de sucesso.
                    alert2.setTitle("Sucesso no Depósito");
                    alert2.setHeaderText("Depósito realizado com sucesso!");
                    alert2.showAndWait();
                    bankClient.showSaldo();
                }
            }
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
    
    @FXML
    private void handleSaldo() throws RemoteException{
        bankClient.showSaldo();
    }    
    
    @FXML
    private void handleSaque() throws RemoteException{
        bankClient.showSaque();
    }  
        
    @FXML
    private void handleTransferencia() throws RemoteException{
        bankClient.showTranferencia();
    }  

    @FXML
    private void handleTED() throws RemoteException{
        bankClient.showTED();
    } 
    
    @FXML
    private void handleExtrato() throws RemoteException{
        bankClient.showExtrato();
    }     
    
     /**
     *Chamado pela aplicação principal para dar uma referência de volta a si mesma
     */
    public void setBankClient(BankClient bankClient) {
        this.bankClient = bankClient;
    }  
}
