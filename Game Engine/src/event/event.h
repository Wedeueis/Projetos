#pragma once

#include <string>

namespace sge { namespace events {
	
	class Event {
	private:
		friend class EventDispatcher;
	public:
		enum class Type
		{
			KEY_PRESSED,
			KEY_RELEASED,

			MOUSE_PRESSED,
			MOUSE_RELEASED,
			MOUSE_MOVED,

			WINDOW_RESIZE
		};
	protected:
		bool m_Handled;
		Type m_Type;
	protected:
		Event(Type type);
	public:
		inline Type getType() const { return m_Type; }
		inline bool isHandled() const { return m_Handled; }

		virtual std::string  toString() const;

		static std::string  typeToString(Type type);
	};

}}