import scalafx.Includes._
import scalafx.scene.control.TextArea
import scalafx.event.ActionEvent
import scalafxml.core.macros.sfxml
import utils._
import services._


@sfxml
class ExtratoController(private val txtExtrato: TextArea) {
  val resp = ServiceProvider.process(Request("Transactions",Map("user"->BikeRent.user)))
  if(resp.status == 0){
    txtExtrato.setText("data                  descrição       tipo  valor\n")
    val map = resp.content
    for(line <- map){
      val t_type = line.get("t_type").get.toInt
      val typeTxt = t_type match{
        case 0 => txtExtrato.appendText(line.get("t_date").get + "       recarga           C     " + line.get("value").get + "\n")
        case 1 => txtExtrato.appendText(line.get("t_date").get + "       aluguel           D     -" + line.get("value").get + "\n")     
      }     
    }
  }
}