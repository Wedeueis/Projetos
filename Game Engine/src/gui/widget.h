#pragma once

#include "../math/rectangle.h"
#include "../graphic/renderer/renderer2D.h"
#include "../graphic/layers/layer.h"
#include "../event/events.h"
#include "../app/application.h"
#include "../math/maths.h"
#include "../graphic/shader/shader.h"
#include "../utils/colors.h"

namespace sge { namespace graphics { namespace gui {

	class Component;

	class Widget : public Renderable2D {
	protected:
		bool m_Active;
		bool m_Focused;

		Component* m_Father;
		math::Rectangle m_Bounds;
	private:
		Widget() {}
	protected:
		Widget(const math::Rectangle& bounds);
	public:
		virtual bool onMousePressed(events::MousePressedEvent& e);
		virtual bool onMouseReleased(events::MouseReleasedEvent& e);
		virtual bool onMouseMoved(events::MouseMovedEvent& e);

		virtual void onUpdate();

		virtual void onEvent(events::Event& event) override {
			Renderable2D::onEvent(event);
		}

		virtual void submit(Renderer2D* renderer) const override{
			Renderable2D::submit(renderer);
		}

		inline const math::Rectangle& getBounds() const { return m_Bounds; }
		inline math::Rectangle& getBounds() { return m_Bounds; }
		inline void setBounds(const math::Rectangle& bounds) { m_Bounds = bounds; }

		inline bool isActive() const { return m_Active; }
		inline void setActive(bool active) { m_Active = active; }
	};

} } }