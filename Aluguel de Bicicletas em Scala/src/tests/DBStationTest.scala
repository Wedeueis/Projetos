package tests

import model._

object DBStationTest {
  def main(args: Array[String]){
    val station1 = Station(1,"UFABC", "Av. dos Estados, 2000, Santa Adélia, Santo André - SP")
    val station2 = Station(2,"Metrô Carrão", "Radial Leste, 5000, Tatuapé, São Paulo - SP")
    //DBManager.init()
    //StationDAO.create(station1)
    //StationDAO.create(station2)
    //StationDAO.delete(station2)
    StationDAO.update(station1.copy(name="Universidade Federal do ABC"))
    println(StationDAO.read(station1.station_id).name)
  }
}