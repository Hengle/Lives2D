#pragma once

#include"UIDrawRect.h"
#include"Font.h"
#include"GLProgram/GLProgram_Font.h"


class UILabel:public UIDrawRect
{
	DECLEAR_DYNCRT_ACTION(UILabel)
public:
	float mPosX;
	float mPosY;
	float mScaleX;
	float mScaleY;

private:
	Font* mFont;

	GLProgram_Font m_GLProgram_Font;

	//����ʹ��GL_ALPHA��ʽ;
	unsigned int m_fontTexture;//����Texutre;

	UIVertex  vert[1024];

	std::string mText;

	int mSpace;//�ּ��

	bool mAlignCenter;//���ж���

public:
	UILabel();
	~UILabel();

public:
	void Init(const char* varText);

	//����				 
	void Draw() override;


	//����λ��
	void SetPosition(float varPosX, float varPosY);


	//��������
	void SetScale(float varScaleX, float varScaleY);

	//�����ּ��
	void SetSpace(int varSpace);

	//���þ��ж���
	void SetAlignCenter(bool varAlignCenter);
};
