#pragma once

#include"../KeyTouch/KeyTouchListener.h"
#include"UIRect.h"

class UIClickRect:public UIRect,public KeyTouchListener
{
private:
	float mPosX, mPosY, mWidth, mHeight; //�������

	bool mOnTouchClick;//��ǰ�Ƿ���

public:
	UIClickRect();
	~UIClickRect();

	
	

	void OnKey(KeyCode varkeyCode) override final;

	void OnTouch(int varX, int varY) override final;

	//�ͷŵ��
	void OnTouchRelease(int varX, int varY) override final;



	virtual void OnTouchClickRect(float varX, float varY)=0;

	virtual void OnTouchReleaseClickRect(float varX, float varY) = 0;

protected:
	void UpdateRect(float varPosX, float varPosY, float varWidth, float varHeight);//���õ����Χ
};

