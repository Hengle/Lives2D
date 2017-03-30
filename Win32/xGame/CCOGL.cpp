#include "CCOGL.h"
#include "CCSceneManager.h"
#include "CCAudioManager.h"



unsigned int ShaderGLPrograms[SHADER_GL_PROGRAM_COUNT]; //ÿһ��Shader����һ��GL Program


GLuint v,f,p;
float lpos[4]={1,0.5,1,0};


GLuint g_GLProgram;  //


GLuint g_TextureID; //���� �����������һ����

char g_SavePath[1024]={0};


int CCOGL::m_Width;
int CCOGL::m_Height;

CCOGL::CCOGL(void)
{
	m_Width=0;
	m_Height=0;
}

void CCOGL::ChangeSize(int w,int h)
{
	if(h==0)
	{
		h=1;
	}
	float ratio=1.0*w/h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,w,h);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void CCOGL::NativeRender()
{
	static int begintime=0;
	static int endtime=0;
	if(endtime-begintime>((1/60)*1000))
	{
		begintime=GetTickCount();
		CCSceneManager::SharedInstance()->Draw();
		CCSceneManager::SharedInstance()->Update();
	}
	endtime=GetTickCount();
	Sleep(1);
	
}

void CCOGL::ProcessNormalKeys(unsigned char key,int x,int y)
{
	if(key==27)
	{
		exit(0);
	}
}


bool CCOGL::NativeInit(int argc,char* argv[],int width,int height)
{
	glutInit(&argc,argv);    //��ʼ��glut,������ã����������仰����  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //������ʾ��ʽ��RGB�������塣��Ȼ����GLUT_INDEX������ɫ GLUT_DOUBLE˫����(Qt�п�����˫����)  
	glutInitWindowPosition(100,100);   //λ��
	glutInitWindowSize(width,height);//���ڴ�С
	glutCreateWindow("CCEngine-2D");  //�������ڣ����ñ���

	glClearColor(1.0,1.0,1.0,1.0);

	glutDisplayFunc(NativeRender);  // �����ƴ���ʱ����myDisplay

	glutIdleFunc(NativeRender);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(ProcessNormalKeys);
	glEnable(GL_DEPTH_TEST);



	
	glewInit();
	if(glewIsSupported("GL_VERSION_2_0"))
	{
		printf("Ready for OpenGL 2.0\n");
	}
	else
	{
		printf("OpenGL 2.0 not supported\n");
		return false;
	}

	//ÿһ��Shader����һ��GLProgram
	CreateShadersGLPrograms();

	//�������ش洢ģʽ
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	Helper::CheckGLError("glPixelStorei");
	LOGI("glPixelStorei\n");

	glViewport(0,0,width,height);//�����ӿ�
	LOGI("glViewport width=%d,height=%d",width,height);
	Helper::CheckGLError("glViewport");

	glUseProgram(ShaderGLPrograms[SHADER_GL_PROGRAM_NORMAL]);

	CCSceneManager::SharedInstance()->RegisterAllScene();//ע�����еĳ���

	CCAudioManager::SharedInstance()->Init(argc,argv);//��ʼ��OpenAL


	glutMainLoop();  //��Ϣѭ��
	return false;
}


//����Shader
GLuint CCOGL::CreateShaderProgram(GLenum shaderType,const char* pSource)
{
	GLuint shader=glCreateShader(shaderType); //����ָ����shader����
	if(shader)
	{
		glShaderSource(shader,1,&pSource,NULL); //����ɫ������Դ�����ַ�����󶨵���Ӧ����ɫ������
		glCompileShader(shader);//����shader
		GLint compiled=0;
		glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled); //����shader
		if(!compiled)
		{
			GLint infoLen=0;
			glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLen);
			if(infoLen)
			{
				char* buf=(char*)malloc(infoLen);
				if(buf)
				{
					glGetShaderInfoLog(shader,infoLen,NULL,buf);
					LOGE("Could not compile shader %d:\n%s\n",shaderType,buf); //���������Ϣ
					free(buf);
				}
				glDeleteShader(shader); //����Shaderʧ���ˣ�ɾ��shader����
				shader=0;
			}
		}
	}
	return shader;
}

//����GL����
GLuint CCOGL::CreateGLProgram(const char* pVertexSource,const char* pFragmentSource)
{
	LOGI("CreateGLProgram 1 \n");
	GLuint vertexShader=CreateShaderProgram(GL_VERTEX_SHADER,pVertexSource);
	if(!vertexShader)
	{
		return 0;
	}
	LOGI("CreateGLProgram 2 \n");
	GLuint fragmentShader=CreateShaderProgram(GL_FRAGMENT_SHADER,pFragmentSource);
	if(!fragmentShader)
	{
		return 0;
	}
	LOGI("CreateGLProgram 3 \n");
	GLuint program=glCreateProgram();
	if(program)
	{
		glAttachShader(program,vertexShader);
		Helper::CheckGLError("glAttachShader");
		
		glAttachShader(program,fragmentShader);
		Helper::CheckGLError("glAttachShader");
		
		glLinkProgram(program);
		GLint linkStatus=GL_FALSE;
		
		LOGI("CreateGLProgram 4 \n");
		glGetProgramiv(program,GL_LINK_STATUS,&linkStatus); //��ȡ���
		if(linkStatus!=GL_TRUE) //���ʧ��
		{
			GLint bufLength=0;
			glGetProgramiv(program,GL_INFO_LOG_LENGTH,&bufLength); //��ȡʧ����Ϣ����
			if(bufLength)
			{
				char* buf=(char*)malloc(bufLength); 
				if(buf)
				{
					glGetProgramInfoLog(program,bufLength,NULL,buf); //��ȡʧ����Ϣ
					LOGE("could not link program:\n%s\n",buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			program=0;
		}
	}
	LOGI("CreateGLProgram 5 \n");
	return program;
}


void CCOGL::CreateShadersGLPrograms()
{
	CompileShader(ShaderGLPrograms[SHADER_GL_PROGRAM_NORMAL],"ShaderNormal");
}

void CCOGL::CompileShader(GLuint &shaderprogram,const string &shadername)
{
	if(shaderprogram!=0) //�Ѿ�����������ShaderProgram
	{
		return;
	}
	if(shadername=="ShaderNormal")
	{
		shaderprogram=CreateGLProgram(g_VertexShaderNormal,g_FragmentShaderNormal);
	}

}


//���ÿ��
void CCOGL::SetWidthHeight(int w,int h)
{
	m_Width=w;
	m_Height=h;
}

int CCOGL::GetWindowWidth()
{
	return m_Width;
}

int CCOGL::GetWindowHeight()
{
	return m_Height;
}

CCOGL::~CCOGL(void)
{
}
