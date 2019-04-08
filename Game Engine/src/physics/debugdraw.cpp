#include "debugdraw.h"

namespace sge { namespace physics {
    DebugDraw::DebugDraw() {
    	m_Renderer = nullptr;
    }

    DebugDraw::~DebugDraw() {
    	delete m_Renderer;
    }

    void DebugDraw::setRenderer(graphics::Renderer2D* renderer){
    	if(m_Renderer==nullptr){
    		m_Renderer = renderer;
    	}
    }

    void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
      for (int i = 1; i < vertexCount; i++) {
      	m_Renderer->drawLine(vertices[i-1].x, vertices[i-1].y, vertices[i].x, vertices[i].y, BLUE_ACCENT , 0.02f);
      }
    }

    void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {    
    	if(vertexCount == 4){
    		float posx = vertices[0].x;
    		float posy = vertices[0].y;
    		float width = abs(vertices[1].x - vertices[0].x);
    		float height = abs(vertices[3].y - vertices[0].y);
    		m_Renderer->fillRect(math::Rectangle(posx, posy,width,height), BLUE_ACCENT );
    	}
      
    }

    void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
		//To do
    }

    void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
    	//To do
    }

    void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
      m_Renderer->drawLine(p1.x, p1.y, p2.x, p2.y, BLUE_ACCENT , 0.02f);

    	/*
      //set up vertex array
      GLfloat glverts[4]; 
      glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
      glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays
      
      glverts[0]   = p1.x;
      glverts[1] = p1.y;

      glverts[2]   = p2.x;
      glverts[3] = p2.y;
    
      //draw lines
      glLineWidth(3); //fat lines
      glColor4f( 1, 0, 1, 1 ); //purple
      glDrawArrays(GL_LINE_LOOP, 0, 2);
      */
    }

    void DebugDraw::DrawTransform(const b2Transform& xf) {
    	//To do
    }

    void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color){
    	/*
   	  //set up vertex array
      GLfloat glverts[2]; 
      glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
      glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays
      
      glverts[0]   = p.x;
      glverts[1] = p.y;

      //draw lines
      glLineWidth(size); //fat lines
      glColor4f( 1, 0, 1, 1 ); //purple
      glDrawArrays(GL_LINE_LOOP, 0, 1);
      */
    }

}}