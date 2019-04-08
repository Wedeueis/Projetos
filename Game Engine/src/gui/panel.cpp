#include "panel.h"

#include "component.h"

namespace sge { namespace graphics { namespace gui {

	using namespace events;
	using namespace math;

	Panel::Panel(const math::Rectangle& bounds): Component(bounds), hasTexture(false){
		addTransformation(math::mat4::translate(math::vec3(bounds.x, bounds.y, 0.0f)));
	}

	Panel::Panel(const math::Rectangle& bounds, std::string sprite): Component(bounds), hasTexture(true){
		addTransformation(math::mat4::translate(math::vec3(bounds.x, bounds.y, 0.0f)));

		float posX = bounds.getMinimumBound().x;
		float posY = bounds.getMinimumBound().y;
		float w = (bounds.size*2.0f).x;
		float h = (bounds.size*2.0f).y;

		m_Sprite = new Sprite(posX, posY, w, h, new Texture("panel", sprite));
	}

	Panel::~Panel() {}

	void Panel::onEvent(events::Event& event) {
		events::EventDispatcher dispatcher(event);
		dispatcher.dispatch<events::MousePressedEvent>([this](events::MousePressedEvent& e) { return onMousePressed(e); });
		dispatcher.dispatch<events::MouseReleasedEvent>([this](events::MouseReleasedEvent& e) { return onMouseReleased(e); });
		dispatcher.dispatch<events::MouseMovedEvent>([this](events::MouseMovedEvent& e) { return onMouseMoved(e); });

		Component::onEvent(event);
		
		// TODO: Temporary fix
		//dispatcher.dispatch<ResizeWindowEvent>([this](events::ResizeWindowEvent& e) { return Layer::onResize(e.getWidth(), e.getHeight());  });
	}

	bool Panel::onMousePressed(events::MousePressedEvent& e) {
		return false;
	}

	bool Panel::onMouseReleased(events::MouseReleasedEvent& e) {
		return false;
	}

	bool Panel::onMouseMoved(events::MouseMovedEvent& e) {
		return false;
	}

	void Panel::submit(Renderer2D* renderer) const {

		if(hasTexture){
			m_Sprite->submit(renderer);
		}else{
			renderer->drawRect(m_Bounds);
			renderer->fillRect(m_Bounds, BLUE_GREY);
		}

		Component::submit(renderer);
	}

} } }