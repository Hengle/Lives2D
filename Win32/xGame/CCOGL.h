#pragma once

#include"Helper.h"
#include"ShaderNormal.h"
#include"CCTexture.h"
#include"ShaderTest.h"
#include"CCEngine.h"

enum SHADER_GL_PROGRAM_ID
{
	SHADER_GL_PROGRAM_NONE=-1,
	SHADER_GL_PROGRAM_NORMAL=0,
	SHADER_GL_PROGRAM_COUNT=1
};

class CCOGL
{
public:
	CCOGL(void);
	~CCOGL(void);

	//��ʼ��
	static bool NativeInit(int argc,char* argv[],int width,int height);

	//��Ⱦ
	static void NativeRender();

	static void NativeDraw();

	static void NativeUpdate();

	static void ChangeSize(int w,int h);

	static void ProcessNormalKeys(unsigned char key,int x,int y);

	static void CreateShadersGLPrograms();

	static void CompileShader(GLuint &shaderprogram,const string &shadername);

	//����Shader
	static GLuint CreateShaderProgram(GLenum shaderType,const char* pSource);

	//����GL����
	static GLuint CreateGLProgram(const char* pVertexSource,const char* pFragmentSource);

	//���ÿ��
	static void SetWidthHeight(int w,int h);

	static int GetWindowWidth();

	static int GetWindowHeight();

private:
	static int m_Width;
	static int m_Height;

};

