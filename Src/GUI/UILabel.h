#pragma once

#include"UIDrawRect.h"
#include"Font.h"

class UILabel:public UIDrawRect
{

public:
	float mPosX;
	float mPosY;
	float mScaleX;
	float mScaleY;

private:
	Font& mFont;

public:
	UILabel();
	~UILabel();

public:
	void Init();

	//����				 
	void Draw() override;


	//����λ��
	void SetPosition(float varPosX, float varPosY);


	//��������
	void SetScale(float varScaleX, float varScaleY);
};