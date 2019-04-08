/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco.view;

import banco.BankClient;
import com.jfoenix.controls.JFXButton;
import java.rmi.RemoteException;
import javafx.fxml.FXML;

/**
 *
 * @author camila
 */
public class HomeController {
    
    @FXML
    private JFXButton saldoButton;
    
    @FXML
    private JFXButton depositoButton;
    
    @FXML
    private JFXButton saqueButton;
    
    @FXML
    private JFXButton transfButton;
    
    @FXML
    private JFXButton tedButton;
    
    @FXML
    private JFXButton extratoButton;
    
    // Referencia para a aplicacao principal
    private BankClient bankClient;    
    
    
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
