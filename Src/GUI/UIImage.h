#pragma once

#include"GLProgram/GLProgram_Texture.h"
#include"GLProgram/GLProgram_Texture_ReceiveLightEffect.h"
#include"Texture2D/Texture2D.h"
#include"GUI/UIDrawRect.h"


class UIImage:public UIDrawRect
{
	DECLEAR_DYNCRT_ACTION(UIImage)
public:
	UIImage(void);
	~UIImage(void);

public:
	void  Init(const char* varFilePath); //����ͼƬ������Texture;

	//�Ƿ���ܵƹ�Ӱ��,��Init֮ǰ���ã������������ѡ��ͬ��Shader������UIImage
	void Init(const char* varFilePath, bool varReceiveLightEffect);

	//����
	void Draw() override;


	//����λ��
	void SetPosition(float varPosX, float varPosY);


	//��������
	void SetScale(float varScaleX, float varScaleY);

private:
	GLProgram_Texture* mGLProgram;
	Texture2D* mTexture2D;


	bool mReceiveLightEffect;///�Ƿ���ܵƹ�Ӱ��
public:
	float mPosX;
	float mPosY;
	float mScaleX;
	float mScaleY;
};

