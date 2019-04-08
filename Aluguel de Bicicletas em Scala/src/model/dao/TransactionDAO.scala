package model

import java.sql.ResultSet

object TransactionDAO {
    def create(t: Transaction){
    val sql = "INSERT INTO transactions(t_date, t_type, client_id, value) VALUES(?,?,?,?);"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setDate(1, t.date)
      stmt.setInt(2, t.t_type)
      stmt.setInt(3, t.client_id)
      stmt.setDouble(4, t.value)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def read(id: Int): Transaction = {
    val sql = "SELECT t_date, t_type, client_id, value FROM transactions WHERE transaction_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, id)
      val rs = stmt.executeQuery();
                 
      if(rs.next()){
        val t_date = rs.getDate("t_date");
        val t_type = rs.getInt("t_type");
        val client = rs.getInt("client_id");
        val value = rs.getDouble("value");
        val transaction = Transaction(id, t_date, t_type, client, value)
        rs.close();
			  stmt.close();
			  connection.close()
			  transaction      
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
  
  def update(t: Transaction){
    val sql = "UPDATE transactions SET t_date=?, t_type=?, client_id=?, value=? WHERE transaction_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setDate(1, t.date)
      stmt.setInt(2, t.t_type)
      stmt.setInt(3, t.client_id)
      stmt.setDouble(4, t.value)
      stmt.setDouble(5, t.transaction_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def delete(t: Transaction){
    val sql = "DELETE FROM transactions WHERE transaction_id=?;"
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, t.transaction_id)
      stmt.execute();
			stmt.close();
			connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def listByClient(c: Client): List[Transaction] = {
    val sql = "SELECT * FROM transactions WHERE client_id=?;"
    
    def go(rs: ResultSet,l: List[Transaction]): List[Transaction] = {
      if(rs.next){
        val t_date = rs.getDate("t_date");
        val t_type = rs.getInt("t_type");
        val id = rs.getInt("transaction_id");
        val value = rs.getDouble("value");
        val transaction = Transaction(id, t_date, t_type, c.client_id, value)
        
			  go(rs, transaction::l) 
      }else l
    }
       
    try{
      val connection = DBManager.getConnection()
      val stmt = connection.prepareStatement(sql)
      stmt.setInt(1, c.client_id)
      val rs = stmt.executeQuery();
      val transactions = go(rs,List())
      rs.close()
			stmt.close();
			connection.close()
			transactions
    }catch{
      case e: Exception => e.printStackTrace
      null
    }       
  }
}