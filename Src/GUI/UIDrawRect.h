#pragma once

#include"UIRect.h"


//UIDrawRect is base of ui widget
class UIDrawRect:public UIRect
{
public:
	UIDrawRect();
	~UIDrawRect();

public:
	//����
	virtual void Draw() {};


};

