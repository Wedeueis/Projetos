#include "keyevent.h"

namespace sge { namespace events {

	KeyEvent::KeyEvent(unsigned int keyCode, Event::Type type)
		: Event(type), m_KeyCode(keyCode)
	{
	}

	KeyPressedEvent::KeyPressedEvent(unsigned int button, unsigned int repeat, unsigned int modifiers)
		: KeyEvent(button, KeyPressedEvent::getStaticType()), m_Repeat(repeat), m_Modifiers(modifiers)
	{
	}

	KeyReleasedEvent::KeyReleasedEvent(unsigned int button)
		: KeyEvent(button, KeyReleasedEvent::getStaticType())
	{
	}

} }