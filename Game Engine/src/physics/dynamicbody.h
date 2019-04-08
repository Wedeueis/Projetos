#pragma once

#include "body.h"

namespace sge { namespace physics {

	class DynamicBody: public Body {
	private:
		math::vec2 m_Speed;
	public:
		DynamicBody(float x, float y, float width, float height);
		~DynamicBody();

		void onUpdate() override;

		void setSpeed(math::vec2 speed);
	private:
		void applyImpulse(math::vec2 desiredVel);

	};

} }