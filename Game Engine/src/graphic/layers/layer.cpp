#include "layer.h"

namespace sge { namespace graphics{

	Layer::Layer(Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix)
		:m_Name("Layer"), m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) {
		init();
	}

	Layer::Layer(std::string name, Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix)
		:m_Name(name), m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix){
		init();
	}

	Layer::~Layer(){
		delete m_Shader;
		delete m_Renderer;

		for(int i=0; i<m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	void Layer::init(){
		m_Shader->enable();
		GLint texIDs[] = {
    		 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    		10,11,12,13,14,15,16,17,18,19,
    		20,21,22,23,24,25,26,27,28,29,
    		30,31
    	};
    	m_Shader->setUniform1iv("tex", texIDs, 32);
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->setUniformMat4("vw_matrix", math::mat4::identity());
		m_Shader->setUniformMat4("ml_matrix", math::mat4::identity());
		m_Shader->disable();
	}

	void Layer::add(Renderable2D* renderable){
		m_Renderables.push_back(renderable);
	}

	void Layer::onEvent(events::Event& event){

		for(int i=0; i< m_Renderables.size(); i++)
			m_Renderables[i]->onEvent(event);

		events::EventDispatcher dispatcher(event);
		dispatcher.dispatch<events::ResizeWindowEvent>([this](events::ResizeWindowEvent& e) { return onResize(e.getWidth(), e.getHeight()); });
	}

	void Layer::onRender(){
		m_Shader->enable();
		m_Renderer->begin();

		for(int i=0; i< m_Renderables.size(); i++)
			m_Renderables[i]->submit(m_Renderer);

		m_Renderer->end();

		m_Renderer->flush();
	}

	bool Layer::onResize(uint width, uint height) {
		return false;
	}

	void Layer::onTick() {
	}

	void Layer::onUpdate() {
	}

	bool Layer::onKeyPressed() {
		return false;
	}

	bool Layer::onMousePressed() {
		std::cout << m_Name << ": peguei! " << std::endl;
		return false;
	}

	
}}