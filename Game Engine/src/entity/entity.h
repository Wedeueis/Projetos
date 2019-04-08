#pragma once

#include "component/components.h"
#include <unordered_map>

namespace sge { namespace entity {

	class Entity {
	protected:
		std::unordered_map<component::ComponentType*, component::Component*> m_Components;
	public:
		Entity();
		Entity(graphics::Sprite* sprite, const math::mat4& transform = math::mat4::identity());

		void addComponent(component::Component* component);

		template <typename T>
		const T* getComponent() const {
			return getComponentInternal<T>();
		}

		template <typename T>
		T* getComponent() {
			return (T*)getComponentInternal<T>();
		}
	private:
		template <typename T>
		const T* getComponentInternal() const {
			component::ComponentType* type = T::getStaticType();
			auto it = m_Components.find(type);
			if (it == m_Components.end())
				return nullptr;
			return (T*)it->second; // TODO: ...
		}
	};

} }
