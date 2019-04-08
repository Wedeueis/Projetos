#pragma once

#include "../../src/entity/gameobject.h"

namespace sge { namespace entity{

	class Robot: public GameObject {
	public:
		enum class State {
			IDLE,
			WALKING_RIGHT,
			WALKING_LEFT,
			WALKING_DOWN,
			WALKING_UP
		};
	private:
		State m_State;
	public:
		Robot(graphics::Sprite *sprite);
		~Robot(){}

		void init() override;
		void onUpdate() override;
		void onEvent(events::Event& event) override;
		bool onKeyPressed(events::KeyPressedEvent& e) override;
		bool onKeyReleased(events::KeyReleasedEvent& e) override;
	};

} }