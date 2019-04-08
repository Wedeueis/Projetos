package services
import utils._
import model._
import java.sql.{Date,Time}

object Book extends Service {
  def execute(req: Request): Response ={
    val user = req.params.get("user").get
    val bike_id = req.params.get("bike_id").get.toInt
    val date = Date.valueOf(req.params.get("date").get)
    val time = Time.valueOf(req.params.get("time").get)
    val client = ClientDAO.read(user)
    if(client == null){
      Response(status= -1,description= "usuário inválido")
    }else{
      BookingDAO.create(Booking(-1, client.client_id, bike_id, date, time))
      val bike = BikeDAO.read(bike_id)
      BikeDAO.update(bike.copy(state = 2))
      Response(description= "reserva realizada com sucesso")
    }
  }
  
  def counter(){
    //create a concurrent task that counts the booking time in background
  }
}