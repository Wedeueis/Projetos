#include "robot.h"

namespace sge { namespace entity{

	Robot::Robot(graphics::Sprite *sprite): GameObject(sprite){
		init();
	}


	void Robot::init(){
		//GameObject::init();

		//WALKING_LEFT
		m_Animation.push_back(graphics::Animation(0, false));

		//WALKING_up
		m_Animation.push_back(graphics::Animation(1, false));

		//walking_RIGHT
		m_Animation.push_back(graphics::Animation(2, false));

		//WALKING_DOWN
		m_Animation.push_back(graphics::Animation(3, false));

		m_State = State::IDLE;

		m_Sprite->setUV(m_Animation[2].getNextFrameUV());
	}

	void Robot::onUpdate(){

		GameObject::onUpdate();

		if(active){
	        if(App::getApplication().window->getInputManager()->isKeyPressed(GLFW_KEY_RIGHT)){
				m_Speed.x = 5.0f;
				m_Sprite->setUV(m_Animation[2].getNextFrameUV());
	        }else if(App::getApplication().window->getInputManager()->isKeyPressed(GLFW_KEY_LEFT)){
				m_Speed.x = -5.0f;
				m_Sprite->setUV(m_Animation[0].getNextFrameUV());
	        }else{
	        	m_Speed.x = 0.0f;
	        }
	        
			if(App::getApplication().window->getInputManager()->isKeyPressed(GLFW_KEY_UP)){
				m_Speed.y = 5.0f;
				m_Sprite->setUV(m_Animation[1].getNextFrameUV());
			}else if(App::getApplication().window->getInputManager()->isKeyPressed(GLFW_KEY_DOWN)){
				m_Speed.y = -5.0f;
				m_Sprite->setUV(m_Animation[3].getNextFrameUV());
			}else{
				m_Speed.y = 0.0f;
			}
		}

	}

	void Robot::onEvent(events::Event& event) {
		events::EventDispatcher dispatcher(event);
		dispatcher.dispatch<events::KeyPressedEvent>([this](events::KeyPressedEvent& e) { return onKeyPressed(e); });
		dispatcher.dispatch<events::KeyReleasedEvent>([this](events::KeyReleasedEvent& e) { return onKeyReleased(e); });
	}

	bool Robot::onKeyPressed(events::KeyPressedEvent& e) {
		int key = (int)e.getKeyCode();
		bool handled = false;

		if(active){
			switch(key){
				case GLFW_KEY_UP:{
					m_State = State::WALKING_UP;
					handled = true;
					break;
				}case GLFW_KEY_DOWN:{
					m_State = State::WALKING_DOWN;
					handled = true;
					break;
				}case GLFW_KEY_LEFT:{
					m_State = State::WALKING_LEFT;
					handled = true;
					break;
				}case GLFW_KEY_RIGHT:{
					m_State = State::WALKING_RIGHT;
					handled = true;
					break;
				}		
			}
		}
		return handled;
	}

	bool Robot::onKeyReleased(events::KeyReleasedEvent& e) {
		int key = e.getKeyCode();
		m_State = State::IDLE;
		return true;
	}


} }