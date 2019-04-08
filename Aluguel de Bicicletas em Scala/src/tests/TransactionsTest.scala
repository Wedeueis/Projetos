package tests
import utils._
import services._

object TransactionsTest {
  def main(args: Array[String]){
    val resp = ServiceProvider.process(Request("Transactions", Map("user" -> "Wedeueis")))
    println(resp.description)
    for(m <- resp.content) {
       println(m.get("id").get+" "+m.get("t_date").get+" "+m.get("t_type").get+" "+
                 m.get("client").get+" "+m.get("value").get)
    }
  }
}