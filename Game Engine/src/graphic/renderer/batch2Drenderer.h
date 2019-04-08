#pragma once

#include "renderer2D.h"
#include "../renderable/renderable2D.h"
#include "../buffers/indexbuffer.h"
#include "../../math/rectangle.h"
#include <stddef.h>

namespace sge { namespace graphics{

#define RENDERER_MAX_SPRITES 	10000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE 	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE 	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE 	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES   32

#define SHADER_VERTEX_INDEX 	0
#define SHADER_UV_INDEX 		1
#define SHADER_TID_INDEX 		2
#define SHADER_COLOR_INDEX 		3


	class Batch2DRenderer: public Renderer2D {
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		GLsizei m_IndexCount;
		IndexBuffer* m_IBO;
		VertexData* m_Buffer;

		std::vector<GLuint> m_TextureSlots;
	public:
		Batch2DRenderer();
		~Batch2DRenderer();
		void begin() override;
		void submit(const Renderable2D* renderable) override;
		void end() override;
		void flush() override;

		void drawLine(float x0, float y0, float x1, float y1, uint color = WHITE, float thickness = 0.02f);
		void drawLine(const math::vec2& start, const math::vec2& end, uint color = WHITE, float thickness = 0.02f);
		void drawRect(float x, float y, float width, float height, uint color = WHITE);
		void drawRect(const math::vec2& position, const math::vec2& size, uint color = WHITE);
		void drawRect(const math::Rectangle& rectangle, uint color = WHITE);
		void drawString(const std::string &text, const math::vec2 &position, const Font &font = *FontManager::get(), unsigned int color = WHITE) override;

		void fillRect(float x, float y, float width, float height, uint color = WHITE);
		void fillRect(const math::vec2& position, const math::vec2& size, uint color = WHITE);
		void fillRect(const math::Rectangle& rectangle, uint color = WHITE);
	private:
		void init();
	};

} }