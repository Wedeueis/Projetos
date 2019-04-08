package model

object BookingDAO {
  def create(b: Booking){
    val sql = "INSERT INTO bookings(client_id, bike_id, booking_date, start) VALUES(?,?,?,?);"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, b.client_id)
      stmt.setInt(2, b.bike_id)
      stmt.setDate(3, b.date)
      stmt.setTime(4, b.start)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def read(id: Int): Booking = {
    val sql = "SELECT client_id, bike_id, booking_date, start FROM bookings WHERE booking_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, id)
      val rs = stmt.executeQuery();
                 
      if(rs.next()){
        val client = rs.getInt("client_id");
        val bike = rs.getInt("bike_id");
        val date = rs.getDate("booking_date");
        val start = rs.getTime("start");
        val booking = Booking(id, client, bike, date, start)
        rs.close();
			  stmt.close();
			  connection.close()
			  booking       
      }else{
        stmt.close();
			  connection.close()
			  null
      }

    }catch{
      case e: Exception => e.printStackTrace
      null
    }
  }
  
  def update(b: Booking){
    val sql = "UPDATE bookings SET client_id=?, bike_id=?, booking_date=?, start=? WHERE booking_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, b.client_id)
      stmt.setInt(2, b.bike_id)
      stmt.setDate(3, b.date)
      stmt.setTime(4, b.start)
      stmt.setInt(5, b.booking_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def delete(b: Booking){
    val sql = "DELETE FROM bookings WHERE booking_id=?"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, b.booking_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
}