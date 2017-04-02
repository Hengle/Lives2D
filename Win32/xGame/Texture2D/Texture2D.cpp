#include "Texture2D.h"


Texture2D::Texture2D():m_textureId(-1),m_imageFilePath("")
{
	
}

void Texture2D::LoadTexture(const char* varFilePath)
{
	m_imageFilePath = std::string(varFilePath);

	//1����ȡͼƬ��ʽ;
	FREE_IMAGE_FORMAT imageformat = FreeImage_GetFileType(varFilePath, 0);

	//2�����ݻ�ȡ���ĸ�ʽ������ͼƬ;
	FIBITMAP *bitmap = FreeImage_Load(imageformat, varFilePath, 0);

	//3��ת��Ϊrag 24ɫ;
	bitmap = FreeImage_ConvertTo32Bits(bitmap);

	//4����ȡ����ָ��;
	BYTE *pixels = (BYTE*)FreeImage_GetBits(bitmap);

	//5��ʹ��;
	int width = FreeImage_GetWidth(bitmap);
	int height = FreeImage_GetHeight(bitmap);

	//6���������ݣ������ȷ����ɫ ����1��3 RGB ԭ���洢���� BGR?;
	for (int i = 0; i < width * height * 4; i += 4)
	{
		BYTE r = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = r;
	}

	//1������һ������ID;
	glGenTextures(1, &m_textureId);

	//2���������������ID;
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	//3��ָ���Ŵ���С�˲���ʽ�������˲������Ŵ���С�Ĳ�ֵ��ʽ;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//��ͼƬrgb�����ϴ���OpenGL,����һ���Ű����ݴ��ڴ�Copy���Դ�;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	//�ͷ��ڴ�;
	FreeImage_Unload(bitmap);
}


Texture2D::~Texture2D()
{
}
