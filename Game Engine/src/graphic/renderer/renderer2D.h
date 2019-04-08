#pragma once

#include <GL/glew.h>
#include <vector>
#include "../../font/fontmanager.h"
#include "../../math/maths.h"
#include "../../utils/colors.h"

#ifndef DEBUG
#define DEBUG
#define LOG(x) std::cout << x << std::endl;
#endif

namespace sge { namespace graphics{

	class Renderable2D;
	
	class Renderer2D {
	private:
		std::vector<math::mat4> m_TransformationStack;
	protected:
		Renderer2D(){
			m_TransformationStack.push_back(math::mat4::identity());
			m_TransformationBack = &m_TransformationStack.back();
		}
	public:
		const math::mat4 *m_TransformationBack;
	public:
		void push(const math::mat4& matrix, bool override = false){
			if(override){
				m_TransformationStack.push_back(matrix);
			}else{
				m_TransformationStack.push_back(m_TransformationStack.back()*matrix);
			}
			m_TransformationBack = &m_TransformationStack.back();
		}

		void pop(){
			//Todo - log this!
			if(m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();
			m_TransformationBack = &m_TransformationStack.back();
		}

		virtual void begin() {}
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void end() {}
		virtual void flush() = 0;

		virtual void drawLine(float x0, float y0, float x1, float y1, uint color = WHITE, float thickness = 0.02f) {}
		virtual void drawLine(const math::vec2& start, const math::vec2& end, uint color = WHITE, float thickness = 0.02f) {}
		virtual void drawRect(float x, float y, float width, float height, uint color = WHITE) {}
		virtual void drawRect(const math::vec2& position, const math::vec2& size, uint color = WHITE) {}
		virtual void drawRect(const math::Rectangle& rectangle, uint color = WHITE) {}
		virtual void drawString(const std::string &text, const math::vec2 &position, const Font &font = *FontManager::get(), unsigned int color = WHITE) {}

		virtual void fillRect(float x, float y, float width, float height, uint color = WHITE) {}
		virtual void fillRect(const math::vec2& position, const math::vec2& size, uint color = WHITE) {}
		virtual void fillRect(const math::Rectangle& rectangle, uint color = WHITE) {}
	};

} }