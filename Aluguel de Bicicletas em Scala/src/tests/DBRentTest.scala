package tests
import model._
import java.sql.{Date,Time}

object DBRentTest {
  def main(args: Array[String]){
    val rent1 = Rent(1, Date.valueOf("2017-07-20"), 1, 1, Time.valueOf("19:00:00"), Time.valueOf("20:00:00"), 3.4)
    val rent2 = Rent(2, Date.valueOf("2017-08-15"), 1, 1, Time.valueOf("17:00:00"), Time.valueOf("19:00:00"), 5.5)
    //DBManager.init()
    //RentDAO.create(rent1)
    //RentDAO.create(rent2)
    //RentDAO.delete(rent2)
    println(rent1.copy(client_id=2).client_id)
    RentDAO.update(rent1.copy(client_id=2))
    println(RentDAO.read(1).client_id)
  }
}