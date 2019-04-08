package tests
import java.sql.Date
import model._

object DBTransactionTest {
  def main(args: Array[String]){
    val t1 = Transaction(1, Date.valueOf("2008-10-25"), 1, 1, 50.0)
    val t2 = Transaction(2, Date.valueOf("2008-09-20"), 1, 1, -30.0)
    val t3 = Transaction(3, Date.valueOf("2008-11-27"), 1, 1, 45.0)
    //TransactionDAO.create(t1)
    //TransactionDAO.create(t2)
    //TransactionDAO.create(t3)
    //TransactionDAO.update(t1.copy(date= Date.valueOf("2007-11-25")))
    println(TransactionDAO.read(1).date)
    //TransactionDAO.delete(t3)
    val transactions = TransactionDAO.listByClient(Client(1,"","","","","",0.0))
    for(t <- transactions){
      println(t.transaction_id+" "+t.date+" "+t.t_type+" "+t.client_id+" "+t.value)
    }
  }
}