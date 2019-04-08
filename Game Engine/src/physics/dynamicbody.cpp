#include "dynamicbody.h"

namespace sge { namespace physics {

	DynamicBody::DynamicBody(float x, float y, float width, float height)
	:Body(Type::Dynamic, x, y, width, height) {
		m_Speed = math::vec2(0,0);
	}

	DynamicBody::~DynamicBody(){}

	void DynamicBody::onUpdate() {

		Body::onUpdate();
	}

	void DynamicBody::setSpeed(math::vec2 speed){
		applyImpulse(speed);
	}

	void DynamicBody::applyImpulse(math::vec2 desiredVel){
		b2Vec2 vel = body->GetLinearVelocity();
	    float velChangeX = desiredVel.x - vel.x;
	    float velChangeY = desiredVel.y - vel.y;
	    float impulseX = body->GetMass() * velChangeX;
	    float impulseY = body->GetMass() * velChangeY;
	    body->ApplyLinearImpulse( b2Vec2(impulseX,impulseY), body->GetWorldCenter(), true);
	}

} }