import scalafx.application.JFXApp
import java.sql.Time
import scala.collection.mutable.ListBuffer
import javafx.scene.control.TextArea
import javafx.scene.control.Label
import services._

object BikeRent extends JFXApp {
      val cart = ListBuffer.empty[Item]
      var txtCart:TextArea = null
      var saldo:Label = null
      var user = "";
   
      val mStage = new MontaStage
      mStage.montaS("Login.fxml")
      
      def updateSaldoTxt(s: String){
        saldo.setText(s)     
      }
      def updateCartTxt(){
        val list = cart.toList
        txtCart.setText("")
        for(x <- list){
          val txt = "id da Bike: " + x.id + " valor R$: " + x.valor
          txtCart.appendText(txt + "\n")
        }        
      }
}
