/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco.view;

import banco.BankClient;
import banco.Request;
import banco.Response;
import com.jfoenix.controls.JFXTextArea;
import java.rmi.RemoteException;
import javafx.fxml.FXML;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.StackPane;

/**
 *
 * @author camila
 */
public class ExtratoController { 

    @FXML
    private ScrollPane extratoScrollPane;

    @FXML
    private StackPane extratoStackPane;  
    
    @FXML
    private JFXTextArea extratoTextArea;    
    
    // Referencia para a aplicacao principal
    private BankClient bankClient;
    
    /**
     * Método chamado automaticamente
     * após o arquivo fxml ter sido carregado
     */
    @FXML
    private void initialize() {
        try{
            Request extReq = new Request();
            extReq.setOperacao("Extrato");
            extReq.setConta_origem(LoginController.account);
            Response extResp = LoginController.service.processar(extReq);
            extratoScrollPane.setContent(extratoStackPane);
            extratoTextArea.setText(extResp.getContent());
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

    
    /**
    *Chamado pela aplicação principal para dar uma referência de volta a si mesma
    */
    public void setBankClient(BankClient bankClient) {
        this.bankClient = bankClient;
    }   
    
}
