/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco.view;

import banco.BankClient;
import banco.Request;
import banco.Response;
import com.jfoenix.controls.JFXButton;
import java.rmi.RemoteException;
import javafx.fxml.FXML;
import javafx.scene.control.Label;

/**
 *
 * @author camila
 */
public class SaldoController {
    
    @FXML
    private JFXButton saldoButton;
        
    @FXML
    private Label saldoLabel;
    
    // Referencia para a aplicacao principal
    private BankClient bankClient;
    
    /**
     * Método chamado automaticamente
     * após o arquivo fxml ter sido carregado
     */
    @FXML
    private void initialize() {
        try{
            Request saldoReq = new Request();
            saldoReq.setOperacao("Saldo");
            Integer account = LoginController.account;
            saldoReq.setConta_origem(account);
            Response saldoResp = LoginController.service.processar(saldoReq);
            saldoLabel.setText("R$ " + saldoResp.getContent() + "0");
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
