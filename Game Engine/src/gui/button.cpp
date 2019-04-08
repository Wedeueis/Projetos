#include "button.h"

namespace sge { namespace graphics { namespace gui {

	using namespace math;

	Button::Button(const std::string& label, const math::Rectangle& bounds, const ActionHandler& handler)
		: Widget(bounds), m_Label(label), m_ActionHandler(handler), m_State(ButtonState::UNPRESSED) {

		m_Font = FontManager::get("gui");

		hasTexture = false;
	}

	Button::Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, 
			const ActionHandler& handler): Widget(bounds), m_Label(label), m_ActionHandler(handler), 
	   		m_State(ButtonState::UNPRESSED) {

		m_Font = FontManager::get("gui");

		hasTexture = true;

		float posX = bounds.getMinimumBound().x;
		float posY = bounds.getMinimumBound().y;
		float w = (bounds.size*2.0f).x;
		float h = (bounds.size*2.0f).y;

		m_UnpressedSprite = new Sprite(posX, posY, w, h, new Texture(label, unpressed));
		m_PressedSprite = m_FocusedSprite = m_DisabledSprite = m_ActiveSprite = m_UnpressedSprite;


	}

	Button::Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, std::string pressed, 
				const ActionHandler& handler): Widget(bounds), m_Label(label), m_ActionHandler(handler), 
				m_State(ButtonState::UNPRESSED){

		m_Font = FontManager::get("gui");

		hasTexture = true;

		float posX = bounds.getMinimumBound().x;
		float posY = bounds.getMinimumBound().y;
		float w = (bounds.size*2.0f).x;
		float h = (bounds.size*2.0f).y;

		m_UnpressedSprite = new Sprite(posX, posY, w, h, new Texture(label, unpressed));
		m_PressedSprite = new Sprite(posX, posY, w, h, new Texture(label, pressed));
		m_FocusedSprite = m_DisabledSprite = m_ActiveSprite =  m_UnpressedSprite;
	}

	Button::Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, std::string pressed,
			std::string focused, const ActionHandler& handler): Widget(bounds), m_Label(label), m_ActionHandler(handler), 
			m_State(ButtonState::UNPRESSED){

		m_Font = FontManager::get("gui");

		hasTexture = true;

		float posX = bounds.getMinimumBound().x;
		float posY = bounds.getMinimumBound().y;
		float w = (bounds.size*2.0f).x;
		float h = (bounds.size*2.0f).y;

		m_PressedSprite = new Sprite(posX, posY, w, h, new Texture(label, pressed));
		m_UnpressedSprite= new Sprite(posX, posY, w, h, new Texture(label, unpressed));
		m_FocusedSprite = new Sprite(posX, posY, w, h, new Texture(label, focused));
		m_DisabledSprite = m_ActiveSprite = m_UnpressedSprite;
	}

	Button::Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, std::string pressed,
			std::string focused, std::string disabled, const ActionHandler& handler): Widget(bounds), m_Label(label), 
			m_ActionHandler(handler), m_State(ButtonState::UNPRESSED) {

		m_Font = FontManager::get("gui");

		hasTexture = true;

		float posX = bounds.getMinimumBound().x;
		float posY = bounds.getMinimumBound().y;
		float w = (bounds.size*2.0f).x;
		float h = (bounds.size*2.0f).y;

		m_PressedSprite = new Sprite(posX, posY, w, h, new Texture(label, pressed));
		m_UnpressedSprite = new Sprite(posX, posY, w, h, new Texture(label, unpressed));
		m_FocusedSprite = new Sprite(posX, posY, w, h, new Texture(label, focused));
		m_DisabledSprite = new Sprite(posX, posY, w, h, new Texture(label, disabled));
		m_ActiveSprite = m_UnpressedSprite;
	}

	bool Button::onMousePressed(events::MousePressedEvent& e) {
		vec2 mouse(e.getX() * (16.0f / App::getApplication().window->getWidth()), 9.0f - e.getY() * (9.0f / App::getApplication().window->getHeight()));
		if (m_Bounds.contains(mouse)){
			m_State = ButtonState::PRESSED;
			m_ActiveSprite = m_PressedSprite;
			return true;
			LOG("testebotao");
		}
		return false;
	}

	bool Button::onMouseReleased(events::MouseReleasedEvent& e) {
		vec2 mouse(e.getX() * (16.0f / App::getApplication().window->getWidth()), 9.0f - e.getY() * (9.0f / App::getApplication().window->getHeight()));
		if (m_State == ButtonState::PRESSED)
			onAction();

		if(!m_Bounds.contains(mouse)){
			m_State = ButtonState::UNPRESSED;
			m_ActiveSprite = m_UnpressedSprite;
		}else{
			m_State = ButtonState::FOCUSED;
			m_ActiveSprite = m_FocusedSprite;

		}
		return true;
	}

	bool Button::onMouseMoved(events::MouseMovedEvent& e) {
		vec2 mouse(e.getX() * (16.0f / App::getApplication().window->getWidth()), 9.0f - e.getY() * (9.0f / App::getApplication().window->getHeight()));
		if ( (m_State == ButtonState::PRESSED || m_State == ButtonState::FOCUSED)  && 
														!m_Bounds.contains(mouse)) {
			m_State = ButtonState::UNPRESSED;
			m_ActiveSprite = m_UnpressedSprite;
		}
  			
  		if (m_State == ButtonState::UNPRESSED && m_Bounds.contains(mouse)){
  			m_State = ButtonState::FOCUSED;
  			m_ActiveSprite = m_FocusedSprite;
  		}
		return false;
	}

	void Button::onEvent(events::Event& event) {
		events::EventDispatcher dispatcher(event);
		dispatcher.dispatch<events::MousePressedEvent>([this](events::MousePressedEvent& e) { return onMousePressed(e); });
		dispatcher.dispatch<events::MouseReleasedEvent>([this](events::MouseReleasedEvent& e) { return onMouseReleased(e); });
		dispatcher.dispatch<events::MouseMovedEvent>([this](events::MouseMovedEvent& e) { return onMouseMoved(e); });
	}

	void Button::onAction() {
		m_ActionHandler();
	}

	void Button::onUpdate() {
	}

	void Button::submit(Renderer2D* renderer) const {
		float horizontalPadding = 1.0f * 0.5f;

		if(hasTexture){
			if(m_ActiveSprite != NULL)
				m_ActiveSprite->submit(renderer);
		}else{
			renderer->drawRect(m_Bounds);
			uint bcolor = 0;
			if(m_State == ButtonState::PRESSED)
				bcolor = BLUE_GREY_SECONDARY;
			else if(m_State == ButtonState::UNPRESSED)
				bcolor = BLUE_GREY;
			else if(m_State == ButtonState::FOCUSED)
				bcolor = BLUE_GREY_ACCENT;

			renderer->fillRect(m_Bounds, bcolor);
			renderer->drawString(m_Label, m_Bounds.position - vec2(m_Bounds.width - horizontalPadding, m_Font->getHeight(m_Label) * 0.5f), *m_Font);
		}

	}

} } }