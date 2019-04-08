package model

import java.sql.{Connection, DriverManager}

object DBManager {
  
  def init(){
    createClientTable()
    createBikeTable()
    createRentTable()
    createTransactionTable()
    createBookingTable()
    createStationTable()
  }
  
  def getConnection():Connection = {
    try {
        // db parameters
        val url = "jdbc:sqlite:BikeRent.db"
        // create a connection to the database
        DriverManager.getConnection(url)              
    } catch {
        case e: Exception => e.printStackTrace
        null
    } 
  }
      
  def createClientTable(){
    val sql = "CREATE TABLE IF NOT EXISTS clients (client_id integer PRIMARY KEY," +
             "name text NOT NULL, user text NOT NULL, password text NOT NULL," +
             "cpf varchar(14) NOT NULL, email text NOT NULL, credits double);"
    try{
      val connection = getConnection()
      val stmt = connection.createStatement()
      stmt.executeUpdate(sql);
      stmt.close();
      connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
  
  def createBikeTable(){
    val sql = "CREATE TABLE IF NOT EXISTS bikes (bike_id integer PRIMARY KEY," +
             "model text NOT NULL, tax double NOT NULL, state integer NOT NULL," +
             "station_id integer NOT NULL, description text NOT NULL);"
    try{
      val connection = getConnection()
      val stmt = connection.createStatement()
      stmt.executeUpdate(sql);
      stmt.close();
      connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
    
  def createRentTable(){
    val sql = "CREATE TABLE IF NOT EXISTS rents (rent_id integer PRIMARY KEY," +
             "rent_date date NOT NULL, client_id integer NOT NULL, bike_id integer NOT NULL," +
             "start time NOT NULL, finish time NOT NULL, value double);"
    try{
      val connection = getConnection()
      val stmt = connection.createStatement()
      stmt.executeUpdate(sql);
      stmt.close();
      connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
      
  def createTransactionTable(){
    val sql = "CREATE TABLE IF NOT EXISTS transactions (transaction_id integer PRIMARY KEY," +
             "t_date date NOT NULL, t_type integer NOT NULL, client_id integer NOT NULL," +
             "value double);"
    try{
      val connection = getConnection()
      val stmt = connection.createStatement()
      stmt.executeUpdate(sql);
      stmt.close();
      connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
        
  def createBookingTable(){
    val sql = "CREATE TABLE IF NOT EXISTS bookings (booking_id integer PRIMARY KEY," +
             "client_id integer NOT NULL, bike_id integer NOT NULL, booking_date date NOT NULL, start time NOT NULL);"
    try{
      val connection = getConnection()
      val stmt = connection.createStatement()
      stmt.executeUpdate(sql);
      stmt.close();
      connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
          
  def createStationTable(){
    val sql = "CREATE TABLE IF NOT EXISTS stations (station_id integer PRIMARY KEY," +
             "name text NOT NULL, adress text NOT NULL);"
    try{
      val connection = getConnection()
      val stmt = connection.createStatement()
      stmt.executeUpdate(sql);
      stmt.close();
      connection.close()
    }catch{
      case e: Exception => e.printStackTrace
    }
  }
}