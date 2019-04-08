import scalafx.Includes._
import scalafxml.core.macros.sfxml
import javafx.event.ActionEvent
import scalafx.scene.control.Alert.AlertType
import scalafx.scene.control.Alert
import javafx.scene.control.TextField
import services._
import utils._

@sfxml
class LoginController(private val txtLogin: TextField, 
                      private val txtSenha: TextField){
   
   def btnClick_Entrar(event: ActionEvent) {
     if(ServiceProvider.process(Request("Login",Map("user"->txtLogin.getText(),
                   "password" ->txtSenha.getText()))).status == 0) {
       new Alert(AlertType.Information, "Bem Vindo "+txtLogin.getText()).showAndWait()
       BikeRent.user = txtLogin.getText()
       val mP = new MontaStage
       mP.montaS("Principal.fxml")
       
     }
     else new Alert(AlertType.Information, "Digite um usuário válido").showAndWait()
   }
   
   def hlClick_Event(event: ActionEvent){
       val mES = new MontaStage
       mES.montaS("EsqueceuSenha.fxml")
   }
  def mnClose_Click(event: ActionEvent){
      sys.exit(0)
  }
  def printTeste(){
    println("OK")
  }
}