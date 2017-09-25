#pragma once

#include"KeyTouchListener.h"

#include<vector>

class KeyTouch
{
public:
	KeyTouch();
	~KeyTouch();

private:
	static std::vector<KeyTouchListener*> mVectorKeyTouchListener;

public:
	static void RegisterKeyTouchListener(KeyTouchListener* varKeyTouchListener);

	static void UnRegisterKeyTouchListener(KeyTouchListener* varKeyTouchListener);


	//�������
	static void OnKey(int varkeyCode);

	//��Ļ�������
	static void OnTouch(int varX, int varY);

	//�ͷŵ��
	static void OnTouchRelease(int varX, int varY);
};


