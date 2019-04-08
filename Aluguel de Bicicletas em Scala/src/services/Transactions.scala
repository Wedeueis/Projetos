package services
import utils._
import model._

object Transactions extends Service {
  
 def toMap(l: List[Transaction],m: List[Map[String,String]]): List[Map[String,String]] = {
   if(l.isEmpty) m
   else{
    val t_date = l.head.date
    val t_type = l.head.t_type
    val id = l.head.transaction_id
    val value = l.head.value
    val client = l.head.client_id
    toMap(l.tail,Map("t_date"->t_date.toString(),"t_type"->t_type.toString(),"id"->id.toString(),
                      "value"->value.toString, "client"->client.toString())::m)
   }
 }
  def execute(req: Request): Response = {
    val user = req.params.get("user").get
    val transactions = TransactionDAO.listByClient(ClientDAO.read(user))
    if(transactions.isEmpty){
      Response(status= -1,description= "Nenhuma transação encontrada")
    }else{
      Response(content= toMap(transactions, List()), description= "OK")
    }   
  }
}