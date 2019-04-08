

import scalafxml.core.NoDependencyResolver
import scalafxml.core.FXMLView
import scalafx.application.JFXApp
import scalafx.Includes._
import scalafx.scene.Scene
import scalafx.stage.Stage.sfxStage2jfx

class MontaStage extends JFXApp{
   
   def montaS(url: String) {     
      val resource = getClass.getResource(url)
      val root = FXMLView(resource, NoDependencyResolver)    
      stage = new JFXApp.PrimaryStage() {
        title = url
        scene = new Scene(root)
      }
      stage.setResizable(false);
   }
}