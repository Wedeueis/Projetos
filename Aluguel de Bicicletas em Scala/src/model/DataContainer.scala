package model
import java.sql.{Date, Time}

case class Bike(bike_id: Int, model: String, tax: Double, state: Int, station_id: Int, description: String )

case class Client(client_id: Int, name: String, user: String, password: String, 
                  cpf: String, email: String, credits: Double)
                  
case class Rent(rent_id: Int, date: Date, client_id: Int, bike_id: Int, start: Time, finish: Time, value: Double)

case class Booking(booking_id: Int, client_id: Int, bike_id: Int, date: Date, start: Time)

case class Transaction(transaction_id: Int, date: Date, t_type: Int, client_id: Int, value: Double)

case class Station(station_id: Int, name: String, adress: String)