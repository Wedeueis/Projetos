#pragma once

#include <vector>
#include <string>

#include "../../math/maths.h"
#include "../renderable/sprite.h"

namespace sge { namespace graphics{

	class SpriteSheet{


	private:
		std::vector<Sprite::Tex_Coord> m_Uvs;
		int m_Rows, m_Columns;

	public:
		SpriteSheet(int columns, int rows);
		~SpriteSheet();

		inline const Sprite::Tex_Coord  getFramesUV(int index) const { return m_Uvs[index]; }

	};

} }