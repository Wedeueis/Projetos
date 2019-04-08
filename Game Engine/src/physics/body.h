#pragma once

#include "../../ext/box2d/include/Box2D.h"
#include "../math/maths.h"
#include "coordinates.h"

namespace sge{ namespace physics {

	class Body{
	public:
		enum class Type{
			Static,
			Dynamic,
			Kinematic
		};
	protected:
		b2Body *body;
		b2World *world;
		math::vec3 m_Position;
		math::vec2 m_Size;
		Type m_Type;
	public:
		Body(Type type, float x, float y, float width, float height);
		~Body();

		virtual void onUpdate();

		inline const math::vec3 getPosition() const { return m_Position; }
		inline const math::vec2 getSize() const { return m_Size; }
		inline const Type getType() const { return m_Type; }
	};

} }