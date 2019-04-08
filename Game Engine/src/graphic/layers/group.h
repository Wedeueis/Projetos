#pragma once

#include "../renderable/renderable2D.h"

namespace sge{ namespace graphics{

	class Group: public Renderable2D{
	private:
		std::vector<Renderable2D*> m_Renderables;
		math::mat4 m_TransformationMatrix;
	public:
		Group();
		~Group();
		Group(math::mat4 transform);
		void addTransformation(math::mat4 transform);
		void resetTransformation();
		void add(Renderable2D * renderable);
		void remove(Renderable2D * renderable);
		void submit(Renderer2D* renderer) const override;
	};

}}