#include "application.h"

namespace sge {

	using namespace graphics;

	App* App::s_Instance = nullptr;

	App::App(const std::string &name, const WindowProperties& properties) 
		:m_FramesPerSecond(0), m_UpdatesPerSecond(0), m_Name(name){
			window = new Window(name, properties);
			s_Instance = this;
			std::cout << window->getWidth() << std::endl;
			window->setEventCallback(std::bind(&App::onEvent, this, std::placeholders::_1));
		}

	App::~App() {
		delete window;
		delete m_Timer;
		for(int i=0; i<m_LayerStack.size(); i++)
			delete m_LayerStack[i];
	}

	void App::pushLayer(Layer* layer){
		m_LayerStack.push_back(layer);
	}

	Layer* App::popLayer() {
		Layer* layer = m_LayerStack.back();
		m_LayerStack.pop_back();
		return layer;
	}

	Layer* App::popLayer(Layer* layer)
	{
		for (uint i = 0; i < m_LayerStack.size(); i++)
		{
			if (m_LayerStack[i] == layer)
			{
				m_LayerStack.erase(m_LayerStack.begin() + i);
				break;
			}
		}
		return layer;
	}

	void App::init() {
		
	}

	void App::start(){
		init();
		m_Running = true;
		m_Suspended = false;
		run();
	}

	void App::suspend() {
		m_Suspended = true;
	}

	void App::resume() {
		m_Suspended = false;
	}

	void App::stop() {
		m_Running = false;
	}

	void App::onRender(){
		for (uint i = 0; i < m_LayerStack.size(); i++){
				m_LayerStack[i]->onRender();
		}

	}

	void App::run(){
		m_Timer = new Timer();
		float time = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		unsigned int frames = 0;
		unsigned int updates = 0;

		while(!window->closed()){
			window->clear();

			if (m_Timer->elapsed() - updateTimer > updateTick) {
				onUpdate();
				updates++;
				updateTimer += updateTick;
			}

			onRender();

			frames++;

			window->update();


			if (m_Timer->elapsed() - time > 1.0f) {	
				time += 1.0f;
				m_FramesPerSecond = frames;
				m_UpdatesPerSecond = updates;
				frames = 0;
				updates = 0;
				onTick();
			}
		}

	}

	void App::onEvent(events::Event& event) {
		for (int i = m_LayerStack.size() - 1; i >= 0; i--) {
			m_LayerStack[i]->onEvent(event);
			if (event.isHandled())
				return;
		}
	}
}