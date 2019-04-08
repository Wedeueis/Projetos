#pragma once

#include "component.h"

namespace sge { namespace graphics { namespace gui {

	class Panel: public Component {
	private:
		bool hasTexture;
		Sprite *m_Sprite;
	public:
		Panel(const math::Rectangle& bounds);
		Panel(const math::Rectangle& bounds, std::string sprite);
		~Panel();

		void onEvent(events::Event& event) override;
		bool onMousePressed(events::MousePressedEvent& e);
		bool onMouseReleased(events::MouseReleasedEvent& e);
		bool onMouseMoved(events::MouseMovedEvent& e);

		void submit(Renderer2D* renderer) const override;
	};

} } }