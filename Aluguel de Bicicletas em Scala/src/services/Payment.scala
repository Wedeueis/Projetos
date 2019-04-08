package services
import utils._
import model._
import java.sql.Time

case class Item(station: Int, id: Int, valor: Double, inicio: Time,fim: Time);

object Payment extends Service{
  def execute(req: Request): Response= {
    val charge = req.params.get("charge").get.toDouble
    val user = req.params.get("user").get    
    val client = ClientDAO.read(user)
    if(client.credits >= charge){
      ClientDAO.update(client.copy(credits = client.credits - charge) )
      Response(description= "Pagamento efetuado com suceso!")
    }else{
      Response(status= -1, description= "Créditos insuficientes")
    }
  }
  
  def calc(u:String, v: List[Item]): Map[String,String] = {
    def go(l: List[Item], sum: Double): Double = {
      if(l.isEmpty) sum
      else go(l.tail, sum + l.head.valor)
    }
    val total = go(v, 0)
    Map("user" -> u, "charge" -> total.toString())
  }
}