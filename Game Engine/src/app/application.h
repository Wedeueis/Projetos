#pragma once

#include "../sge.h"

namespace sge {
	class App{
	private:
		static App* s_Instance;
	public:
		Window* window;
	private:
		bool m_Running, m_Suspended;
		Timer* m_Timer;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;

		std::string m_Name;
		std::vector<graphics::Layer*> m_LayerStack;
	public:
		App(const std::string &name, const WindowProperties& properties);
		virtual ~App();

		void pushLayer(graphics::Layer* layer);
		graphics::Layer* popLayer();
		graphics::Layer* popLayer(graphics::Layer* layer);

		void start();
		void suspend();
		void resume();
		void stop();

		//Runs once upon initialization
		virtual void init();

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }

		inline uint getWindowWidth() const { return window->getWidth(); }
		inline uint getWindowHeight() const { return window->getHeight(); }
		inline math::vec2 GetWindowSize() const { return math::vec2((float)window->getWidth(), (float)window->getHeight()); }
	protected:
		//Runs once per second
		virtual void onTick() { }
		//Runs 60 times per second
		virtual void onUpdate() { }
		//Runs as fast as possible (unless vsync is enabled)
		virtual void onRender();

	private:
		void run();
		
	public:
		void onEvent(events::Event& event);
		inline static App& getApplication() { return *s_Instance; }
	};
}