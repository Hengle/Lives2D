#pragma once
#include<iostream>

#ifdef WIN32
#include"AL\alut.h"
#elif ANDROID

#endif

class AudioSource
{
private:
#ifdef WIN32
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	ALuint m_SoundBuffer; //��������
	ALuint m_SoundSource; //��Դ
#elif ANDROID

#endif


public:
	AudioSource();
	~AudioSource();

public:
	void LoadAudio(const char* varAudioPath);

	void Play();

	void Loop();
};

