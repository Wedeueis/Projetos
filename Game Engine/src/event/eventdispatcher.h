#pragma once

#include "events.h"
#include <functional>

namespace sge { namespace events {

	class EventDispatcher {
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& event): m_Event(event) { }

		template<typename T>
		void dispatch(std::function<bool(T&)> func) {
			if ((unsigned int)m_Event.getType() == (unsigned int)T::getStaticType()){
					m_Event.m_Handled = func(*(T*)&m_Event);
				}
		}
	};

} }
