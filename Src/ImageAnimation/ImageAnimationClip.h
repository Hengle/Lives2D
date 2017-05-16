//֡���� Ƭ�� ����

#pragma once

#include<string>
#include<vector>
#include"Image\Image.h"

class ImageAnimationClip
{
private:
	std::string mClipName;

	std::vector<Image*> mVectorImageData;


	//�Ƿ��ڲ���
	bool mPlay;

	//��ǰ����ʱ��
	float mPlayTime;

	//��֡��
	int mKeyFrameCount;

	//��ǰ֡
	int mIndex;

	//�����ٶ�
	float mSpeed;

public:
	std::string GetClipName();

public:
	ImageAnimationClip(std::string varClipName,std::vector<std::string> varVectorFrameImagePath,int varKeyFrameCount, float varSpeed);
	~ImageAnimationClip();


	void Update(float varDeltaTime);

	void Draw();

	void Play();

	void Stop();
};

