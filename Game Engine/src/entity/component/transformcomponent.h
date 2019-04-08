#pragma once

#include "component.h"
#include "../../math/maths.h"

namespace sge { namespace entity { namespace component {

	class TransformComponent : public Component {
	public:
		math::mat4 transform;
	public:
		TransformComponent(const math::mat4& transform);

		static ComponentType* getStaticType() {
			static ComponentType type({ "Transform" });
			return &type;
		}

		inline virtual ComponentType* getType() const override { return getStaticType(); }
	};

} } }