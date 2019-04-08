#include "animation.h"

namespace sge { namespace graphics{

	Animation::Animation(int firstFrame, bool lock): 
        m_SpriteSheet(new SpriteSheet(SPRITESHEET_COL, SPRITESHEET_ROW)), m_Frame(0) {
		addFrame(firstFrame);
	}

	Animation::~Animation() {}

	void Animation::addFrame(int indice) {
		m_Frames.push_back(m_SpriteSheet->getFramesUV(indice));
	}

	Sprite::Tex_Coord Animation::getNextFrameUV() {
        if(m_Time%10 == 0){
            m_Frame++;
            if(m_Frame >= m_Frames.size()){
                m_Frame = 0;
            }
        }

        m_Time++;

        if(m_Time>1000){
            m_Time = 0;
        }
        return m_Frames[m_Frame];
	}

}}