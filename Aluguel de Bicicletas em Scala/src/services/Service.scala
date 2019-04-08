package services
import utils._

trait Service {
  def execute(req: Request): Response
}