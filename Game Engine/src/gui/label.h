#pragma once

#include "../graphic/renderable/renderable2D.h"
#include "../font/fontmanager.h"

namespace sge { namespace graphics{

	class Label: public Renderable2D{
	public:
		Font* font;
		std::string text;
	public:
		Label(std::string text, float x, float y, unsigned int color);
		Label(std::string text, float x, float y, Font* font, unsigned int color);
		Label(std::string text, float x, float y, const std::string& font, unsigned int color);
		Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);

		void submit(Renderer2D* renderer) const override;
		void validateFont(const std::string fontname, int size = -1);
	};

} }