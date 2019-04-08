#include "component.h"

namespace sge{ namespace graphics{ namespace gui {

	Component::Component(const math::Rectangle& bounds)
		: Widget(bounds), m_TransformationMatrix(math::mat4::identity()) {
	}

	Component::~Component(){
		clear();
	}
	
	void Component::submit(Renderer2D* renderer) const{
		renderer->push(m_TransformationMatrix);
		for(const Widget* widget: m_Widgets){
			widget->submit(renderer);
		}
		renderer->pop();
	}

	void Component::addTransformation(math::mat4 transform){
		m_TransformationMatrix = transform*m_TransformationMatrix;
	}

	void Component::resetTransformation(){
		m_TransformationMatrix = math::mat4::identity();
	}

	void Component::onUpdate() {
		for (Widget* widget : m_Widgets) {
			if (widget->isActive())
				widget->onUpdate();
		}
	}

	void Component::onEvent(events::Event& event){
		for (Widget* widget : m_Widgets) {
			if (widget->isActive())
				widget->onEvent(event);
		}
	}

	Widget* Component::add(Widget *widget){
		math::vec2 newPosition = m_TransformationMatrix * widget->getBounds().position;
 		widget->setBounds(math::Rectangle(newPosition, widget->getBounds().size));
		m_Widgets.push_back(widget);
		return widget;
	}

	void Component::remove(Widget *widget) {
		int index = 0;
		for (uint i = 0; i < m_Widgets.size(); i++) {
			if (m_Widgets[i] == widget) {
				m_Widgets.erase(m_Widgets.begin() + i);
				delete  m_Widgets[i];
				break;
			}
		}
	}

	void Component::clear() {
		for (uint i = 0; i < m_Widgets.size(); i++)
			delete m_Widgets[i];

		m_Widgets.clear();
	}

} } }