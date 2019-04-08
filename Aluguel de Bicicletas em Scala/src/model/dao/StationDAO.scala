package model

object StationDAO {
    def create(s: Station){
    val sql = "INSERT INTO stations(name, adress) VALUES(?,?);"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, s.name)
      stmt.setString(2, s.adress)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def read(id: Int): Station = {
    val sql = "SELECT name, adress FROM stations WHERE station_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, id)
      val rs = stmt.executeQuery();
                 
      if(rs.next()){
        val name = rs.getString("name");
        val adress = rs.getString("adress");
        val station = Station(id, name, adress)
        rs.close();
			  stmt.close();
			  connection.close()
			  station    
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
  
  def update(s: Station){
    val sql = "UPDATE stations SET name=?, adress=? WHERE station_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, s.name)
      stmt.setString(2, s.adress)
      stmt.setInt(3, s.station_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def delete(s: Station){
    val sql = "DELETE FROM stations WHERE station_id=?"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, s.station_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
}