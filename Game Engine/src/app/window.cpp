#include "window.h"
#include "application.h"

namespace sge{

	using namespace graphics;
	using namespace events;

	std::map<void*, Window*> Window::s_Handles;

	void onKey(GLFWwindow *window, int key, int code, int action, int mods){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_InputManager->m_KeyState[key] = action != GLFW_RELEASE;
		switch(action){
			case GLFW_PRESS:{
				if (win->m_EventCallback)
					if(action != GLFW_REPEAT)
						win->m_EventCallback(*(new KeyPressedEvent((unsigned int)key,GLFW_REPEAT, mods)));
					else
						win->m_EventCallback(*(new KeyPressedEvent((unsigned int)key,0, mods)));
				break;
			}case GLFW_RELEASE:{
				if (win->m_EventCallback)
					win->m_EventCallback(*(new KeyReleasedEvent((unsigned int)key)));
				break;
			}
		}
	}

	void onClick(GLFWwindow *window, int button, int action, int mods){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_InputManager->m_MouseButtons[button] = action != GLFW_RELEASE;
		float x = win->m_InputManager->getMousePosition().x;
		float y =  win->m_InputManager->getMousePosition().y;
		switch(action){
			case GLFW_PRESS:{
				if (win->m_EventCallback)
					win->m_EventCallback(*(new MousePressedEvent((unsigned int)button, x, y)));
				break;
			}case GLFW_RELEASE:{
				if (win->m_EventCallback)
					win->m_EventCallback(*(new MouseReleasedEvent((unsigned int)button, x, y)));
				break;
			}
		}
	}

	void onMouse(GLFWwindow *window, double xpos, double ypos){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_InputManager->setMousePosition(math::vec2(xpos, ypos));
		if (win->m_EventCallback)
			win->m_EventCallback(*(new MouseMovedEvent((unsigned int)xpos, (unsigned int)ypos)));
	}

	void onResize(GLFWwindow *window, int width, int height){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		glViewport( 0, 0, width, height);
		win->m_Properties.width = width;
		win->m_Properties.height = height;
		FontManager::get()->setScale(win->m_Properties.width / 16.0f, win->m_Properties.height / 9.0f);
		if (win->m_EventCallback)
			win->m_EventCallback(*(new ResizeWindowEvent((unsigned int)width, (unsigned int)height)));
	}

	void onFocus(GLFWwindow *window, bool focused) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		if (!focused)
		{
			win->m_InputManager->clearKeys();
			win->m_InputManager->clearMouseButtons();
		}
	}

	Window::Window(const std::string &title, const WindowProperties& properties)
		:m_Title(title), m_Properties(properties), m_Handle(nullptr), m_Closed(false), m_EventCallback(nullptr){
		if(!init())
			glfwTerminate();

		FontManager::add(new Font("SourceSansPro", "resources/fonts/SourceSansPro-Light.ttf", 32));
		FontManager::add(new Font("gui", "resources/fonts/SourceSansPro-Light.ttf", 24));
		FontManager::get()->setScale(m_Properties.width / 16.0f, m_Properties.height / 9.0f);
		FontManager::get("gui")->setScale(m_Properties.width / 16.0f, m_Properties.height / 9.0f);
		audio::SoundManager::init();

		m_InputManager = new InputManager();
	}

	Window::~Window() {
		FontManager::clean();
		audio::SoundManager::clean();
		TextureManager::clean();
		glfwTerminate();
	}

	void Window::update() {
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		audio::SoundManager::update();
		m_InputManager->update();
	}

	bool Window::init() {
		if(!glfwInit()){
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Properties.width, m_Properties.height, m_Title.c_str(), NULL, NULL);
		if(!m_Window){
			glfwTerminate();	
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, onResize);
		glfwSetKeyCallback(m_Window, onKey);
		glfwSetMouseButtonCallback(m_Window, onClick);
		glfwSetCursorPosCallback(m_Window, onMouse);
		glfwSwapInterval(0.0);

		if(glewInit() != GLEW_OK){
			glfwTerminate();
			std::cout << "Failed to initialize GLEW!" << std::endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void Window::setVsync(bool enabled) {
		// TODO: Not implemented
		m_Vsync = enabled;
		
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window);
	}

	void Window::setEventCallback(const WindowEventCallback& callback) {
		m_EventCallback = callback;
		m_InputManager->setEventCallback(m_EventCallback);
	}
}