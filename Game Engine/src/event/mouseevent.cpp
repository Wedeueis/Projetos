#include "mouseevent.h"

namespace sge { namespace events {

	MouseButtonEvent::MouseButtonEvent(unsigned int button, float x, float y, Type type)
		: Event(type), m_Button(button), m_Position(math::vec2(x, y)) {
	}

	MousePressedEvent::MousePressedEvent(unsigned int button, float x, float y)
		: MouseButtonEvent(button, x, y, MousePressedEvent::getStaticType()) {
	}

	std::string MousePressedEvent::toString() const
	{
		char buffer[256];
		sprintf(buffer, "MouseReleasedEvent: (%d, %f, %f)", getButton(), getX(), getY());
		return std::string(buffer);
	}

	MouseReleasedEvent::MouseReleasedEvent(unsigned int button, float x, float y)
		: MouseButtonEvent(button, x, y, MouseReleasedEvent::getStaticType()) {
	}

	MouseMovedEvent::MouseMovedEvent(float x, float y)
		: Event(MouseMovedEvent::getStaticType()), m_Position(math::vec2(x, y)) {
	}

} }