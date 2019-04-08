#include "windowevent.h"

namespace sge { namespace events {

	ResizeWindowEvent::ResizeWindowEvent(unsigned int width, unsigned int height)
		: Event(ResizeWindowEvent::getStaticType()), m_Size(math::vec2(width, height))
	{
	}

} }