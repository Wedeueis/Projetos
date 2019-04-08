package tests

import model.Client
import model.ClientDAO
import model.DBManager

object DBCLientTest {
  def main(args: Array[String]){
    val client = Client(1,"Camila do Amaral Sass", "CamilaSass", "chocolate", "444.444.444-44", "csass@gmail.com", 0.0 )
    val client2 = Client(2, "Wedeueis Braz", "Wedeueis", "bala", "333.333.333-33", "ws@gmail.com", 12.0)
    DBManager.init()
    ClientDAO.create(client2)
    ClientDAO.create(client)
    ClientDAO.delete(client)
    ClientDAO.update(client2.copy(password="batata"))
    println(ClientDAO.read("Wedeueis").password)
  }
}