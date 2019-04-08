#pragma once

#include <string>

#include "widget.h"
#include "../font/fontmanager.h"
#include "../graphic/renderable/sprite.h"

namespace sge { namespace graphics { namespace gui {

	class Button : public Widget {
	public:
		using ActionHandler = std::function<void()>;
	private:
		enum class ButtonState {
			UNPRESSED, PRESSED, FOCUSED, DISABLED
		};
	protected:
		std::string m_Label;
		ButtonState m_State;
		ActionHandler m_ActionHandler;
		Font* m_Font;
		bool hasTexture;
		Sprite* m_PressedSprite;
		Sprite* m_UnpressedSprite;
		Sprite* m_FocusedSprite;
		Sprite* m_DisabledSprite;
		Sprite* m_ActiveSprite;
	public:
		Button(const std::string& label, const math::Rectangle& bounds, const ActionHandler& handler = &Button::noAction);

		Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, const ActionHandler& handler = 
			   &Button::noAction);

		Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, std::string pressed, 
			   const ActionHandler& handler = &Button::noAction);

		Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, std::string pressed,
			std::string focused, const ActionHandler& handler = &Button::noAction);

		Button(const std::string& label, const math::Rectangle& bounds, std::string unpressed, std::string pressed,
			std::string focused, std::string disabled, const ActionHandler& handler = &Button::noAction);

		bool onMousePressed(events::MousePressedEvent& e) override;
		bool onMouseReleased(events::MouseReleasedEvent& e) override;
		bool onMouseMoved(events::MouseMovedEvent& e) override;

		virtual void onEvent(events::Event& event) override;
		void onAction();
		virtual void onUpdate() override;

		virtual void submit(Renderer2D* renderer) const override;

		inline void setLabel(const std::string& label) { m_Label = label; }
		inline const std::string& getLabel() const { return m_Label; }

		inline void setFont(Font* font) { m_Font = font; }
		inline const Font& getFont() const { return *m_Font; }

		inline void setAction(const ActionHandler& action) { m_ActionHandler = action; }
	private:
		static void noAction() {}
	};


} } }