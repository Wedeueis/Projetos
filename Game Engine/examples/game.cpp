#include "../src/app/application.h"
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
	Sprite *m_Sprite;
	Shader *m_Shader;
	float m_Gain;
public:
	Game(): App("SGE", {960, 540, false, false} ){

	}
	~Game(){
	}

	void init() override{
		app = &getApplication();

		m_Shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

		Layer *background = new Layer("Background", new Batch2DRenderer(), m_Shader, math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
		Layer *gui = new Layer("GUI", new Batch2DRenderer(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
		Layer *objs = new Layer("Objects", new Batch2DRenderer(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	    for(float y=0.0f; y<9.0f; y+=0.5f){
        	for(float x=0.0f; x<16.0f; x+=0.5f){
            	background->add(new Sprite(x,y,0.48f,0.48f,BLUE_70));         
        	}
    	}

	    FontManager::add(new Font("SourceSansPro", "resources/fonts/SourceSansPro-Light.ttf", 32));
    	FontManager::add(new Font("LuckiestGuy", "resources/fonts/LuckiestGuy.ttf", 48));
    	
    	FontManager::get("SourceSansPro")->setScale(window->getWidth()/16.0f, window->getHeight()/9.0f);
    	FontManager::get("LuckiestGuy")->setScale(window->getWidth()/16.0f, window->getHeight()/9.0f);

    	SoundManager::add(new Sound("test","resources/audios/test.ogg"));
    	m_Gain = 0.5f;

	    Group *g = new Group(math::mat4::translate(math::vec3(0.0f, 7.5f, 0.0f)));
	    m_Fps = new Label("fps", 0.5f, 0.5f, FontManager::get("SourceSansPro"), WHITE);
	    g->add(new Sprite(0.2f, 0.2f, 2.2f, 0.95f, BLUE_GREY_60));
	    g->add(m_Fps);

	   	Group *g2 = new Group(math::mat4::translate(math::vec3(5, 7.5, 0.0f)));
    	g2->add(new Sprite(0, 0, 5.5f, 0.95f, WHITE_50));
    	g2->add(new Label("Hello World!", 0.2f, 0.2f, FontManager::get("LuckiestGuy"), YELLOW));

	    gui->add(g);
    	gui->add(g2);

    	std::string panelName("resources/images/panel.png");
    	Panel *panel = new Panel(Rectangle(13.5f,5.0f,2.0f,2.5f), panelName);

        std::string subpanelName("resources/images/subpanel.png");
    	Panel *subpanel = new Panel(Rectangle(0.0f,1.0f,1.5f,1.5f), subpanelName);
    	panel->add(subpanel);

    	Rectangle playRect(-0.9f,-0.8f,0.6f,0.6f);
    	std::string playUnpressed("resources/images/playUnpressed.png");
    	std::string playPressed("resources/images/playPressed.png");
    	std::string playFocused("resources/images/playFocused.png");
    	Button* play = new Button("Button", playRect, playUnpressed, playPressed, playFocused, buttonactionplay);
    	panel->add(play);

    	Rectangle pauseRect(0.0f,-0.8f,0.35f,0.35f);
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

    	m_Sprite = new Sprite(7.0,4.0,1.0f,1.0f,new Texture("smile","resources/images/smile.png"));
    	objs->add(m_Sprite);

    	app->pushLayer(background);
    	app->pushLayer(objs);
    	app->pushLayer(gui);
	}

	void onTick() override {
		m_Fps->text = std::to_string(getFPS()) + " fps";
		std::cout << "fps " << getFPS() << ", ups " << getUPS() << std::endl;

	}

	void onUpdate() override{

		float speed = 0.05f;

		if(window->getInputManager()->isKeyPressed(GLFW_KEY_UP))
			m_Sprite->setPosition(math::vec2(m_Sprite->getPosition().x, m_Sprite->getPosition().y + speed));
		else if(window->getInputManager()->isKeyPressed(GLFW_KEY_DOWN))
			m_Sprite->setPosition(math::vec2(m_Sprite->getPosition().x, m_Sprite->getPosition().y - speed));
		if(window->getInputManager()->isKeyPressed(GLFW_KEY_LEFT))
			m_Sprite->setPosition(math::vec2(m_Sprite->getPosition().x - speed, m_Sprite->getPosition().y));
		else if(window->getInputManager()->isKeyPressed(GLFW_KEY_RIGHT))
			m_Sprite->setPosition(math::vec2(m_Sprite->getPosition().x + speed, m_Sprite->getPosition().y));

		if(window->getInputManager()->isKeyPressed(GLFW_KEY_W)){
              m_Gain += 0.1f;
              SoundManager::get("test")->setGain(m_Gain);
              std::cout << "Volume: " << m_Gain << std::endl;
        }else if(window->getInputManager()->isKeyPressed(GLFW_KEY_Q)){
              m_Gain -= 0.1f;
              SoundManager::get("test")->setGain(m_Gain);
              std::cout << "Volume: " << m_Gain << std::endl;
        }

		double x = window->getInputManager()->getMousePosition().x;
		double y = window->getInputManager()->getMousePosition().y;
        m_Shader->enable();
        m_Shader->setUniform2f("light_pos", math::vec2((float)(x*16.0f/window->getWidth()), (float)(9.0f-y*9.0f/window->getHeight())));

	}

	void onRender() override{

		App::onRender();
		
		if(window->getInputManager()->isKeyPressed(GLFW_KEY_P)){
          SoundManager::get("test")->play(false);
        }else if(window->getInputManager()->isKeyPressed(GLFW_KEY_S)){
          SoundManager::get("test")->stop();
        }else if(window->getInputManager()->isKeyPressed(GLFW_KEY_U)){
          SoundManager::get("test")->pause();
        }


	}
};

int main(){
	Game game;
	game.start();
    return 0;
}