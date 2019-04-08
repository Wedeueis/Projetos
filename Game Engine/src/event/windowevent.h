#pragma once

#include "event.h"
#include "../math/vec2.h"

namespace sge { namespace events {

	class ResizeWindowEvent : public Event {
	protected:
		math::vec2 m_Size;
	public:
		ResizeWindowEvent(unsigned int width, unsigned int height);

		inline const math::vec2& getSize() const { return m_Size; }
		inline const unsigned int getWidth() const { return m_Size.x; }
		inline const unsigned getHeight() const { return m_Size.y; }
	public:
		inline static Type getStaticType() { return Event::Type::WINDOW_RESIZE; }
	};

} }