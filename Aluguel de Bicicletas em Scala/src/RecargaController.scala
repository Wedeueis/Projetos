import scalafx.Includes._
import scalafx.scene.control.TextField
import scalafx.event.ActionEvent
import scalafx.scene.control.Button
import scalafxml.core.macros.sfxml
import scalafx.scene.control.Alert.AlertType
import scalafx.scene.control.Alert
import utils._
import services._

@sfxml
class RecargaController(private val txtValor: TextField, private val txtCartao: TextField,
                        private val recarregar: Button){
  def btnClick_Recarregar(event: ActionEvent) {
       val resp = ServiceProvider.process(Request("Credit",Map("user"->BikeRent.user, 
                           "value" ->txtValor.getText.toString)))
       if(resp.status == 0){
          new Alert(AlertType.Information, "Recarga realizada com sucesso").showAndWait()
          BikeRent.updateSaldoTxt("R$ " + ServiceProvider.process(Request("Balance",Map("user"->BikeRent.user))).description)
          txtValor.setText("")
          txtCartao.setText("")
       }else
         new Alert(AlertType.Information, "Serviço indisponivel. Tente novamente mais tarde.").showAndWait()
  }
}