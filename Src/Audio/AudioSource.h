#pragma once
#include<iostream>

#ifdef WIN32
#include"AL\alut.h"
#elif ANDROID

#elif IOS
#include <OpenAL/OpenAL.h>
#include "AL/alut.h"
#endif

class AudioSource
{
private:
#if (defined WIN32)||(defined __APPLE__)
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	ALuint m_SoundBuffer; //��������
	ALuint m_SoundSource; //��Դ
#elif ANDROID
	std::string mAudioPath;
#endif


public:
	AudioSource();
	~AudioSource();

public:
	void LoadAudio(const char* varAudioPath);

	void Play();

	void Loop();
};

