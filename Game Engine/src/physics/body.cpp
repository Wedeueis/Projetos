#include "body.h"
#include "../graphic/renderable/scene.h"

namespace sge{ namespace physics {

	Body::Body(Type type, float x, float y, float width, float height)
		:m_Type(type), m_Position(math::vec3(x,y,0)), m_Size(math::vec2(width, height)) {
			
			  b2BodyDef bodyDef;
			  switch(m_Type){
			  	case Type::Static:{
			  		bodyDef.type = b2_staticBody;
			  		break;
			  	}case Type::Dynamic:{
			  		bodyDef.type = b2_dynamicBody;
			  		break;
			  	}case Type::Kinematic:{
			  		bodyDef.type = b2_kinematicBody;
			  		break;
			  	}
			  }
			  vec3 pos = screenToWorld(m_Position);
			  bodyDef.position.Set(pos.x, pos.y);
			  bodyDef.angle = 0;
			  body = graphics::Scene::world->CreateBody(&bodyDef);
			  b2PolygonShape boxShape;
			  boxShape.SetAsBox(width,height);
			  
			  b2FixtureDef boxFixtureDef;
			  boxFixtureDef.shape = &boxShape;
			  boxFixtureDef.density = 1;
			  body->CreateFixture(&boxFixtureDef);
	}

	Body::~Body(){
		body->GetWorld()->DestroyBody( body );
	}

	void Body::onUpdate(){
		vec3 pos = worldToScreen(vec3(body->GetPosition().x, body->GetPosition().y, 0));
		m_Position.x = pos.x;
		m_Position.y = pos.y;
	}

} }