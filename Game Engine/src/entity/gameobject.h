#pragma once

#include "object.h"
#include "../physics/dynamicbody.h"

namespace sge { namespace entity{

	class GameObject: public Object {
	protected:
		math::vec2 m_Speed;
		bool active;
	public:
		GameObject(graphics::Sprite *sprite);
		~GameObject();

		virtual void init() override;

		virtual void onUpdate() override;
		virtual void onEvent(events::Event& event) override;

		virtual bool onKeyPressed(events::KeyPressedEvent& e);
		virtual bool onKeyReleased(events::KeyReleasedEvent& e);

		inline void setActive(bool act) { active = act; }
		inline void setSpeed(math::vec2 speed) { m_Speed = speed; }
		inline const math::vec2 getSpeed() const { return m_Speed; }

	};
}}