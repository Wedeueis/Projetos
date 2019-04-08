#include "transformcomponent.h"

namespace sge { namespace entity { namespace component {

	TransformComponent::TransformComponent(const math::mat4& transform)
		: transform(transform) {
	}

} } }