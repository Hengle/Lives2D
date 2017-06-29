#pragma once

#include"UIClickRect.h"
#include"Image\Image.h"

#include<string>
#include<functional>

class UIButton:public UIClickRect
{
private:
	float mPosX, mPosY, mWidth, mHeight;

	Image* mImageNormal;		//������ʾ��ͼƬ
	Image* mImageClickDown;		//���µ�ͼƬ

	bool mClickDown;		//�Ƿ���

	std::function<void(void)> mOnClick;//����ص�

public:
	UIButton(std::string varNormalImagePath,std::string varClickDownImagePath,float varPosX,float varPosY,float varWidth,float varHeight, std::function<void(void)> varOnClick);
	~UIButton();


	void Update(float varDeltaTime) override final;

	void Draw() override final;

	void OnTouchClickRect(float varX, float varY) override final;

	void OnTouchReleaseClickRect(float varX, float varY) override final;
};

