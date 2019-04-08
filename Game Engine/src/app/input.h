#pragma once

#include "../math/maths.h"
#include "../event/events.h"
#include <GLFW/glfw3.h>

namespace sge {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	typedef std::function<void(events::Event& event)> WindowEventCallback;

	class Window;

	class InputManager {
	private:
		friend class Window;
	private:
		bool m_KeyState[MAX_KEYS];
		bool m_LastKeyState[MAX_KEYS];

		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		bool m_MouseGrabbed;
		unsigned int m_KeyModifiers;

		math::vec2 m_MousePosition;
		WindowEventCallback m_EventCallback;
	public:
		InputManager();

		inline void setEventCallback(const WindowEventCallback& eventCallback) { m_EventCallback = eventCallback; }

		void update();

		bool isKeyPressed(uint keycode) const;
		bool isMouseButtonPressed(uint button) const;
		bool isMouseButtonClicked(uint button) const;

		const math::vec2& getMousePosition() const;
		void setMousePosition(const math::vec2& position);
		const bool isMouseGrabbed() const;
		void setMouseGrabbed(bool grabbed);
		void setMouseCursor(unsigned int cursor);

		void clearKeys();
		void clearMouseButtons();
	private:
		friend void onKey(GLFWwindow *window, int key, int code, int action, int mods);
		friend void onClick(GLFWwindow *window, int button, int action, int mods);
		friend void onMouse(GLFWwindow *window, double xpos, double ypos);
	};

	class Input {
	private:
		friend class InputManager;
	private:
		static InputManager* s_InputManager;
	public:
		inline static bool isKeyPressed(unsigned int keycode) { return s_InputManager->isKeyPressed(keycode); }
		inline static bool isMouseButtonPressed(unsigned int button) { return s_InputManager->isMouseButtonPressed(button); }
		inline static bool isMouseButtonClicked(unsigned int button) { return s_InputManager->isMouseButtonClicked(button); }

		inline static const math::vec2& getMousePosition() { return s_InputManager->getMousePosition(); }

		inline static InputManager* getInputManager() { return s_InputManager; }
	};

}


#define SGE_MOUSE_LEFT	  			0x00
#define SGE_MOUSE_MIDDLE			0x01
#define SGE_MOUSE_RIGHT    			0x02

#define SGE_NO_CURSOR	  			NULL

#define SGE_MODIFIER_LEFT_CONTROL	0x03
#define SGE_MODIFIER_LEFT_ALT		0x04
#define SGE_MODIFIER_LEFT_SHIFT		0x05
#define SGE_MODIFIER_RIGHT_CONTROL	0x06
#define SGE_MODIFIER_RIGHT_ALT		0x07
#define SGE_MODIFIER_RIGHT_SHIFT	0x08

#define SGE_KEY_TAB			  0x09

#define SGE_KEY_0			  0x30
#define SGE_KEY_1			  0x31
#define SGE_KEY_2			  0x32
#define SGE_KEY_3			  0x33
#define SGE_KEY_4			  0x34
#define SGE_KEY_5			  0x35
#define SGE_KEY_6			  0x36
#define SGE_KEY_7			  0x37
#define SGE_KEY_8			  0x38
#define SGE_KEY_9			  0x39

#define SGE_KEY_A			  0x41
#define SGE_KEY_B			  0x42
#define SGE_KEY_C			  0x43
#define SGE_KEY_D			  0x44
#define SGE_KEY_E			  0x45
#define SGE_KEY_F			  0x46
#define SGE_KEY_G			  0x47
#define SGE_KEY_H			  0x48
#define SGE_KEY_I			  0x49
#define SGE_KEY_J			  0x4A
#define SGE_KEY_K			  0x4B
#define SGE_KEY_L			  0x4C
#define SGE_KEY_M			  0x4D
#define SGE_KEY_N			  0x4E
#define SGE_KEY_O			  0x4F
#define SGE_KEY_P			  0x50
#define SGE_KEY_Q			  0x51
#define SGE_KEY_R			  0x52
#define SGE_KEY_S			  0x53
#define SGE_KEY_T			  0x54
#define SGE_KEY_U			  0x55
#define SGE_KEY_V			  0x56
#define SGE_KEY_W			  0x57
#define SGE_KEY_X			  0x58
#define SGE_KEY_Y			  0x59
#define SGE_KEY_Z			  0x5A

