import scalafxml.core.FXMLView
import scalafxml.core.NoDependencyResolver
import scalafxml.core.macros.sfxml
import javafx.event.ActionEvent
import scalafx.scene.control.Alert.AlertType
import scalafx.scene.control.Alert
import scalafx.scene.control.ListView
import scalafx.collections.ObservableBuffer
import scalafx.scene.input.MouseEvent
import javafx.scene.layout.BorderPane
import javafx.scene.control.TextArea
import javafx.scene.control.Label
import utils._
import services._

@sfxml
class PrincipalController(private val listMenu: ListView[String], private val borderPane: BorderPane,
                          private val txtSaldo: Label, private val txtCart: TextArea) {
  
  setNovoFXML("Aluguel.fxml")
  BikeRent.saldo = txtSaldo
  BikeRent.txtCart = txtCart
  BikeRent.updateSaldoTxt("R$ "+ ServiceProvider.process(Request("Balance",Map("user"->BikeRent.user))).description)
  
  val itemsMenu = ObservableBuffer("Alugue uma Bike", "Reserve sua Bike", "Recarga", "Histórico", "Extrato", "Mapa de Postos")
  listMenu.items = itemsMenu
  listMenu.setFixedCellSize(50)
      
  def mouseEvent(event: MouseEvent){
    val itemMenu = listMenu.getSelectionModel().getSelectedItem()
    
    itemMenu match {
      case "Alugue uma Bike" => setNovoFXML("Aluguel.fxml")
                                
      case "Reserve sua Bike" => setNovoFXML("Reserva.fxml")
                                 
      case "Recarga" => setNovoFXML("Recarga.fxml")
                                 
      case "Histórico" => setNovoFXML("Historico.fxml")
                                 
      case "Extrato" => setNovoFXML("Extrato.fxml")
                                 
      case "Mapa de Postos" => setNovoFXML("Mapa.fxml")
    }
  }  
  
  def mnClose_Click(event: ActionEvent){
    sys.exit(0)
  }
  
  def btnClick_Pagar(event: ActionEvent) {
    if(!BikeRent.cart.isEmpty) {
      val req = Request("Payment", Payment.calc(BikeRent.user, BikeRent.cart.toList))
      val resp = ServiceProvider.process(req)
      if(resp.status == 0){
        var erro = false
        for(item <- BikeRent.cart.toList){
          val req2 = Request("Rentall", Map("user"->BikeRent.user, "bike_id"->item.id.toString, 
                              "start"->item.inicio.toString,"finish"->item.fim.toString, 
                              "value"->item.valor.toString))
          val resp2 = ServiceProvider.process(req2)
          println(resp2.description)
          if(resp2.status!=0) {
            erro = true
          }
        }
        if (!erro)
          new Alert(AlertType.Information, "Pagamento realizado com sucesso!").showAndWait()
        else
          new Alert(AlertType.Information, "Falha ao realizar pagamento!\nEntre" +
                      " em contato com nossa central \nde atendimento.").showAndWait()
        BikeRent.updateSaldoTxt("R$ " + ServiceProvider.process(Request("Balance",Map("user"->BikeRent.user))).description)
        BikeRent.cart.clear
        BikeRent.updateCartTxt()
      }else{
        new Alert(AlertType.Information, "Saldo insuficiente!").showAndWait()
      }
    }
  }
  
  def setNovoFXML(nomeTela: String){
    val fxmlLoader = FXMLView(getClass().getResource(nomeTela),NoDependencyResolver)
    borderPane.setCenter(fxmlLoader)
  }
}