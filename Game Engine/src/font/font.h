#pragma once

#include "../../ext/freetype-gl/include/freetype-gl.h"
#include "../math/maths.h"
#include "../math/rectangle.h"
#include <string>

namespace sge{ namespace graphics{

		class Font {
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			float m_Size;
			math::vec2 m_Scale;
			std::string m_Name;
			std::string m_Filename;
		public:
			Font(std::string name, std::string filename, int size);

			void setScale(float x, float y);

			inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
			inline ftgl::texture_atlas_t* getFTAtlas() const { return m_FTAtlas; }
			inline const math::vec2 getScale() const { return m_Scale; }
			inline const std::string getName() const { return m_Name; }
			inline const std::string getFileName() const { return m_Filename; }
			inline const float getSize() const { return m_Size; }
			inline const unsigned int getId() const { return m_FTAtlas->id; }

			math::vec2 getOffsets(const std::string& text) const;
			float getWidth(const std::string& text) const;
			float getHeight(const std::string& text) const;
			math::vec2 getSize(const std::string& text) const;

			math::Rectangle getBounds(const std::string& text) const;
		};

} }