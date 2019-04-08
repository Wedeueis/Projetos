#pragma once

#include "widget.h"

namespace sge{ namespace graphics { namespace gui {

	class Component: public Widget {
	protected:
		std::vector<Widget*> m_Widgets;
		math::mat4 m_TransformationMatrix;
	public:
		Component(const math::Rectangle& bounds);
		~Component();
		void addTransformation(math::mat4 transform);
		void resetTransformation();
		Widget* add(Widget *widget);
		void remove(Widget *widget);
		void clear();

		void onUpdate() override;
		void onEvent(events::Event& event) override;
		void submit(Renderer2D *renderer) const override;

		inline const std::vector<Widget*>& GetWidgets() const { return m_Widgets; }
	};

} } }