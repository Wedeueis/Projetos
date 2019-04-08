#pragma once

#include "../app/application.h"

#include <vector>
#include "../graphic/animation/animation.h"
#include "../physics/body.h"

namespace sge{namespace entity {

	class Object {
	protected:
		physics::Body *m_Body;
		graphics::Sprite *m_Sprite;
		std::vector<graphics::Animation> m_Animation;
	public:
		Object(graphics::Sprite *sprite);
		~Object();

		virtual void init();

		virtual void onUpdate();
		virtual void onEvent(events::Event& event);

		inline const graphics::Sprite* getSprite() const { return m_Sprite; }
	};

}}
