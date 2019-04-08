#pragma once

#include <string>
#include <iostream>
#include "../utils/stringutils.h"
#include "../../ext/gorilla-audio/include/ga.h"
#include "../../ext/gorilla-audio/include/gau.h"

namespace sge { namespace audio {

	class Sound{
	private:
		std::string m_Name;
		std::string m_Filename;
		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		float m_Gain;
		static bool m_Playing;
		static bool m_Paused;
		gc_int32 m_Position;
	public:
		Sound(const std::string &name, const std::string &filename);
		~Sound();

		void play(bool loop);
		void pause();
		void stop();

		void setGain(float gain);

		inline const bool isPlaying() const  { return m_Playing; }
		inline const float getGain() const { return m_Gain; }
 		inline const std::string getName() const { return m_Name; }
		inline const std::string getFileName() const { return m_Filename; }
	private:
		friend void onFinish(ga_Handle* in_handle, void* in_context);
	};
	
} }