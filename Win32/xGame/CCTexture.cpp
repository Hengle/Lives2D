#include "CCTexture.h"
#include"FreeImage.h"


using namespace std;


CCTexture::CCTexture(void)
{
}

///��Png�ļ�����Texture
GLuint CCTexture::CreateTextureFromPng(const char* filename)
{
	GLuint textureID; //��������

	// 1����ȡͼƬ��ʽ;
	FREE_IMAGE_FORMAT imageformat = FreeImage_GetFileType(filename, 0);

	//2�����ݻ�ȡ���ĸ�ʽ������ͼƬ;
	FIBITMAP *bitmap = FreeImage_Load(imageformat, filename, 0);

	//3��ת��Ϊrag 24ɫ;
	bitmap = FreeImage_ConvertTo32Bits(bitmap);

	//4����ȡ����ָ��;
	BYTE *pixels = (BYTE*)FreeImage_GetBits(bitmap);
	//5��ʹ��;
	int width = FreeImage_GetWidth(bitmap);
	int height = FreeImage_GetHeight(bitmap);

	for (int i = 0; i < width* height * 4; i += 4)
	{
		BYTE r = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = r;
	}

	
	//����������ͼ OpenGL ES2.0 ����Ҫ�������˻ᱨ�� invalid_enum
	//glEnable(GL_TEXTURE_2D);
	//LOGI("CreateTextureFromPng 81 \n");

	//��������
	glGenTextures(1,&textureID);
	//LOGI("CreateTextureFromPng 82 \n");
	Helper::CheckGLError("glGenTextures");
	//������
	glBindTexture(GL_TEXTURE_2D,textureID);
	//LOGI("CreateTextureFromPng 83 \n");
	Helper::CheckGLError("glBindTexture");

	 //������ͼ������Ļ��Ч��������Ĭ��ֻ������
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//�����������õ�ͼƬ����
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE, pixels);
	//LOGI("CreateTextureFromPng 84 \n");
	Helper::CheckGLError("glTexImage2D");

	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Helper::CheckGLError("glTexParameteri");

	//LOGI("CreateTextureFromPng 9 \n");
	//�ͷ��ڴ�;
	FreeImage_Unload(bitmap);

	return textureID;
}


CCTexture::~CCTexture(void)
{
}
