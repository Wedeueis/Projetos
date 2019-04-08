#include "input.h"

namespace sge {

	InputManager* Input::s_InputManager = nullptr;

	InputManager::InputManager() {
		clearKeys();
		clearMouseButtons();

		m_MouseGrabbed = true;

		Input::s_InputManager = this;
	}

	void InputManager::update() {
		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_LastKeyState, m_KeyState, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
	}

	void InputManager::clearKeys() {
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_KeyState[i] = false;
			m_LastKeyState[i] = false;
		}
		m_KeyModifiers = 0;
	}

	void InputManager::clearMouseButtons() {
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}
	}

	bool InputManager::isKeyPressed(uint keycode) const {
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_KeyState[keycode];
	}

	bool InputManager::isMouseButtonPressed(uint button) const {
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[button];
	}

	bool InputManager::isMouseButtonClicked(uint button) const {
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseClicked[button];
	}

	void InputManager::setMousePosition(const math::vec2& position){
		m_MousePosition = position;
	}

	const math::vec2& InputManager::getMousePosition() const {
		return m_MousePosition;
	}

	const bool InputManager::isMouseGrabbed() const {
		return m_MouseGrabbed;
	}

	void InputManager::setMouseGrabbed(bool grabbed) {
		m_MouseGrabbed = grabbed;
	}

}