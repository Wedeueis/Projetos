import scalafx.Includes._
import scalafxml.core.macros.sfxml
import javafx.event.ActionEvent
import scalafx.scene.control.Alert.AlertType
import scalafx.scene.control.Alert
import javafx.scene.control.TextField


@sfxml
class ESController(private val txtES: TextField) {
  
  def btnES_Click(event: ActionEvent){
    
    if(true) {
      new Alert(AlertType.Information, "E-mail enviado!").showAndWait()
      val mES = new MontaStage
      mES.montaS("Login.fxml")
    }
    else new Alert(AlertType.Information, "Informe um e-mail válido!").showAndWait()
  }
  
}