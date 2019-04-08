package services
import utils._

object ServiceProvider {
  def process(req: Request): Response = {
    val o = req.option
    val resp = o match {
      case "Login" => Authenticate.execute(req)
      case "Rentall" => Rentall.execute(req)
      case "Booking" => Book.execute(req)
      case "Credit" => Credit.execute(req)
      case "Payment" => Payment.execute(req)
      case "Transactions" => Transactions.execute(req)
      case "Balance" => Balance.execute(req)
      case "History" => null
      case "ForgotPassword" => null       
    }
    resp
  }
}