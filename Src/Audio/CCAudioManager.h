#pragma once

#include"al.h"
#include"alc.h"
#include"alut.h"

/*OPENALͷ��OPENGLͷ�Ķ���������������֮�������ˡ�al.h","al
u.h","alut.h"�롱gl.h","glu.h","glut.h"���ƣ���������һ��"alc.h".ALC��
AUDIO LIBRARY CONTEXT����������ͨ����ͬ��ƽ̨����Ҳ�������ڼ��������¹�
���豸�Ļ�����
*/

#include<iostream>
#include<map>

using namespace std;

class CCAudioManager
{
public:

	static CCAudioManager* SharedInstance();

	//��ʼ��
	void Init(int argc,char* argv[]);

	//��������
	ALboolean LoadBGMusic(string filename);

	//��������
	void PlayBGMusic(string filename);

	//��ͣ����
	void PauseBGMusic();

	//ֹͣ����
	void StopBGMusic();


	//������Ч
	ALboolean LoadEffectMusic(string filename);

	//������Ч
	void PlayEffectMusic(string filename);

	//��ͣ��Ч
	void PauseEffectMusic(string filename);

	//ֹͣ��Ч
	void StopEffectMusic(string filename);


	//���þ������ر�һ������
	void CloseAllSound();


	//�������ߵ�λ��-��ɫ��λ�� ��ɫ�ƶ�ʱҪ���½�ɫλ�õ�����
	void SetListener();


private:
	CCAudioManager(void);
	~CCAudioManager(void);


private:
	static CCAudioManager* m_Instance;

	ALuint m_SoundBuffer; //��������
	ALuint m_SoundSource; //��Դ


	typedef map<string,ALuint> SOUND_MAP; //������Map
	SOUND_MAP m_SoundMap;
};

