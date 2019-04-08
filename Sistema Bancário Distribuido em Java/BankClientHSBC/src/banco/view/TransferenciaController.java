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
public class TransferenciaController {
@FXML
    private JFXTextField contaField;

    @FXML
    private JFXTextField valorField;   
    
    @FXML
    private JFXButton tranferirButton;  
    
    // Referencia para a aplicacao principal
    private BankClient bankClient;
    
    @FXML
    private void handleTransferir() {
        try{
            String menssErro = "";
            
            //Valida conta inserida
            if(contaField.getText() == null || contaField.getText().length() == 0){
                menssErro += "Insira a conta para a qual deseja realizar a Transferência!\n";
            }else {
                //Tenta converter o número da conta em um inteiro
                try{
                   Integer.parseInt(contaField.getText());
                }catch (NumberFormatException e) {
                   menssErro += "Insira um número de conta válido!"
                           + "\nExemplo:"
                           + "\n1"
                           + "\n387"
                           + "\n4578\n"; 
                }   
            }
            //Valida valor inserido
            if(valorField.getText() == null || valorField.getText().length() == 0){
                menssErro += "Insira o valor para realizar a Transferência!\n";
            }else {
                //Tenta converter o valor inserido em um double
                try{
                   Double.parseDouble(valorField.getText());
                }catch (NumberFormatException e) {
                   menssErro += "Insira um valor como:\n"
                           + "100\n"
                           + "200.50\n"; 
                }   
            }
            
             /**
             * Verifica se existem erros nos campos inseridos
             * Em caso positivo mostra um alerta
             * Em caso negativo tenta realizar a transferência
             */
            Alert alert = new Alert(Alert.AlertType.ERROR);
            if (menssErro.length() != 0) {
                // Mostra a mensagem de erro.
                alert.setTitle("Campos Inválidos");
                alert.setHeaderText("Corrija os campos inválidos para"
                        + "\n prosseguir com a Transferência!");
                alert.setContentText(menssErro);
                alert.showAndWait();
            }else{
                Request transReq = new Request();
                transReq.setOperacao("Transferencia");
                transReq.setConta_origem(account);
                transReq.setConta_destino(Integer.parseInt(contaField.getText()));
                transReq.setValor(Double.parseDouble(valorField.getText()));
                Response transResp = service.processar(transReq);
                
                if(transResp.getStatus()== 1){
                    // Mostra a mensagem de erro.
                    alert.setTitle("Falha na Transferência");
                    alert.setHeaderText("Falha ao tentar realizar Transferência");
                    alert.setContentText(transResp.getContent());
                    alert.showAndWait();
                }else{
                    Alert alert2 = new Alert(Alert.AlertType.INFORMATION);
                    // Mostra a mensagem de sucesso.
                    alert2.setTitle("Sucesso na Transferência");
                    alert2.setHeaderText("Transferência realizada com sucesso!");
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
    private void handleDeposito() throws RemoteException{
        bankClient.showDeposito();
    }  
    
    @FXML
    private void handleSaque() throws RemoteException{
        bankClient.showSaque();
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
