#pragma once

#include "event.h"
#include "../math/vec2.h"

namespace sge { namespace events {

	class MouseButtonEvent : public Event {
	protected:
		unsigned int m_Button;
		math::vec2 m_Position;
	protected:
		MouseButtonEvent(unsigned int button, float x, float y, Event::Type type);
	public:
		inline const unsigned int getButton() const { return m_Button; }
		inline const float getX() const { return m_Position.x; }
		inline const float getY() const { return m_Position.y; }
		inline const math::vec2& getPosition() const { return m_Position; }

		inline static unsigned int getStaticType() { return (unsigned int)Event::Type::MOUSE_PRESSED | (unsigned int)Event::Type::MOUSE_RELEASED; }
	};

	class MousePressedEvent : public MouseButtonEvent {
	public:
		MousePressedEvent(unsigned int button, float x, float y);

		std::string toString() const override;

		inline static Type getStaticType() { return Event::Type::MOUSE_PRESSED; }
	};

	class MouseReleasedEvent : public MouseButtonEvent{
	public:
		MouseReleasedEvent(unsigned int button, float x, float y);

		inline static Type getStaticType() { return Event::Type::MOUSE_RELEASED; }
	};

	class MouseMovedEvent : public Event {
	private:
		math::vec2 m_Position;
	public:
		MouseMovedEvent(float x, float y);

		inline const float getX() const { return m_Position.x; }
		inline const float getY() const { return m_Position.y; }
		inline const math::vec2& getPosition() const { return m_Position; }

		inline static Type getStaticType() { return Event::Type::MOUSE_MOVED; }
	};

} }