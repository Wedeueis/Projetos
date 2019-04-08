package services

import utils._
import model._

object Authenticate extends Service {
  def execute(req: Request): Response = {
    val user = req.params.get("user").get
    val password = req.params.get("password").get
    
    val client = ClientDAO.read(user)

    if(client == null){
       Response(status= -1,description="Usuário invalido.")
    }else{
      if(client.password.equals(password)){
        Response(description="Logado com sucesso!")
      }else{
        Response(status= -1, description="Senha inválida.")
      }
    }
  }
}