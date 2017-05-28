#pragma once

#include"../KeyTouch/KeyTouchListener.h"

class UIClickRect:KeyTouchListener
{
private:
	float mPosX, mPosY, mWidth, mHeight; //�������

	bool mOnTouchClick;//��ǰ�Ƿ���

public:
	UIClickRect();
	~UIClickRect();

	
	

	void OnKey(KeyCode varkeyCode) override final;

	void OnTouch(float varX, float varY) override final;

	//�ͷŵ��
	void OnTouchRelease(float varX, float varY) override final;



	virtual void OnTouchClickRect(float varX, float varY)=0;

	virtual void OnTouchReleaseClickRect(float varX, float varY) = 0;

protected:
	void UpdateRect(float varPosX, float varPosY, float varWidth, float varHeight);//���õ����Χ
};

