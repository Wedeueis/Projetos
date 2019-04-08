#pragma once

#include "renderable2D.h"
#include "../../utils/colors.h"

namespace sge { namespace graphics{

	class Sprite: public Renderable2D {
	public:
		struct Tex_Coord {
			math::vec2 uv1;
			math::vec2 uv2;
			math::vec2 uv3;
			math::vec2 uv4;
		};
	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);

		inline void setPosition(math::vec2 pos) {
			m_Position = pos;
			m_Bounds.x = pos.x + m_Size.x/2;
			m_Bounds.y = pos.y + m_Size.y/2;
		}

		inline void setUV(Tex_Coord uvs) {
			m_UV.clear();
			m_UV.push_back(uvs.uv1);
			m_UV.push_back(uvs.uv2);
			m_UV.push_back(uvs.uv3);
			m_UV.push_back(uvs.uv4);
		}
	};

} }	