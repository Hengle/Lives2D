#pragma once

#include"GLProgram\GLProgram_Texture.h"
#include"Texture2D\Texture2D.h"
#include"Image\Image.h"


class Lives2D
{
public:
	static int m_Width;
	static int m_Height;

	static float m_DesignWidth;
	static float m_DesignHeight;

	//����һ��ͼƬ
	static Image* mImage;

public:

	//��ʼ��
	static void Init(EGLSurface& varEGLSurface, EGLDisplay& varEGLDisplay, int& varWidth, int& varHeight);

	//ˢ֡
	static void Update(float varDeltaTime);

	//����
	static void Draw();

};


