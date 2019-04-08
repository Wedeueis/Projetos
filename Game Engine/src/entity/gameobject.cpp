#include "gameobject.h"

namespace sge { namespace entity{

	GameObject::GameObject(graphics::Sprite *sprite): 
		Object(sprite) {

		init();

	}

	GameObject::~GameObject(){
		delete m_Sprite;
		delete m_Body;
	}

	void GameObject::init(){
		const float w = m_Sprite->getBoundBox().size.x;
		const float h  =  m_Sprite->getBoundBox().size.y;
		const float x = m_Sprite->getBoundBox().position.x;
		const float y = m_Sprite->getBoundBox().position.y;

		m_Body = new physics::DynamicBody(x, y, w, h);

		m_Speed = 0.00f;
	}

	void GameObject::onUpdate(){

		dynamic_cast<physics::DynamicBody*>(m_Body)->setSpeed(m_Speed);

		m_Body->onUpdate();
		math::vec2 pos = m_Body->getPosition();

		m_Sprite->setPosition(pos);

	}

	void GameObject::onEvent(events::Event& event) {

	}

	bool GameObject::onKeyPressed(events::KeyPressedEvent& e) {
	}

	bool GameObject::onKeyReleased(events::KeyReleasedEvent& e) {
	}

} }