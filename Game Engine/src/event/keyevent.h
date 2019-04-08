#pragma once

#include "event.h"


namespace sge { namespace events {


	class KeyEvent : public Event {
	protected:
		unsigned int m_KeyCode;
		unsigned int m_Count;
	public:
		KeyEvent(unsigned int keyCode, Event::Type type);

		inline unsigned int getKeyCode() const { return m_KeyCode; }

		inline static unsigned int getStaticType() { return (unsigned int)Event::Type::KEY_PRESSED | (unsigned int)Event::Type::KEY_RELEASED; }
	};

	class KeyPressedEvent : public KeyEvent {
	private:
		unsigned int m_Repeat;
		unsigned int m_Modifiers;
	public:
		KeyPressedEvent(unsigned int button, unsigned int repeat, unsigned int modifiers);

		inline unsigned int getRepeat() const { return m_Repeat; }
		inline unsigned int getModifiers() const { return m_Modifiers; }
		inline bool isModifier(unsigned int modifier) const { return (bool)(m_Modifiers & modifier); }

		inline static Type getStaticType() { return Event::Type::KEY_PRESSED; }
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(unsigned int button);

		inline static Type getStaticType() { return Event::Type::KEY_RELEASED; }
	};

} }