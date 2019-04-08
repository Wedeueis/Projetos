#include "spritesheet.h"

namespace sge { namespace graphics{

		SpriteSheet::SpriteSheet(int columns, int rows){
			float xRate = 1.0f/columns;
			float yRate = 1.0f/rows;
			int x = 0, y = 0;
			for(int i = 0; i<rows; i++)
				for(int j = 0; j<columns; j++){
					Sprite::Tex_Coord uvs = {											
						math::vec2(j*xRate, i*yRate),
						math::vec2(j*xRate, i*yRate + yRate),
						math::vec2(j*xRate + xRate, i*yRate + yRate),
						math::vec2(j*xRate + xRate, i*yRate)
					};
					m_Uvs.push_back(uvs);
				}


		}

		SpriteSheet::~SpriteSheet(){}

} }