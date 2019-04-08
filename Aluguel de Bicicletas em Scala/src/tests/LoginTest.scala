package tests

import services._
import utils._

object LoginTest {
  def main(args: Array[String]){
    val resp = ServiceProvider.process(Request("Login", Map("user"-> "Wedeueis", "password" -> "bala") ) )
    println(resp.description)
  }
}