package services
import utils._
import model._

object Balance extends Service {
  def execute(req: Request): Response = {
    val user = req.params.get("user").get
    val client = ClientDAO.read(user)
    if(client == null){
      Response(status= -1,description= "usuário inválido")
    }else{                
      Response(description= client.credits.toString)
    }    
  }
}