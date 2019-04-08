#include "font.h"

namespace sge{ namespace graphics{

	Font::Font(std::string name, std::string filename, int size)
		:m_Name(name), m_Filename(filename), m_Size(size) {

		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
 		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str() );
 		glGenTextures(1, &m_FTAtlas->id );
	}

	void Font::setScale(float x, float y){
		m_Scale = math::vec2(x,y);
	}

	math::vec2 Font::getOffsets(const std::string& text) const{
		using namespace ftgl;

		if (text.empty())
			return math::vec2(0.0f, 0.0f);

		texture_glyph_t* glyph = texture_font_get_glyph(m_FTFont, &text[0]);

		float yo = 0.0f;
		const math::vec2& scale = m_Scale;
		for (int i = 0; i < text.size(); i++) {
			texture_glyph_t* glyph = texture_font_get_glyph(m_FTFont, &text[i]);
			float height = glyph->height / scale.y;
			float offset = glyph->offset_y / scale.y - height;
			if (offset < yo)
				yo = offset;
		}

		return math::vec2(glyph->offset_x / scale.x, yo);
	}

	float Font::getWidth(const std::string& text) const{
		using namespace ftgl;

		float width = 0.0f;
		const math::vec2& scale = m_Scale;
		for (int i = 0; i < text.size(); i++) {
			texture_glyph_t* glyph = texture_font_get_glyph(m_FTFont, &text[i]);
			if (i > 0)
			{
				float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
				width += kerning / scale.x;
			}
			width += glyph->advance_x / scale.x;
		}
		return width;
	}
	
	float Font::getHeight(const std::string& text) const{
		using namespace ftgl;

		const math::vec2& scale = m_Scale;
		float min = 0.0f;
		float max = 0.0f;
		for (int i = 0; i < text.size(); i++) {
			texture_glyph_t* glyph = texture_font_get_glyph(m_FTFont, &text[i]);
			float height = glyph->height / scale.y;
			float offset = glyph->offset_y / scale.y - height;
			if (offset < min)
				min = offset;
			if (height > max)
				max = height;
		}

		return std::abs(min) + std::abs(max);
	}
	
	math::vec2 Font::getSize(const std::string& text) const{
		return math::vec2(getWidth(text), getHeight(text));
	}
	

	math::Rectangle Font::getBounds(const std::string& text) const{
		return math::Rectangle(0.0f, 0.0f, getWidth(text), getHeight(text));
	}
	

} }
