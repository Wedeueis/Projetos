#include "object.h"

namespace sge { namespace entity{

	Object::Object(graphics::Sprite *sprite): m_Sprite(sprite) {
		init();
	}

	Object::~Object(){
		delete m_Sprite;
		delete m_Body;
	}

	void Object::init(){
		const float w = m_Sprite->getBoundBox().size.x;
		const float h  =  m_Sprite->getBoundBox().size.y;
		const float x = m_Sprite->getBoundBox().position.x;
		const float y = m_Sprite->getBoundBox().position.y;

		m_Body = new physics::Body(physics::Body::Type::Static, x, y, w, h);
	}

	void Object::onUpdate(){

		m_Body->onUpdate();
		math::vec2 pos = m_Body->getPosition();

		m_Sprite->setPosition(math::vec3(pos));
	}

	void Object::onEvent(events::Event& event) {
	}

} }