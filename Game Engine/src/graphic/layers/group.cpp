#include "group.h"

namespace sge{ namespace graphics{

	Group::Group(){
		m_TransformationMatrix = math::mat4::identity();
	}

	Group::Group(math::mat4 transform){
		m_TransformationMatrix = transform;
	}

	Group::~Group(){
		for(int i = 0; i<m_Renderables.size(); i++)
			delete m_Renderables[i];
	}
	
	void Group::submit(Renderer2D* renderer) const{
		renderer->push(m_TransformationMatrix);
		for(const Renderable2D* renderable: m_Renderables){
			renderable->submit(renderer);
		}
		renderer->pop();
	}

	void Group::addTransformation(math::mat4 transform){
		m_TransformationMatrix = transform*m_TransformationMatrix;
	}

	void Group::resetTransformation(){
		m_TransformationMatrix = math::mat4::identity();
	}

	void Group::add(Renderable2D * renderable){
		m_Renderables.push_back(renderable);
	}

	void Group::remove(Renderable2D *renderable) {
		int index = 0;
		for (uint i = 0; i < m_Renderables.size(); i++)
		{
			if (m_Renderables[i] == renderable)
			{
				m_Renderables.erase(m_Renderables.begin() + i);
				delete  m_Renderables[i];
				break;
			}
		}
	}
}}