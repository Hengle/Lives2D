#pragma once

enum  UIRectType
{
	Type_UIClickRect=0,
	Type_UIDrawRect=1,
};

//UIRect is base of ui widget
class UIRect
{
private:
	int mDepth; //Depth use to control front or back

	UIRectType mUIRectType;

public:
	UIRect(UIRectType varUIRectType);
	~UIRect();

public:


	//�������
	void SetDepth(int varDepth);

	//��ȡ���
	int GetDepth();


	virtual void Update(float varDeltaTime) {};

	//����
	virtual void Draw() {};
};

