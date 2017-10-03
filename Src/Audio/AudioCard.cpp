#pragma once

#ifdef WIN32
#include"AL\alut.h"

void AudioCardInit()
{
	ALboolean tmpRet=alutInit(0, 0);
}

void AudioCardExit()
{
	alutExit();
}

#elif ANDROID
#include <jni.h>
#include"Tools\Helper.h"

JNIEnv* mJNIEnv;
jclass mjclass;
jobject mjobject;
jmethodID mjmethodID_PlayAudio;
void AudioCardInit(JNIEnv* env, jobject thiz)
{
	Helper::LOG("AudioCardInit");
	mJNIEnv=env;
	jclass clazz = env->GetObjectClass(thiz); //��ȡ��ǰ���������Ϣ
	if(clazz==NULL)
	{
		Helper::LOG("env->GetObjectClass(thiz) NULL");
		return;
	}
	mjclass = (jclass)env->NewGlobalRef(clazz); //��������Ϣ�洢��m_class��  
	if(mjclass==NULL)
	{
		Helper::LOG("env->NewGlobalRef(clazz) NULL");
		return;
	}
	
	mjobject = thiz;
	
	// = (jobject)env->NewGlobalRef(thiz); // ��������Ϣ�洢��m_object��
	//if(mjobject==NULL)
	//{
	//	Helper::LOG("env->NewGlobalRef(thiz) NULL");
	//	return;
	//}
	mjmethodID_PlayAudio = env->GetMethodID(mjclass, "PlayAudio", "(Ljava/lang/String)V");  // ��������Ϣ������������������ֵ�ҵ�����ID
	if(mjmethodID_PlayAudio ==NULL)
	{
		Helper::LOG("mjmethodID_PlayAudio NULL");
		return;
	}
}

void AudioCardPlay(const char* varAudioPath)
{
	Helper::LOG("AudioCardPlay 0 %s", varAudioPath);
	mJNIEnv->CallVoidMethod(mjobject,mjmethodID_PlayAudio,varAudioPath);
	Helper::LOG("AudioCardPlay 1 %s", varAudioPath);
}

void AudioCardExit()
{
	
}

#endif


