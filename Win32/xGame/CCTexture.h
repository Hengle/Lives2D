#pragma once

#include<iostream>
#include"Helper.h"

class CCTexture
{
public:
	CCTexture(void);
	~CCTexture(void);

	///��Png�ļ�����Texture
	static GLuint CreateTextureFromPng(const char* filename);



private:
	GLuint m_TextureID;
	
};
