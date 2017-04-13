#pragma once
#include"FreeImage.h"
#include<gles2\gl2.h>
#include<string>

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

public:
	std::string m_imageFilePath;//�ļ�·��;
	GLuint m_textureId;

	int mTextureWidth;
	int mTextureHeight;

public:
	void  LoadTexture(const char* varFilePath); //����ͼƬ������Texture;
};

