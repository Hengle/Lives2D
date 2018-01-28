//֡���� Ƭ�� ����

#pragma once

#include<string>
#include<vector>
#include"GUI/UIImage.h"

class ImageAnimationClip
{
private:
	std::string mClipName;

	std::vector<UIImage*> mVectorImageData;


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

	float mPosX;
	float mPosY;
	float mScaleX;
	float mScaleY;

public:
	std::string GetClipName();

public:
	ImageAnimationClip(std::string varClipName,std::vector<std::string> varVectorFrameImagePath,int varKeyFrameCount, float varSpeed);
	~ImageAnimationClip();


	void Update(float varDeltaTime);

	void Draw();

	void Play();

	void Stop();

	//����λ��
	void SetPosition(float varPosX, float varPosY);

	//��������
	void SetScale(float varScaleX, float varScaleY);
};

