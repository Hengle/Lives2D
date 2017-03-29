#include "CCImage.h"
#include "CCOGL.h"


extern unsigned int ShaderGLPrograms[SHADER_GL_PROGRAM_COUNT]; //ÿһ��Shader����һ��GL Program

CCImage::CCImage(void)
{
	m_imageFileName="";
	m_textureId=0;
}


//����ͼƬ·��
void CCImage::SetImageFile(const string filename)
{
	m_imageFileName=filename;
	LOGI("m_imageFileName = %s\n",m_imageFileName.c_str());
}

GLfloat g_PositionVertices[12]=
{
	0.0f,1.0f,0.0f, //Position 0
	0.0f,0.0f,0.0f, //Position 1
	1.0f,0.0f,0.0f, //Position 2
	1.0f,1.0f,0.0f //Position 3
};

GLfloat g_TexCoordVertices[8]=
{
	0.0f,1.0f, //TexCoord 0
	0.0f,0.0f, //TexCoord1
	1.0f,0.0f, //TexCoord 2
	1.0f,1.0f //TexCoord3
};


const GLushort indices[]={0,1,2,0,2,3};  //�����λ��Ʒ�ʽ triangle_strip

GLsizei stride1=5*sizeof(GLfloat); //���5  ���궥��3  ������2

GLuint g_VertexShaderPositionHandle;//Vertex Shader��vPosition������Handle
GLuint g_VertexShaderTexCoordHandel; //��������
GLuint g_FragShaderTexSamplerHandel; //����

void CCImage::DrawImage(float x,float y,float w,float h)
{
	DrawImage(x,y,w,h,0);
}

void CCImage::DrawImage(float x,float y,float w,float h,int z)
{
	//����Texture
	if(m_textureId==0)
	{
		m_textureId=CCTexture::CreateTextureFromPng(m_imageFileName.c_str());

		LOGI("textureId = %d \n",m_textureId);
	}

	//����λ��
	g_PositionVertices[0]=x;
	g_PositionVertices[1]=y+h;
	g_PositionVertices[2]=z;

	g_PositionVertices[3]=x;
	g_PositionVertices[4]=y;
	g_PositionVertices[5]=z;

	g_PositionVertices[6]=x+w;
	g_PositionVertices[7]=y;
	g_PositionVertices[8]=z;

	g_PositionVertices[9]=x+w;
	g_PositionVertices[10]=y+h;
	g_PositionVertices[11]=z;

	
    

	//��ȡVertexShader�е�vPosition
	g_VertexShaderPositionHandle=glGetAttribLocation(ShaderGLPrograms[SHADER_GL_PROGRAM_NORMAL],"vPosition");
	Helper::CheckGLError("glGetAttribLocation");

	//��ȡ��������
	g_VertexShaderTexCoordHandel=glGetAttribLocation(ShaderGLPrograms[SHADER_GL_PROGRAM_NORMAL],"textureCoords");
	Helper::CheckGLError("glGetAttribLocation");
	//LOGI("g_VertexShaderTexCoordHandel\n");

	//��������
	g_FragShaderTexSamplerHandel=glGetAttribLocation(ShaderGLPrograms[SHADER_GL_PROGRAM_NORMAL],"s_texture");
	Helper::CheckGLError("glGetAttribLocation");
	//LOGI("g_FragShaderTexSamplerHandel\n");


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//���ض�������
	glVertexAttribPointer(g_VertexShaderPositionHandle,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),&g_PositionVertices);
	Helper::CheckGLError("glVertexAttribPointer");

	//������������
	glVertexAttribPointer(g_VertexShaderTexCoordHandel,2,GL_FLOAT,GL_FALSE,2*sizeof(GLfloat),&g_TexCoordVertices);

	glEnableVertexAttribArray(g_VertexShaderPositionHandle);
	glEnableVertexAttribArray(g_VertexShaderTexCoordHandel);
	Helper::CheckGLError("glEnableVertexAttribArray");

	//͸��
	glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	Helper::CheckGLError("glActiveTexture");
	glBindTexture(GL_TEXTURE_2D,m_textureId);
	Helper::CheckGLError("glBindTexture");

	//�������� Ϊ0 ,û���õ�������
	glUniform1i(g_FragShaderTexSamplerHandel,0);
	Helper::CheckGLError("glUniform1i");

	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,indices);
	Helper::CheckGLError("glDrawElements");

}


CCImage::~CCImage(void)
{
}
