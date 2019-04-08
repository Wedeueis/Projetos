#include "widget.h"
#include "component.h"

namespace sge { namespace graphics { namespace gui {

	Widget::Widget(const math::Rectangle& bounds)
		: m_Bounds(bounds), m_Active(true), m_Focused(false) {
	}

	bool Widget::onMousePressed(events::MousePressedEvent& e) {
		return false;
	}

	bool Widget::onMouseReleased(events::MouseReleasedEvent& e) {
		return false;
	}

	bool Widget::onMouseMoved(events::MouseMovedEvent& e) {
		return false;
	}

	void Widget::onUpdate() {
	}

} } }