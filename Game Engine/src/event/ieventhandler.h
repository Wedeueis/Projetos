#pragma once

#include "event.h"

namespace sge { namespace events {

	class IEventHandler {
	public:
		virtual void onEvent(Event& event) = 0;
	};

} }