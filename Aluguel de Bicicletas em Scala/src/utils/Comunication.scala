package utils


case class Request(option: String, params: Map[String, String])

case class Response(status: Int=0, content: List[Map[String,String]]=List(), description: String="OK")
/*
 * Response Status
 * status 0 = OK
 * status -1 = error
 */
