#pragma once

#include "../renderer/renderer2D.h"
#include "../renderable/renderable2D.h"
#include "../../event/events.h"

namespace sge { namespace graphics{

	class Layer : public events::IEventHandler{
	private:
		std::string m_Name;
	protected:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		math::mat4 m_ProjectionMatrix;
	private:
		void init();
	public:
		Layer(Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix);
		Layer(std::string name, Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix);

		virtual ~Layer();
		virtual void add(Renderable2D* renderable);
		virtual void onRender();
		virtual bool onResize(uint width, uint height);
		virtual void onTick();

		bool onKeyPressed();
		bool onMousePressed();

		virtual void onUpdate();

		virtual void onEvent(events::Event& event) override;

		const inline std::vector<Renderable2D*> getRenderables() const { return m_Renderables; }
	};	
}}