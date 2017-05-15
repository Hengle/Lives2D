#pragma once

#include<vector>
#include"Image\Image.h"

class ImageAnimation
{
private:
	std::vector<Image*> mVectorImageData;

	//是否在播放
	bool mPlay;

	//当前播放时间
	float mPlayTime;

	//总帧数
	int mKeyFrameCount;

	//当前帧
	int mIndex;

	//播放速度
	float mSpeed;


public:
	ImageAnimation(std::string varImageData[],int varKeyFrameCount,float varSpeed);
	~ImageAnimation();

	void Update(float varDeltaTime);

	void Draw();

	void Play();
};

