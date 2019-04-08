import scalafx.Includes._
import scalafx.scene.control.TextField
import scalafx.event.ActionEvent
import scalafx.scene.control.Alert.AlertType
import scalafx.scene.control.Alert
import scalafx.scene.control.Button
import java.sql.Time
import scalafxml.core.macros.sfxml
import services._
import model._

@sfxml
class AluguelController(private val txtPosto: TextField, private val txtBike: TextField,
                        private val txtDe: TextField, private val txtA: TextField, 
                        private val addCart: Button) {
  
  def btnClick_Alugar(event: ActionEvent) {
    val bike = BikeDAO.read(txtBike.getText.toInt)
    if(bike!=null){
      val item = Item(txtPosto.getText.toInt, txtBike.getText.toInt, bike.tax, Time.valueOf(txtDe.getText.toString),
        Time.valueOf(txtA.getText.toString))
      BikeRent.cart += item
      BikeRent.updateCartTxt()
      txtPosto.setText("")
      txtBike.setText("")
      txtDe.setText("")
      txtA.setText("")
    }
    else
      new Alert(AlertType.Information, "Bicicleta não localizada!").showAndWait()

  }
}