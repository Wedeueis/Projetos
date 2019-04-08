#pragma once

#include "../math/maths.h"
#include "../app/application.h"

#include "widget.h"

#include <algorithm>

namespace sge { namespace graphics { namespace gui {

	class Slider : public Widget {
	public:
		using ValueChangedCallback = std::function<void(float)>;
	private:
		enum class SliderState {
			UNPRESSED, PRESSED, PRESSEDHEAD
		};
	private:
		math::Rectangle m_HeadBounds;
		float m_Value;
		float m_HeadOffset;
		SliderState m_State;
		ValueChangedCallback m_Callback;
		bool m_Vertical;
	public:
		Slider(const math::Rectangle& bounds, bool vertical = false);
		Slider(const math::Rectangle& bounds, float value = 0.0f, const ValueChangedCallback& callback = &Slider::noCallback, bool vertical = false);

		bool onMousePressed(events::MousePressedEvent& e) override;
		bool onMouseReleased(events::MouseReleasedEvent& e) override;
		bool onMouseMoved(events::MouseMovedEvent& e) override;

		void onUpdate() override;
		virtual void submit(Renderer2D* renderer) const override;

		inline void setCallback(const ValueChangedCallback& callback) { m_Callback = callback; }
		inline const ValueChangedCallback& getCallback() const { return m_Callback; }

		inline float getValue() const { return m_Value; }
		void setValue(float value);
	private:
		static void noCallback(float) {}
	};

} } }