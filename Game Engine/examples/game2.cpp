#include "../src/graphic/renderable/scene.h"
#include "../src/gui/gui.h"

using namespace sge;
using namespace graphics;
using namespace audio;
using namespace gui;
using namespace math;

void buttonactionplay(){
	SoundManager::get("test")->play(false);
}

void buttonactionpause(){
	SoundManager::get("test")->pause();
}

void buttonactionstop(){
	SoundManager::get("test")->stop();
}
	
class Game: public App {
private:
	App* app;
	Label *m_Fps;
	float m_Gain;
    Scene* m_Scene;
    Animation *m_Anim;
public:
	Game(): App("SGE", {960, 540, false, false} ){

	}
	~Game(){
	}

	void init() override{
		app = &getApplication();

        initFont();

        initSound();
       
        initScene();

        initGUI();

	}

	void onTick() override {
		m_Fps->text = std::to_string(getFPS()) + " fps";
		std::cout << "fps " << getFPS() << ", ups " << getUPS() << std::endl;

	}

	void onUpdate() override{

		if(window->getInputManager()->isKeyPressed(GLFW_KEY_W)){
              m_Gain += 0.1f;
              SoundManager::get("test")->setGain(m_Gain);
              std::cout << "Volume: " << m_Gain << std::endl;
        }else if(window->getInputManager()->isKeyPressed(GLFW_KEY_Q)){
              m_Gain -= 0.1f;
              SoundManager::get("test")->setGain(m_Gain);
              std::cout << "Volume: " << m_Gain << std::endl;
        }

        m_Scene->onUpdate();

		double x = window->getInputManager()->getMousePosition().x;
		double y = window->getInputManager()->getMousePosition().y;
        //m_Shader->enable();
        //m_Shader->setUniform2f("light_pos", math::vec2((float)(x*16.0f/window->getWidth()), (float)(9.0f-y*9.0f/window->getHeight())));

	}

	void onRender() override{

		App::onRender();

		if(window->getInputManager()->isKeyPressed(GLFW_KEY_P)){
          SoundManager::get("test")->play(true);
        }else if(window->getInputManager()->isKeyPressed(GLFW_KEY_S)){
          SoundManager::get("test")->stop();
        }else if(window->getInputManager()->isKeyPressed(GLFW_KEY_U)){
          SoundManager::get("test")->pause();
        }


	}

    inline void initFont(){
        FontManager::add(new Font("SourceSansPro", "resources/fonts/SourceSansPro-Light.ttf", 32));
        FontManager::add(new Font("LuckiestGuy", "resources/fonts/LuckiestGuy.ttf", 48));
        
        FontManager::get("SourceSansPro")->setScale(window->getWidth()/16.0f, window->getHeight()/9.0f);
        FontManager::get("LuckiestGuy")->setScale(window->getWidth()/16.0f, window->getHeight()/9.0f);
    }

    inline void initSound(){
        m_Gain = 0.5f;
        SoundManager::add(new Sound("test","resources/audios/smw-sky.ogg"));
        SoundManager::add(new Sound("jump","resources/audios/smw_jump.wav"));
    }

    inline void initGUI(){
        Layer *gui = new Layer("GUI", new Batch2DRenderer(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
        
        Group *g = new Group(math::mat4::translate(math::vec3(0.0f, 7.5f, 0.0f)));
        m_Fps = new Label("fps", 0.5f, 0.5f, FontManager::get("SourceSansPro"), WHITE);
        g->add(new Sprite(0.2f, 0.2f, 2.2f, 0.95f, BLUE_GREY_60));
        g->add(m_Fps);

        Group *g2 = new Group(math::mat4::translate(math::vec3(0.5f, 0.5f, 0.0f)));
        g2->add(new Sprite(0, 0, 5.4f, 0.98f, GREY));
        g2->add(new Label("SGE++ Engine!", 0.2f, 0.2f, FontManager::get("LuckiestGuy"), INDIGO));

        gui->add(g);
        gui->add(g2);

        std::string panelName("resources/images/panel.png");
        Panel *panel = new Panel(Rectangle(13.0f,3.0f,2.0f,2.5f), panelName);

        std::string subpanelName("resources/images/subpanel.png");
        Panel *subpanel = new Panel(Rectangle(0.0f,1.0f,1.5f,1.5f), subpanelName);
        panel->add(subpanel);

        Rectangle playRect(-0.9f,-0.8f,0.6f,0.6f);
        std::string playUnpressed("resources/images/playUnpressed.png");
        std::string playPressed("resources/images/playPressed.png");
        std::string playFocused("resources/images/playFocused.png");
        Button* play = new Button("Button", playRect, playUnpressed, playPressed, playFocused, buttonactionplay);
        panel->add(play);

        Rectangle pauseRect(0.0f,-0.8f,0.4f,0.4f);
        std::string pauseUnpressed("resources/images/pauseUnpressed.png");
        std::string pausePressed("resources/images/pausePressed.png");
        std::string pauseFocused("resources/images/pauseFocused.png");
        Button* pause = new Button("Button", pauseRect, pauseUnpressed, pausePressed, pauseFocused, buttonactionpause);
        panel->add(pause);

        Rectangle stopRect(0.9f,-0.8f,0.4f,0.4f);
        std::string stopUnpressed("resources/images/stopUnpressed.png");
        std::string stopPressed("resources/images/stopPressed.png");
        std::string stopFocused("resources/images/stopFocused.png");
        Button* stop = new Button("Button", stopRect, stopUnpressed, stopPressed, stopFocused, buttonactionstop);
        panel->add(stop);

        gui->add(panel);

        gui->add(new Sprite(2.0,5.0,10.0f,3.5f,new Texture("title","resources/images/titulov.png")));

        app->pushLayer(gui);
    }

    inline void initScene(){

        m_Anim = new Animation(5,false);

        m_Scene = new Scene(0.0f, 0.0f , 16.0f , 9.0f, new Texture("background", "resources/images/background3.png"));        

        m_Scene->add(new entity::GameObject(new Sprite(0.0,2.8,1.5f,1.5f,new Texture("mario",
                            "resources/images/mariopequeno.png"))));

        m_Scene->add(new entity::Object(new Sprite(0.0,1.5,16.0f,0.45f,GREEN)));

        Layer *scenes = new Layer("Scenes", new Batch2DRenderer(), new Shader("src/shaders/basic.vert", 
            "src/shaders/basic.frag"), math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
        scenes->add(m_Scene);

        app->pushLayer(scenes);
    }
};

int main(){
	Game game;
	game.start();
    return 0;
}