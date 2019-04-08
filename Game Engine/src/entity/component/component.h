#pragma once

#include <string>

namespace sge { namespace entity {
	class Entity;
} }

namespace sge { namespace entity { namespace component {

	struct ComponentType {
		std::string name;
	};

	class Component {
	protected:
		Entity* m_Entity;
	public:
		virtual Entity* getEntity() { return m_Entity; }
		virtual ComponentType* getType() const { return nullptr; }
	};

} } }
