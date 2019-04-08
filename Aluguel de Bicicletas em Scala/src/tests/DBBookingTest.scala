package tests

import model._
import java.sql.{Date,Time}

object DBBookingTest {
  def main(args: Array[String]){
    val booking1 = Booking(1,1,1,Date.valueOf("2017-07-25"), Time.valueOf("15:00:00"))
    val booking2 = Booking(2,1,3,Date.valueOf("2017-07-25"), Time.valueOf("15:00:00"))
    //DBManager.init()
    //BookingDAO.create(booking1)
   // BookingDAO.create(booking2)
    //BookingDAO.delete(booking2)
    BookingDAO.update(booking1.copy(client_id=10))
    println(BookingDAO.read(1).client_id)
  }
}