#pragma once

#include <string>
#include <GL/glew.h>
#include <FreeImage.h>
#include "../../utils/imageload.h"

namespace sge { namespace graphics{

	class Texture {
	private:
		std::string m_Filename;
		GLuint m_TID;
		GLsizei m_Width, m_Height;
		std::string m_Name;
	public:
		Texture(const std::string& name, const std::string& filename);
		~Texture();
		void bind() const;
		void unbind() const;

		inline const unsigned int getID() const {return m_TID;}
		inline const unsigned int getWidth() const {return m_Width;}
		inline const unsigned int getHeight() const {return m_Height;}
		inline std::string getName() const {return m_Name;}
	private:
		GLuint load();
	};
}}