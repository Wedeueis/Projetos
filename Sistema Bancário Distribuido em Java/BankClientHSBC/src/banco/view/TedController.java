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
import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXComboBox;
import com.jfoenix.controls.JFXTextField;
import java.rmi.RemoteException;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;

/**
 *
 * @author camila
 */
public class TedController {

    @FXML
    private JFXTextField contaField;

    @FXML
    private JFXTextField valorField;

    @FXML
    private JFXComboBox<Label> bancoBox;

    @FXML
    private JFXButton tranferirButton;
    
    // Referencia para a aplicacao principal
    private BankClient bankClient;

    @FXML
    private void initialize(){
        //bancoBox.getItems().add(new Label("1 - Itaú"));
        bancoBox.getItems().add(new Label("1 - Itau"));
 
        bancoBox.setPromptText("Escolha o banco...");
    }
    
    @FXML
    void handleTED() {
        try{
            String menssErro = "";
            
            //Valida conta inserida
            if(contaField.getText() == null || contaField.getText().length() == 0){
                menssErro += "Insira a conta para a qual deseja realizar um TED!\n";
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
                menssErro += "Insira o valor para realizar o TED!\n";
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
             * Em caso negativo tenta realizar o TED
             */
            Alert alert = new Alert(Alert.AlertType.ERROR);
            if (menssErro.length() != 0) {
                // Mostra a mensagem de erro.
                alert.setTitle("Campos Inválidos");
                alert.setHeaderText("Corrija os campos inválidos para"
                        + "\n prosseguir com o TED");
                alert.setContentText(menssErro);
                alert.showAndWait();
            }else{
                Request tedReq = new Request();
                tedReq.setOperacao("TEDCliente");
                tedReq.setConta_origem(account);
                tedReq.setConta_destino(Integer.parseInt(contaField.getText()));
                tedReq.setBanco_origem(BankClient.BANKNUMBER);

                String bancoDest = bancoBox.getValue().getText();
                tedReq.setBanco_destino(Character.getNumericValue(bancoDest.charAt(0)));

                tedReq.setValor(Double.parseDouble(valorField.getText()));
                Response tedResp = LoginController.service.processar(tedReq);
                
                if(tedResp.getStatus()== 1){
                    // Mostra a mensagem de erro.
                    alert.setTitle("Falha no TED");
                    alert.setHeaderText("Falha ao tentar realizar TED");
                    alert.setContentText(tedResp.getContent());
                    alert.showAndWait();
                }else{
                    Alert alert2 = new Alert(Alert.AlertType.INFORMATION);
                    // Mostra a mensagem de sucesso.
                    alert2.setTitle("Sucesso no TED");
                    alert2.setHeaderText("TED realizado com sucesso!");
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
    private void handleTransferencia() throws RemoteException{
        bankClient.showTranferencia();
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
