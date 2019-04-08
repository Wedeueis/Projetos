#include "entity.h"

namespace sge { namespace entity {

	using namespace component;

	Entity::Entity() {
	}

	Entity::Entity(graphics::Sprite* sprite, const math::mat4& transform) {
		addComponent(new SpriteComponent(sprite));
		addComponent(new TransformComponent(transform));
	}

	void Entity::addComponent(component::Component* component) {
		m_Components[component->getType()] = component;
	}

} }