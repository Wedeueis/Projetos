#pragma once

#include "../../math/maths.h"

#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../buffers/vertexarray.h"
#include "../renderer/renderer2D.h"
#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../../event/events.h"

#define _DEBUG_DRAW 1

namespace sge { namespace graphics{
	struct VertexData
	{
		math::vec3 vertex;
		math::vec2 uv;
		float tid;
		unsigned int color;
	};

	class Renderable2D{
	protected:
		math::Rectangle m_Bounds;
		math::vec2 m_Position;
		math::vec2 m_Size;
		unsigned int m_Color;
		std::vector<math::vec2> m_UV;
		Texture *m_Texture;
		bool isVisible;
	protected:
		Renderable2D(){setUVDefaults();m_Texture = nullptr; isVisible = true;}
	public:
		Renderable2D(math::vec2 position, math::vec2 size, unsigned int color)
						: m_Position(position), m_Size(size), m_Color(color){

			m_Bounds = math::Rectangle(math::vec2(position.x + size.x/2, position.y + size.y/2), 
										math::vec2(size.x/2, size.y/2));
			setUVDefaults();
			m_Texture = nullptr;
			isVisible = true;
		}

		virtual ~Renderable2D(){}	

		virtual void submit(Renderer2D* renderer) const{
#if _DEBUG_DRAW
			renderer->drawRect(m_Bounds, GREEN);
#endif
			renderer->submit(this);
		}

		void setColor(unsigned int color){m_Color = color;}
		
		void setColor(const math::vec4 color){
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;
			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		virtual void onEvent(events::Event& event) {}
		virtual void onUpdate() {}

		inline const math::vec2 getPosition() const { return m_Position;}	
		inline const math::vec2 getSize() const { return m_Size;}
		inline const math::Rectangle getBoundBox() const { return m_Bounds;}
		inline const unsigned int getColor() const { return m_Color;}
		inline const std::vector<math::vec2>& getUV() const { return m_UV;}
		inline const GLuint getTID() const { return (m_Texture == nullptr) ? 0 : m_Texture->getID();}	
	private:
		void setUVDefaults(){
			m_UV.push_back(math::vec2(0, 0));
			m_UV.push_back(math::vec2(0, 1));
			m_UV.push_back(math::vec2(1, 1));
			m_UV.push_back(math::vec2(1, 0));
		}	
	};
}}