#include "batch2Drenderer.h"



namespace sge { namespace graphics{

	using namespace math;

	Batch2DRenderer::Batch2DRenderer(){
		init();
	}

	Batch2DRenderer::~Batch2DRenderer(){
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Batch2DRenderer::init(){
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE,(const GLvoid*) (offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE,(const GLvoid*) (offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*) (offsetof(VertexData, VertexData::color)));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		int offset = 0;
		GLushort* indices = new GLushort[RENDERER_INDICES_SIZE];

		for(int i=0; i< RENDERER_INDICES_SIZE; i+=6){
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		glBindVertexArray(0);
	}

	void Batch2DRenderer::submit(const Renderable2D* renderable){

		const math::vec3& position = renderable->getPosition();
		const math::vec2& size = renderable->getSize();
		const unsigned int color = renderable->getColor();
		const std::vector<math::vec2>& uv = renderable->getUV();
		const GLuint tid = renderable->getTID();

		float ts = 0.0f;
		if(tid>0){
			bool found = false;
			for(int i=0; i<m_TextureSlots.size(); i++ ){
				if(m_TextureSlots[i] == tid){
					ts = (float)(i+1);
					found = true;
					break;
				}
			}

			if(!found){
				if(m_TextureSlots.size() >= RENDERER_MAX_TEXTURES){
					end();
					flush();
					begin();
				}
				m_TextureSlots.push_back(tid);
				ts = (float)(m_TextureSlots.size());
			}
		}

		m_Buffer->vertex = *m_TransformationBack *math::vec3(position.x, position.y, position.z);
		m_Buffer->uv = uv[0];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack*math::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[1];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack*math::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[2];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack*math::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->uv = uv[3];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;

		glBindVertexArray(m_VAO);
	}

	void Batch2DRenderer::begin(){
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Batch2DRenderer::drawString(const std::string &text, const math::vec2 &position, const Font &font, unsigned int color){
		float ts = 0.0f;
		bool found = false;
		for(int i=0; i<m_TextureSlots.size(); i++ ){
			if(m_TextureSlots[i] == font.getId()){
				ts = (float)(i+1);
				found = true;
				break;
			}
		}

		if(!found){
			if(m_TextureSlots.size() >= RENDERER_MAX_TEXTURES){
				end();
				flush();
				begin();
			}
			m_TextureSlots.push_back(font.getId());
			ts = (float)(m_TextureSlots.size());
	
		}

		const math::vec2& scale = font.getScale();
		float x = position.x;

		ftgl::texture_font_t* ftFont = font.getFTFont();

		for(int i=0; i<text.length(); i++){
			char c = text[i];
			texture_glyph_t* glyph = ftgl::texture_font_get_glyph(ftFont, &c);
			if(glyph != NULL){

				if(i>0){
					float kerning = texture_glyph_get_kerning(glyph, &text[i-1]);
					x += kerning / scale.x;
				}

				float x0 = x + glyph->offset_x / scale.x;
				float y0 = position.y + glyph->offset_y / scale.y;
				float x1 = x0 + glyph->width / scale.x;
				float y1 = y0 - glyph->height / scale.y;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				m_Buffer->vertex = *m_TransformationBack*math::vec3(x0,y0,0);
				m_Buffer->uv = math::vec2(u0, v0);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_Buffer->vertex = *m_TransformationBack*math::vec3(x0,y1,0);
				m_Buffer->uv = math::vec2(u0, v1);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_Buffer->vertex = *m_TransformationBack*math::vec3(x1,y1,0);
				m_Buffer->uv = math::vec2(u1, v1);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_Buffer->vertex = *m_TransformationBack*math::vec3(x1,y0,0);
				m_Buffer->uv = math::vec2(u1, v0);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_IndexCount += 6;
				x+= glyph->advance_x / scale.x;
			}
		}
		glBindVertexArray(m_VAO);
	}

	void Batch2DRenderer::end(){
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}

	void Batch2DRenderer::flush(){
		for(int i =0; i<m_TextureSlots.size(); i++){
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, NULL);
		
		m_IBO->unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;
		m_TextureSlots.clear();
	}

	void Batch2DRenderer::drawLine(float x0, float y0, float x1, float y1, uint color, float thickness){
		float ts = 0.0f;

		vec2 normal = vec2(y1 - y0, -(x1 - x0)).normalise() * thickness;

		vec3 vertex = *m_TransformationBack * vec3(x0 + normal.x, y0 + normal.y, 0.0f);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(0, 0);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * vec3(x1 + normal.x, y1 + normal.y, 0.0f);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(0, 1);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * vec3(x1 - normal.x, y1 - normal.y, 0.0f);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(1, 1);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * vec3(x0 - normal.x, y0 - normal.y, 0.0f);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(1, 0);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Batch2DRenderer::drawLine(const math::vec2& start, const math::vec2& end, uint color, float thickness){
		drawLine(start.x, start.y, end.x, end.y, color, thickness);
	}

	void Batch2DRenderer::drawRect(float x, float y, float width, float height, uint color){
		drawLine(x, y, x + width, y, color);
		drawLine(x + width, y, x + width, y + height, color);
		drawLine(x + width, y + height, x, y + height, color);
		drawLine(x, y + height, x, y, color);
	}

	void Batch2DRenderer::drawRect(const math::vec2& position, const math::vec2& size, uint color){
		drawRect(position.x, position.y, size.x, size.y, color);
	}

	void Batch2DRenderer::drawRect(const math::Rectangle& rectangle, uint color){
		drawRect(rectangle.getMinimumBound(), rectangle.size * 2.0f, color);
	}

	void Batch2DRenderer::fillRect(float x, float y, float width, float height, uint color){
		vec3 position(x, y, 0.0f);
		vec2 size(width, height);

		float ts = 0.0f;

		vec3 vertex = *m_TransformationBack * position;
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(0, 0);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * vec3(position.x + size.x, position.y, position.z);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(0, 1);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(1, 1);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * vec3(position.x, position.y + size.y, position.z);
		m_Buffer->vertex = vertex;
		m_Buffer->uv = math::vec2(1, 0);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Batch2DRenderer::fillRect(const math::vec2& position, const math::vec2& size, uint color){
		fillRect(position.x, position.y, size.x, size.y, color);
	}

	void Batch2DRenderer::fillRect(const math::Rectangle& rectangle, uint color){
		fillRect(rectangle.getMinimumBound(), rectangle.size * 2.0f, color);
	}



} }