package services
import model._
import java.sql.{Time,Date}
import utils._
import java.util.Calendar

object Rentall extends Service {
  def execute(req: Request): Response = {
    val date = new Date(Calendar.getInstance().getTimeInMillis())
    val user = req.params.get("user").get
    val bike_id = req.params.get("bike_id").get
    val start = req.params.get("start").get
    val finish = req.params.get("finish").get
    val value = req.params.get("value").get
    val bike = BikeDAO.read(bike_id.toInt)
    val client = ClientDAO.read(user).client_id
    if(bike == null) Response(status= -1, description= "Não foi possível localizar a bicicleta")
    else{
      RentDAO.create(Rent(0, date, client, bike_id.toInt, Time.valueOf(start), 
                     Time.valueOf(finish), value.toDouble))
      BikeDAO.update(bike.copy(state= 1))
      Response(status=0, description= "Aluguel registrado")
    }
   
  }
}