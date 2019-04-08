#pragma once

#include "../../ext/box2d/include/Box2D.h"
#include "../../src/graphic/renderer/batch2Drenderer.h"

namespace sge { namespace physics {

  class DebugDraw : public b2Draw{
  private:
    graphics::Renderer2D* m_Renderer;
  public:
    DebugDraw();
    ~DebugDraw();

    void setRenderer(graphics::Renderer2D* renderer);

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    void DrawTransform(const b2Transform& xf) override;
    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
  };

}}