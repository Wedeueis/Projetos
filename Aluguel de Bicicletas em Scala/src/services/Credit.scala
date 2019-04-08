package services
import utils._
import model._
import java.sql.Date
import java.util.Calendar

object Credit extends Service {
  def execute(req: Request): Response = {
    val value = req.params.get("value").get.toDouble
    val user = req.params.get("user").get
    val client = ClientDAO.read(user)
    if(client == null){
      Response(status= -1,description= "usuário inválido")
    }else{
      TransactionDAO.create(Transaction(0, new Date(Calendar.getInstance().getTimeInMillis()), 0, 
                  client.client_id, value))                 
      ClientDAO.update(client.copy(credits = client.credits + value))
      Response(description= client.credits.toString)
    }    
  }
}