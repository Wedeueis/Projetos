#include "label.h"

namespace sge { namespace graphics{
	Label::Label(std::string text, float x, float y, unsigned int color)
		:Renderable2D(), text(text), font(FontManager::get("SourceSansPro")) {
			m_Bounds.position = math::vec2(x,y);
			m_Color = color;
	}

	Label::Label(std::string text, float x, float y, Font* font, unsigned int color)
		:Renderable2D(), text(text), font(font) {
			m_Bounds.position = math::vec2(x,y);
			m_Color = color;
	}

	Label::Label(std::string text, float x, float y, const std::string& font, unsigned int color)
		:Renderable2D(), text(text), font(FontManager::get(font)) {
			m_Bounds.position = math::vec2(x,y);
			m_Color = color;
			validateFont(font);
	}

	Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
		:Renderable2D(), text(text), font(FontManager::get(font, size)) {
			m_Bounds.position = math::vec2(x,y);
			m_Color = color;
			validateFont(font, size);
	}

	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(text, m_Bounds.position, *font, m_Color);
	}

	void Label::validateFont(const std::string fontname, int size) {
		if(font == nullptr){
			std::cout << "NULL FONT! Font: " << fontname;
			if(size > 0)
				std::cout << ", Size: " << size;
			std::cout <<". Loaded default font." << std::endl;

			font = FontManager::get("SourceSansPro");
		}
	}

} }