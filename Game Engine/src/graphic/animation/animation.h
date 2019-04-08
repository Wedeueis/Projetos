#pragma once

#include "spritesheet.h"
#include <vector>

#define SPRITESHEET_COL 2
#define SPRITESHEET_ROW 2

namespace sge { namespace graphics{

	class Animation{
	private:
		SpriteSheet* m_SpriteSheet;
		std::vector<Sprite::Tex_Coord> m_Frames;
		int m_Frame;
		int m_Time;
		bool locked;
	public:
		Animation(int firstFrame, bool lock);
		~Animation();

		void addFrame(int indice);

		Sprite::Tex_Coord getNextFrameUV();

	};

}}