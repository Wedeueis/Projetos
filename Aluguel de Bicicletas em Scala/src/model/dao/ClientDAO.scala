package model

object ClientDAO{
  
  def create(c: Client){
    val sql = "INSERT INTO clients(name, user, password, cpf, email, credits) VALUES(?,?,?,?,?,?);"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, c.name)
      stmt.setString(2, c.user)
      stmt.setString(3, c.password)
      stmt.setString(4, c.cpf)
      stmt.setString(5, c.email)
      stmt.setDouble(6, c.credits)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def read(user: String): Client = {
    val sql = "SELECT client_id, name, password, cpf, email, credits FROM clients WHERE user=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, user)
      val rs = stmt.executeQuery();
                 
      if(rs.next()){
        val id = rs.getInt("client_id");
        val name = rs.getString("name");
        val password = rs.getString("password");
        val cpf = rs.getString("cpf");
        val email = rs.getString("email");
        val creditos = rs.getFloat("credits");
        val client = Client(id,name, user, password, cpf, email, creditos)
        rs.close();
			  stmt.close();
			  connection.close()
			  client        
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
  
  def update(c: Client){
    val sql = "UPDATE clients SET name=?, password=?, cpf=?, email=?, credits=? WHERE user=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, c.name)
      stmt.setString(2, c.password)
      stmt.setString(3, c.cpf)
      stmt.setString(4, c.email)
      stmt.setDouble(5, c.credits)
      stmt.setString(6, c.user)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def delete(c: Client){
    val sql = "DELETE FROM clients WHERE user=?"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setString(1, c.user)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
}