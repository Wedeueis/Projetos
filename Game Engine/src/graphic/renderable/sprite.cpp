#include "sprite.h"

namespace sge { namespace graphics{

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
	:Renderable2D(math::vec2(x,y), math::vec2(width, height), color) {
	}

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
	:Renderable2D(math::vec3(x,y), math::vec2(width, height), WHITE) {
	  	m_Texture = texture;
	}
	
} }