#include "../src/graphic/window.h"
#include "../src/graphic/renderer/batch2Drenderer.h"
#include "../src/graphic/layers/group.h"
#include "../src/graphic/layers/layer.h"
#include "../src/graphic/renderable/sprite.h"
#include "../src/gui/label.h"
#include "../src/font/fontmanager.h"

#include "../src/audio/soundmanager.h"

#include "../src/math/maths.h"
#include "../src/utils/colors.h"

#include <time.h>
#include <thread>

int main() {
    using namespace sge;
    using namespace graphics;
    using namespace audio;
    using namespace math;

    Window window("SGE", 960, 540);
    glClearColor(0.0f,0.0f,0.0f,1.0f);

    Shader *shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

    Layer layer(new Batch2DRenderer(), shader , math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));


    Texture *textures[] = {
    	new Texture("resources/images/teste3.jpeg"),
   		new Texture("resources/images/teste3.jpeg"),
   		new Texture("resources/images/teste3.jpeg")
   	};

    for(float y=0.0f; y<9.0f; y+=0.5f){
        for(float x=0.0f; x<16.0f; x+=0.5f){
            layer.add(new Sprite(x,y,0.48f,0.48f,BLUE_70));         
        }
    }

    FontManager::add(new Font("SourceSansPro", "resources/fonts/SourceSansPro-Light.ttf", 32));
    FontManager::add(new Font("LuckiestGuy", "resources/fonts/LuckiestGuy.ttf", 48));

    FontManager::get("SourceSansPro")->setScale(window.getWidth()/16.0f, window.getHeight()/9.0f);
    FontManager::get("LuckiestGuy")->setScale(window.getWidth()/16.0f, window.getHeight()/9.0f);

    SoundManager::add(new Sound("test","resources/audios/test.ogg"));
    float gain = 0.5f;
    //SoundManager::get("test")->setGain(gain);

    Group *g = new Group(math::mat4::translate(math::vec3(0.0f, 7.5f, 0.0f)));
    Label *fps = new Label("fps", 0.5f, 0.5f, FontManager::get("SourceSansPro"), WHITE);
    g->add(new Sprite(0.2f, 0.2f, 2.2f, 0.95f, BLUE_GREY_40));
    g->add(fps);

    
    Group *g2 = new Group(math::mat4::translate(math::vec3(5, 4.5, 0.0f)));
    g2->add(new Sprite(0, 0, 5.5f, 0.95f, BLUE_GREY_80));
    g2->add(new Label("Hello World!", 0.2f, 0.2f, FontManager::get("LuckiestGuy"), AMBER));

    layer.add(g);
    layer.add(g2);

    while(!window.closed()){
        window.clear();
        double x, y;
        window.getMousePosition(x,y);
        shader->enable();
        shader->setUniform2f("light_pos", math::vec2((float)(x*16.0f/window.getWidth()), (float)(9.0f-y*9.0f/window.getHeight())));
        fps->text = "fps";

        layer.render();
        if(window.isKeyTyped(GLFW_KEY_P)){
          SoundManager::get("test")->play(false);
        }else if(window.isKeyTyped(GLFW_KEY_S)){
          SoundManager::get("test")->stop();
        }else if(window.isKeyTyped(GLFW_KEY_U)){
          SoundManager::get("test")->pause();
        }else if(window.isKeyTyped(GLFW_KEY_W)){
              gain += 0.1f;
              SoundManager::get("test")->setGain(gain);
              std::cout << "Volume: " << gain << std::endl;
        }else if(window.isKeyTyped(GLFW_KEY_Q)){
              gain -= 0.1f;
              SoundManager::get("test")->setGain(gain);
              std::cout << "Volume: " << gain << std::endl;
        }
       
        window.update();
    }
    return 0;
}