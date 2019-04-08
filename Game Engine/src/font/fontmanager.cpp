#include "fontmanager.h"


namespace sge { namespace graphics {

	std::vector<Font *> FontManager::m_Fonts;

	void FontManager::add(Font * font){
		m_Fonts.push_back(font);
	}

	Font* FontManager::get(){
		return m_Fonts[0];
	}

	Font* FontManager::get(int size){
		return get(m_Fonts[0]->getName(),size);
	}

	Font* FontManager::get(const std::string &name){
		for(Font *font: m_Fonts){
			if(font->getName() == name)
				return font;
		}
		//TODO: return default font instead of null
		return nullptr;
	}

	Font* FontManager::get(const std::string &name, unsigned int size){
		for(Font *font: m_Fonts){
			if(font->getSize() == size && font->getName() == name)
				return font;
		}
		//TODO: return default font instead of null
		return nullptr;
	}

	void FontManager::clean(){
		for(int i=0; i<m_Fonts.size(); i++)
			delete m_Fonts[i];
	}

} }