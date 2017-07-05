#pragma once
#include<iostream>
#include"AL\alut.h"

class AudioSource
{
private:
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	ALuint m_SoundBuffer; //��������
	ALuint m_SoundSource; //��Դ


public:
	AudioSource();
	~AudioSource();

public:
	void LoadAudio(const char* varAudioPath);

	void Play();

	void Loop();
};

