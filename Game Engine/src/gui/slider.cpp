#include "slider.h"

namespace sge { namespace graphics { namespace gui {

	using namespace math;

	Slider::Slider(const math::Rectangle& bounds, bool vertical)
		: Widget(bounds), m_Value(0.0f), m_State(SliderState::UNPRESSED), m_HeadOffset(0.0f),
		m_Callback(&Slider::noCallback), m_Vertical(vertical) {

		float size = vertical ? bounds.width : bounds.height;
		m_HeadBounds = Rectangle(bounds.x, bounds.y, size, size);
	}

	Slider::Slider(const math::Rectangle& bounds, float value, const ValueChangedCallback& callback, bool vertical)
		: Widget(bounds), m_Value(value), m_State(SliderState::UNPRESSED), m_HeadOffset(0.0f),
		m_Callback(callback), m_Vertical(vertical) {

		float size = vertical ? bounds.width : bounds.height;
		m_HeadBounds = Rectangle(bounds.x, bounds.y, size, size);
	}

	bool Slider::onMousePressed(events::MousePressedEvent& e) {
		vec2 mouse(e.getX() * (16.0f / App::getApplication().window->getWidth()), 9.0f - e.getY() * (9.0f / App::getApplication().window->getHeight()));
		if (m_HeadBounds.contains(mouse)) {
			m_State = SliderState::PRESSEDHEAD;
			m_HeadOffset = m_Vertical ? (mouse.y - m_HeadBounds.y) : (mouse.x - m_HeadBounds.x);
		} else {
			m_State = SliderState::PRESSED;
		}
		return true;
	}

	bool Slider::onMouseReleased(events::MouseReleasedEvent& e) {
		m_State = SliderState::UNPRESSED;
		return true;
	}

	bool Slider::onMouseMoved(events::MouseMovedEvent& e) {
		vec2 mouse(e.getX() * (16.0f / App::getApplication().window->getWidth()), 9.0f - e.getY() * (9.0f / App::getApplication().window->getHeight()));
		if (m_State == SliderState::PRESSEDHEAD) {
			if (m_Vertical)
				setValue((mouse.y - m_Bounds.getMinimumBound().y - m_HeadOffset) / (m_Bounds.getMaximumBound().y));
			else
				setValue((mouse.x - m_Bounds.getMinimumBound().x - m_HeadOffset) / (m_Bounds.getMaximumBound().x));
		}

		return false;
	}

	void Slider::onUpdate() {
		if (!Input::isMouseButtonPressed(SGE_MOUSE_LEFT))
			m_State = SliderState::UNPRESSED;

		if (m_Vertical)
			m_HeadBounds.y = m_Bounds.getMinimumBound().y + m_HeadBounds.height + m_Value * (m_Bounds.height * 2.0f - m_HeadBounds.height * 2.0f);
		else
			m_HeadBounds.x = m_Bounds.getMinimumBound().x + m_HeadBounds.width + m_Value * (m_Bounds.width * 2.0f - m_HeadBounds.width * 2.0f);
	}

	void Slider::submit(Renderer2D* renderer) const {
		renderer->fillRect(m_Bounds, 0xcf7f7f7f);
		renderer->drawRect(m_Bounds);

		renderer->fillRect(m_HeadBounds, 0xcfbfbfbf);
		renderer->drawRect(m_HeadBounds);

		vec2 offset = m_Vertical ? vec2(0, m_Bounds.size.y) : vec2(m_Bounds.size.x, 0);
		renderer->drawLine(m_Bounds.position - offset, m_Bounds.position + offset);
	}

	void Slider::setValue(float value) {
		value = math::clamp(value, 0.0f, 1.0f);
		m_Value = value;
		m_Callback(value);
	}

} } }