#define SGE_KEY_LBUTTON        0x01
#define SGE_KEY_RBUTTON        0x02
#define SGE_KEY_CANCEL         0x03
#define SGE_KEY_MBUTTON        0x04

#define SGE_KEY_ESCAPE         0x1B
#define SGE_KEY_SHIFT          0x10
#define SGE_KEY_CONTROL        0x11
#define SGE_KEY_MENU           0x12
#define SGE_KEY_ALT	          SG_KEY_MENU
#define SGE_KEY_PAUSE          0x13
#define SGE_KEY_CAPITAL        0x14

#define SGE_KEY_SPACE          0x20
#define SGE_KEY_PRIOR          0x21
#define SGE_KEY_NEXT           0x22
#define SGE_KEY_END            0x23
#define SGE_KEY_HOME           0x24
#define SGE_KEY_LEFT           0x25
#define SGE_KEY_UP             0x26
#define SGE_KEY_RIGHT          0x27
#define SGE_KEY_DOWN           0x28
#define SGE_KEY_SELECT         0x29
#define SGE_KEY_PRINT          0x2A
#define SGE_KEY_EXECUTE        0x2B
#define SGE_KEY_SNAPSHOT       0x2C
#define SGE_KEY_INSERT         0x2D
#define SGE_KEY_DELETE         0x2E
#define SGE_KEY_HELP           0x2F

#define SGE_KEY_NUMPAD0        0x60
#define SGE_KEY_NUMPAD1        0x61
#define SGE_KEY_NUMPAD2        0x62
#define SGE_KEY_NUMPAD3        0x63
#define SGE_KEY_NUMPAD4        0x64
#define SGE_KEY_NUMPAD5        0x65
#define SGE_KEY_NUMPAD6        0x66
#define SGE_KEY_NUMPAD7        0x67
#define SGE_KEY_NUMPAD8        0x68
#define SGE_KEY_NUMPAD9        0x69
#define SGE_KEY_MULTIPLY       0x6A
#define SGE_KEY_ADD            0x6B
#define SGE_KEY_SEPARATOR      0x6C
#define SGE_KEY_SUBTRACT       0x6D
#define SGE_KEY_DECIMAL        0x6E
#define SGE_KEY_DIVIDE         0x6F
#define SGE_KEY_F1             0x70
#define SGE_KEY_F2             0x71
#define SGE_KEY_F3             0x72
#define SGE_KEY_F4             0x73
#define SGE_KEY_F5             0x74
#define SGE_KEY_F6             0x75
#define SGE_KEY_F7             0x76
#define SGE_KEY_F8             0x77
#define SGE_KEY_F9             0x78
#define SGE_KEY_F10            0x79
#define SGE_KEY_F11            0x7A
#define SGE_KEY_F12            0x7B
#define SGE_KEY_F13            0x7C
#define SGE_KEY_F14            0x7D
#define SGE_KEY_F15            0x7E
#define SGE_KEY_F16            0x7F
#define SGE_KEY_F17            0x80
#define SGE_KEY_F18            0x81
#define SGE_KEY_F19            0x82
#define SGE_KEY_F20            0x83
#define SGE_KEY_F21            0x84
#define SGE_KEY_F22            0x85
#define SGE_KEY_F23            0x86
#define SGE_KEY_F24            0x87

#define SGE_KEY_NUMLOCK        0x90
#define SGE_KEY_SCROLL         0x91

#define SGE_KEY_LSHIFT         0xA0
#define SGE_KEY_RSHIFT         0xA1
#define SGE_KEY_LCONTROL       0xA2
#define SGE_KEY_RCONTROL       0xA3
#define SGE_KEY_LMENU          0xA4
#define SGE_KEY_RMENU          0xA5