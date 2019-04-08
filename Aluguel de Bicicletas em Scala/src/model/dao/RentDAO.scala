package model

object RentDAO {
  def create(r: Rent){
    val sql = "INSERT INTO rents(rent_date, client_id, bike_id, start, finish, value) VALUES(?,?,?,?,?,?);"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setDate(1, r.date)
      stmt.setInt(2, r.client_id)
      stmt.setInt(3, r.bike_id)
      stmt.setTime(4, r.start)
      stmt.setTime(5, r.finish)
      stmt.setDouble(6, r.value)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def read(id: Int): Rent = {
    val sql = "SELECT rent_date, client_id, bike_id, start, finish, value FROM rents WHERE rent_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, id)
      val rs = stmt.executeQuery();
                 
      if(rs.next()){
        val date = rs.getDate("rent_date");
        val client = rs.getInt("client_id");
        val bike = rs.getInt("bike_id");
        val start = rs.getTime("start");
        val finish = rs.getTime("finish");
        val value = rs.getDouble("value");
        val rent = Rent(id, date, client, bike, start, finish, value)
        rs.close();
			  stmt.close();
			  connection.close()
			  rent       
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
  
  def update(r: Rent){
    val sql = "UPDATE rents SET rent_date=?, client_id=?, bike_id=?, start=?, finish=?, value=? WHERE rent_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setDate(1, r.date)
      stmt.setInt(2, r.client_id)
      stmt.setInt(3, r.bike_id)
      stmt.setTime(4, r.start)
      stmt.setTime(5, r.finish)
      stmt.setDouble(6, r.value)
      stmt.setInt(7, r.rent_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def delete(r: Rent){
    val sql = "DELETE FROM rents WHERE rent_id=?"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, r.rent_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
}