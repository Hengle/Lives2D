#pragma once

#include<vector>
#include"Image\Image.h"

class ImageAnimation
{
private:
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
	ImageAnimation(std::string varImageData[],int varKeyFrameCount,float varSpeed);
	~ImageAnimation();

	void Update(float varDeltaTime);

	void Draw();

	void Play();
};

