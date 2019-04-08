package model

object BikeDAO {
  def create(b: Bike){
    val sql = "INSERT INTO bikes(model, tax, state, station_id, description) VALUES(?,?,?,?,?);"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, b.model)
      stmt.setDouble(2, b.tax)
      stmt.setInt(3, b.state)
      stmt.setInt(4, b.station_id)
      stmt.setString(5, b.description)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def read(id: Int): Bike = {
    val sql = "SELECT model, tax, state, station_id, description FROM bikes WHERE bike_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, id)
      val rs = stmt.executeQuery();
                 
      if(rs.next()){
        val model = rs.getString("model");
        val tax = rs.getDouble("tax");
        val state = rs.getInt("state");
        val station = rs.getInt("station_id");
        val description = rs.getString("description");
        val bike = Bike(id, model, tax, state, station, description)
        rs.close();
			  stmt.close();
			  connection.close()
			  bike        
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
  
  def update(b: Bike){
    val sql = "UPDATE bikes SET model=?, tax=?, state=?, station_id=?, description=? WHERE bike_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, b.model)
      stmt.setDouble(2, b.tax)
      stmt.setInt(3, b.state)
      stmt.setInt(4, b.station_id)
      stmt.setString(5, b.description)
      stmt.setInt(6, b.bike_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def delete(b: Bike){
    val sql = "DELETE FROM bikes WHERE bike_id=?"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, b.bike_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
}