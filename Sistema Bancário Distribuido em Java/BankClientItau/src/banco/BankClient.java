/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco;

import banco.view.CadastroController;
import banco.view.DepositoController;
import banco.view.ExtratoController;
import banco.view.HomeController;
import banco.view.LoginController;
import banco.view.SaldoController;
import banco.view.SaqueController;
import banco.view.TedController;
import banco.view.TransferenciaController;
import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

/**
 *
 * @author camila
 */
public class BankClient extends Application {
    public static final String CENTRAL_BANK_ADRESS = "localhost:8000";
    public static final int BANKNUMBER = 1;
    public static final String BANKNAME = "Itaú";
    
    private Stage primaryStage;
    private BorderPane rootLayout;

    //Construtor
    public BankClient(){
    }

    @Override
    public void start(Stage primaryStage){
        this.primaryStage = primaryStage;
        this.primaryStage.setTitle(BANKNAME);
        this.primaryStage.setResizable(false);
        
        initRootLayout();
        showLogin();
    }
    
    public void initRootLayout(){
        try{
            //Carrega o arquivo fxml RootLayout
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/RootLayout.fxml"));
            rootLayout = (BorderPane) loader.load();
            
            //Mostra a scene contendo o rootLayout
            Scene scene = new Scene(rootLayout);
            primaryStage.setScene(scene);
            primaryStage.show();      
            
        }catch (IOException e){
            e.printStackTrace();
        }
    }
    
    //Coloca Login dentro do RootLayout
    public void showLogin(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Login.fxml"));
            AnchorPane login = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(login);
            
            //Dá ao LoginController acesso ao BankClient
            LoginController controller = loader.getController();
            controller.setBankClient(this);
            
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    //Coloca Login dentro do RootLayout
    public void showHome(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Home.fxml"));
            AnchorPane home = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(home);
            
            //Dá ao HomeController acesso ao BankClient
            HomeController controller = loader.getController();
            controller.setBankClient(this);
            
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    //Coloca Login dentro do RootLayout
    public void showCadastro(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Cadastro.fxml"));
            AnchorPane cadastro = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(cadastro);
            
            //Dá ao CadastroController acesso ao BankClient
            CadastroController controller = loader.getController();
            controller.setBankClient(this);    
            
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    //Coloca Saldo.fxml dentro do RootLayout
    public void showSaldo(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Saldo.fxml"));
            AnchorPane saldo = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(saldo);
            
            //Dá ao SaldoController acesso ao BankClient
            SaldoController controller = loader.getController();
            controller.setBankClient(this);            
            

            
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    //Coloca Deposito.fxml dentro do RootLayout
    public void showDeposito(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Deposito.fxml"));
            AnchorPane deposito = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(deposito);
            
            //Dá ao DepositoController acesso ao BankClient
            DepositoController controller = loader.getController();
            controller.setBankClient(this);
            
        }catch(IOException e){
            e.printStackTrace();
        }
    }    
    
    //Coloca Saque.fxml dentro do RootLayout
    public void showSaque(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Saque.fxml"));
            AnchorPane saque = (AnchorPane) loader.load();
            
            //Coloca o Saque no centro do RootLayout
            rootLayout.setCenter(saque);
            
            //Dá ao DepositoController acesso ao BankClient
            SaqueController controller = loader.getController();
            controller.setBankClient(this);
            
        }catch(IOException e){
            e.printStackTrace();
        }
    } 
    
    //Coloca Transferencia.fxml dentro do RootLayout
    public void showTranferencia(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Transferencia.fxml"));
            AnchorPane transferencia = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(transferencia);
            
            //Dá ao DepositoController acesso ao BankClient
            TransferenciaController controller = loader.getController();
            controller.setBankClient(this);
            
        }catch(IOException e){
            e.printStackTrace();
        }
    }     
    
    //Coloca Ted.fxml dentro do RootLayout
    public void showTED(){
        try{
            //Carrega o arquivo FXML Login
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Ted.fxml"));
            AnchorPane ted = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(ted);
            
            //Dá ao DepositoController acesso ao BankClient
            TedController controller = loader.getController();
            controller.setBankClient(this);
            
        }catch(IOException e){
            e.printStackTrace();
        }
    }     
    
    //Coloca Extrato.fxml dentro do RootLayout
    public void showExtrato(){
        try{
            //Carrega o arquivo FXML Extrato
            FXMLLoader loader =  new FXMLLoader();
            loader.setLocation(BankClient.class.getResource("view/Extrato.fxml"));
            AnchorPane extrato = (AnchorPane) loader.load();
            
            //Coloca o Login no centro do RootLayout
            rootLayout.setCenter(extrato);
            
            //Dá ao ExtratoController acesso ao BankClient
            ExtratoController controller = loader.getController();
            controller.setBankClient(this);
            
        }catch(IOException e){
            e.printStackTrace();
        }
    }     
        
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

}
