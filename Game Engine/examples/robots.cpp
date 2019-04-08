#include "../src/graphic/renderable/scene.h"
#include "../src/gui/gui.h"

using namespace sge;
using namespace graphics;
using namespace audio;
using namespace gui;
using namespace math;
using namespace entity;

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
    std::vector<GameObject*> robots;
public:
	Game(): App("SGE", {960, 540, false, false} ){

	}
	~Game(){
	}

	void init() override{
		app = &getApplication();

        initFont();

        initScene();

        initGUI();

	}

	void onTick() override {
		m_Fps->text = std::to_string(getFPS()) + " fps";
		std::cout << "fps " << getFPS() << ", ups " << getUPS() << std::endl;

	}

	void onUpdate() override{

        if(App::getApplication().window->getInputManager()->isKeyPressed(GLFW_KEY_1)){
            robots[0]->setActive(true);
            robots[1]->setActive(false);
            robots[2]->setActive(false);
        }else if(App::getApplication().window->getInputManager()->isKeyPressed(GLFW_KEY_2)){
            robots[0]->setActive(false);
            robots[1]->setActive(true);
            robots[2]->setActive(false);
        }else if(App::getApplication().window->getInputManager()->isKeyPressed(GLFW_KEY_3)){
            robots[0]->setActive(false);
            robots[1]->setActive(false);
            robots[2]->setActive(true);
        }

        m_Scene->onUpdate();



		double x = window->getInputManager()->getMousePosition().x;
		double y = window->getInputManager()->getMousePosition().y;
        //m_Shader->enable();
        //m_Shader->setUniform2f("light_pos", math::vec2((float)(x*16.0f/window->getWidth()), (float)(9.0f-y*9.0f/window->getHeight())));

	}

	void onRender() override{
		App::onRender();
	}

    inline void initFont(){
        FontManager::add(new Font("SourceSansPro", "resources/fonts/SourceSansPro-Light.ttf", 32));
        FontManager::add(new Font("LuckiestGuy", "resources/fonts/LuckiestGuy.ttf", 48));
        
        FontManager::get("SourceSansPro")->setScale(window->getWidth()/16.0f, window->getHeight()/9.0f);
        FontManager::get("LuckiestGuy")->setScale(window->getWidth()/16.0f, window->getHeight()/9.0f);
    }

    inline void initGUI(){
        Layer *gui = new Layer("GUI", new Batch2DRenderer(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
        
        Group *g = new Group(math::mat4::translate(math::vec3(0.0f, 7.5f, 0.0f)));
        m_Fps = new Label("fps", 0.5f, 0.5f, FontManager::get("SourceSansPro"), WHITE);
        g->add(new Sprite(0.4f, 0.2f, 1.95f, 0.98f, BLUE_GREY_60));
        g->add(m_Fps);

        Group *g2 = new Group(math::mat4::translate(math::vec3(0.5f, 0.5f, 0.0f)));
        g2->add(new Sprite(0.05f, 0.05f, 5.3f, 0.92f, GREY));
        g2->add(new Label("SGE++ Engine!", 0.2f, 0.2f, FontManager::get("LuckiestGuy"), INDIGO));

        gui->add(g);
        gui->add(g2);

        app->pushLayer(gui);
    }

    inline void initScene(){

        m_Scene = new Scene(0.0f, 0.0f , 16.0f , 9.0f, new Texture("field",
                            "resources/images/field.png"));

        robots.push_back(new GameObject(new Sprite(2.0,4.0,1.2f,1.2f,new Texture("robot1",
                            "resources/images/robot1.png"))));   
        robots.push_back(new GameObject(new Sprite(2.0,4.0,1.2f,1.2f,new Texture("robot2",
                            "resources/images/robot1.png")))); 
        robots.push_back(new GameObject(new Sprite(2.0,4.0,1.2f,1.2f,new Texture("robot3",
                            "resources/images/robot1.png"))));        

        m_Scene->add(robots[0]);
        m_Scene->add(robots[1]);
        m_Scene->add(robots[2]);

        GameObject* ball = new GameObject(new Sprite(5.0,4.0,0.5f,0.5f,new Texture("ball",
                                "resources/images/ball.png")));
        ball->setActive(false);

        m_Scene->add(ball);

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