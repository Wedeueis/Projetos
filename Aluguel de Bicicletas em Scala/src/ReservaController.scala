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
class ReservaController(private val txtPosto: TextField, private val txtBike: TextField,
                        private val txtData: TextField, private val txtInicio: TextField, 
                        private val reservar: Button)  {
  
  def btnClick_Reservar(event: ActionEvent) {
    if(ServiceProvider.process(Request("Booking",Map("user"->BikeRent.user, 
                           "bike_id"->txtBike.getText,"date"->txtData.getText,
                           "time"->txtInicio.getText.toString))).status == 0) {
          new Alert(AlertType.Information, "Reserva realizada com sucesso").showAndWait()
          txtPosto.setText("")
          txtBike.setText("")
          txtData.setText("")
          txtInicio.setText("")
     }else
         new Alert(AlertType.Information, "Serviço indisponivel. Tente novamente mais tarde.").showAndWait()
   } 
}