#include "sound.h"
#include "soundmanager.h"

namespace sge { namespace audio {

	bool Sound::m_Playing = false;
	bool Sound::m_Paused = false;

	void onFinish(ga_Handle* in_handle, void* in_context){
	  Sound::m_Playing = false;
	  Sound::m_Paused = false;
	  ga_handle_destroy(in_handle);
	}

	Sound::Sound(const std::string &name, const std::string &filename)
		:m_Name(name), m_Filename(filename) {

		std::vector<std::string> split = split_string(m_Filename, '.');

		if (split.size() < 2)
		{
			std::cout << "[Sound] Invalid file name '" << m_Filename << "'!" << std::endl;
			return;
		}

		m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

		if (m_Sound == nullptr)
			std::cout << "[Sound] Could not load file '" << m_Filename << "'!" << std::endl;
		
		m_Position = 0;
		
	}

	Sound::~Sound() {
		ga_sound_release(m_Sound);
	}

	void Sound::play(bool loop){
		if(!m_Playing){
			gau_SampleSourceLoop* loopSrc = 0; 
			gau_SampleSourceLoop** pLoopSrc = &loopSrc;  
			gc_int32 quit = 0;

			if (!loop) pLoopSrc = 0;

			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &onFinish, &quit, pLoopSrc);
			
			if(m_Paused){
				ga_handle_seek(m_Handle, m_Position);
			}

			ga_handle_play(m_Handle);
			m_Paused = false;
			m_Playing = true;
		}
	}

	void Sound::pause(){
		if(m_Playing){
			m_Position = ga_handle_tell(m_Handle, GA_TELL_PARAM_CURRENT);
			ga_handle_stop(m_Handle);
			m_Playing = false;
			m_Paused = true;
		}
	}

	void Sound::stop(){
		if(m_Playing){
			ga_handle_stop(m_Handle);
			ga_handle_destroy(m_Handle);
			m_Position = 0;
			m_Playing = false;
			m_Paused = false;
		}
	}

	void Sound::setGain(float gain){
		if(!m_Playing)
			return;
		if(gain > 1.0f)
			gain = 1.0f;
		if(gain<0.0f)
			gain = 0.0f;
		m_Gain = gain;
		ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain); 
	}
	
} }