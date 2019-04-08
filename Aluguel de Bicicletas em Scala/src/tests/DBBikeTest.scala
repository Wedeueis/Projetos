package tests

import model._

object DBBikeTest {
  def main(args: Array[String]){
    val bike1 = Bike(1,"corrida", 3.2, 0, 3, "Bike cara pra profissionais")
    val bike2 = Bike(2,"simples", 1.5, 0, 3, "Bike simples mais barata")
    DBManager.init()
    BikeDAO.create(bike1)
    BikeDAO.create(bike2)
    BikeDAO.delete(bike2)
    BikeDAO.update(bike2.copy(tax=5.5))
    println(BikeDAO.read(bike2.bike_id).tax)
  }
}