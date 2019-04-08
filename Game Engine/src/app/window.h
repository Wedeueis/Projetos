#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <map>
#include "../font/fontmanager.h"
#include "../audio/soundmanager.h"
#include "../event/events.h"
#include "../graphic/texture/texturemanager.h"
#include "input.h"

namespace sge{

	typedef std::function<void(events::Event& event)> WindowEventCallback;

	struct WindowProperties
	{
		unsigned int width, height;
		bool fullscreen;
		bool vsync;
	};

	class Window{
	private:
		static std::map<void*, Window*> s_Handles;
	private:
		std::string m_Title;

		WindowProperties m_Properties;
		GLFWwindow *m_Window;
		bool m_Closed;
		void* m_Handle;
		bool m_Vsync;
		WindowEventCallback m_EventCallback;
		InputManager* m_InputManager;
		
	public:
		
		Window(const std::string &name, const WindowProperties& properties);
		~Window();
		void clear() const;
		bool closed() const;
		void update();

		inline int getWidth() const { return m_Properties.width; }
		inline int getHeight() const { return m_Properties.height; }
		inline InputManager* getInputManager() const { return m_InputManager; }

		void setVsync(bool enabled);
		inline bool IsVsync() const { return m_Vsync; }

		void setEventCallback(const WindowEventCallback& callback);
	private:
		bool init();
		friend void onFocus(GLFWwindow *window, bool focused);
		friend void onResize(GLFWwindow *window, int width, int height);
		friend void onKey(GLFWwindow *window, int key, int code, int action, int mods);
		friend void onClick(GLFWwindow *window, int button, int action, int mods);
		friend void onMouse(GLFWwindow *window, double xpos, double ypos);
	};

}