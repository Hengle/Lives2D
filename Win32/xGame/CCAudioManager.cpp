#include "CCAudioManager.h"
#include "Helper.h"


CCAudioManager* CCAudioManager::m_Instance=NULL;


CCAudioManager* CCAudioManager::SharedInstance()
{
	if(m_Instance==NULL)
	{
		m_Instance=new CCAudioManager();
	}
	return m_Instance;
}

CCAudioManager::CCAudioManager(void)
{
}


//��ʼ��
void CCAudioManager::Init(int argc,char* argv[])
{
	if(alutInit(&argc,argv)==AL_FALSE)
	{
		Helper::CCLOG("CCAudioManager::Init Faild");
	}
}

ALboolean CCAudioManager::LoadBGMusic(string filename)
{
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	alGenBuffers(1,&m_SoundBuffer); //�����ڴ���󣬲��洢��m_SoundBuffer��
	if(alGetError()!=AL_NO_ERROR) //�ж������Ƿ�洢
	{
		return AL_FALSE;
	}
	alutLoadWAVFile((ALbyte*)filename.c_str(),&format,&data,&size,&freq,&loop);//���ļ�,���봴���ڴ�������Ϣ
	alBufferData(m_SoundBuffer,format,data,size,freq);//��wav���ݴ��뵽m_SoundBuffer
	alutUnloadWAV(format,data,size,freq);//�����wav����

	//������Դ
	alGenSources(1,&m_SoundSource);
	if(alGetError()!=AL_NO_ERROR)
	{
		return AL_FALSE;
	}
	alSourcei(m_SoundSource,AL_BUFFER,m_SoundBuffer);
	alSourcef(m_SoundSource,AL_PITCH,1.0f);
	alSourcef(m_SoundSource,AL_GAIN,1.0f);
	//alSourcefv(m_SoundSource,AL_POSITION,m_SoundSourcePos);
	alSourcefv(m_SoundSource,AL_POSITION,m_SoundSourcePosVec3.m_Data);
	alSourcefv(m_SoundSource,AL_VELOCITY,m_SoundSourceVelVec3.m_Data);
	alSourcei(m_SoundSource,AL_LOOPING,loop);
	if(alGetError()==AL_NO_ERROR)
	{
		return AL_TRUE;
	}
	return AL_FALSE;
}

//�������ߵ�λ��-��ɫ��λ�� ��ɫ�ƶ�ʱҪ���½�ɫλ�õ�����
void CCAudioManager::SetListener()
{
	alListenerfv(AL_POSITION,m_ListenerPosVec3.m_Data);
	alListenerfv(AL_VELOCITY,m_ListenerVelVec3.m_Data);
	alListenerfv(AL_ORIENTATION,m_ListenerOriVec3.m_Data);
}

void CCAudioManager::PlayBGMusic(string filename)
{
	SetListener();
	alSourcePlay(m_SoundSource);
}


//��ͣ����
void CCAudioManager::PauseBGMusic()
{
	alSourcePause(m_SoundSource);
}

//ֹͣ����
void CCAudioManager::StopBGMusic()
{
	alSourceStop(m_SoundSource);
	alDeleteBuffers(1,&m_SoundBuffer);
	alDeleteSources(1,&m_SoundSource);
}

ALboolean CCAudioManager::LoadEffectMusic(string filename)
{
	return true;
}

void CCAudioManager::PlayEffectMusic(string filename)
{

}

//��ͣ��Ч
void CCAudioManager::PauseEffectMusic(string filename)
{

}

//ֹͣ��Ч
void CCAudioManager::StopEffectMusic(string filename)
{

}


//���þ������ر�һ������
void CCAudioManager::CloseAllSound()
{

}


CCAudioManager::~CCAudioManager(void)
{
	alDeleteBuffers(1,&m_SoundBuffer);
	alDeleteSources(1,&m_SoundSource);
}
