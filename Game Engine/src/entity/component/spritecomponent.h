#pragma once

#include "component.h"
#include "../../graphic/renderable/sprite.h"

namespace sge { namespace entity { namespace component {

	class SpriteComponent : public Component {
	public:
		graphics::Sprite* sprite;
	public:
		SpriteComponent(graphics::Sprite* sprite);

		static ComponentType* getStaticType() {
			static ComponentType type({ "Sprite" });
			return &type;
		}

		inline virtual ComponentType* getType() const override { return getStaticType(); }
	};

} } }

