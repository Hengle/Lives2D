#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>
#include<string>

#include"png.h"

#include "../../Win32/xGame/xNativeEvent.h"

using namespace std;

#define LOG_TAG "xGame-GLES"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

GLuint g_GLProgram;  //
GLuint g_VertexShaderPositionHandle;//Vertex Shader��vPosition������Handle
GLuint g_VertexShaderTexCoordHande; //��������
GLuint g_FragShaderTexSamplerHandel; //����

GLuint g_TextureID; //���� �����������һ����


char g_SavePath[1024]={0};

jobject g_JavaObject;

//���GL�ı�����ֵ
static void PrintGLString(const char* name,GLenum s)
{
	const char *v=(const char *)glGetString(s);
	LOGI("GL %s = %s\n",name,v); //LOGI��ʽ���ַ���Ȼ���LOG
}

//���GL����
static void CheckGLError(const char* op)
{
	for(GLint error=glGetError();error;error=glGetError())
	{
		LOGI("after %s() glError (0x%x) \n",op,error);
	}
}

//����Shader
static const char g_VertexShader[]=
"attribute vec4 vPosition;\n" //��������
"attribute vec2 textureCoords;\n" //��������
"varying vec2 frag_textureCoords;\n" //�������괫��ƬԪ��ɫ��
"void main(){\n"
"frag_textureCoords=textureCoords;\n" //�Ѵ����д��������������괫��ƬԪ��ɫ����
"	gl_Position=vPosition;\n"
"}\n";

//ƬԪ��ɫ��
static const char g_FragmentShader[]=
              "precision mediump float;                            \n"
                        "varying vec2 frag_textureCoords;                            \n"
                        "uniform sampler2D s_texture;                        \n"
                        "void main()                                         \n"
                        "{                                                   \n"
                        "  gl_FragColor = texture2D( s_texture, frag_textureCoords );\n"
                        "}\n";

//����Shader
GLuint CreateShaderProgram(GLenum shaderType,const char* pSource)
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
GLuint CreateGLProgram(const char* pVertexSource,const char* pFragmentSource)
{
	LOGI("CreateGLProgram 1");
	GLuint vertexShader=CreateShaderProgram(GL_VERTEX_SHADER,pVertexSource);
	if(!vertexShader)
	{
		return 0;
	}
	LOGI("CreateGLProgram 2");
	GLuint fragmentShader=CreateShaderProgram(GL_FRAGMENT_SHADER,pFragmentSource);
	if(!fragmentShader)
	{
		return 0;
	}
	LOGI("CreateGLProgram 3");
	GLuint program=glCreateProgram();
	if(program)
	{
		glAttachShader(program,vertexShader);
		CheckGLError("glAttachShader");
		
		glAttachShader(program,fragmentShader);
		CheckGLError("glAttachShader");
		
		glLinkProgram(program);
		GLint linkStatus=GL_FALSE;
		
		LOGI("CreateGLProgram 4");
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
	LOGI("CreateGLProgram 5");
	return program;
}


//��ȡpngͼƬ
GLuint CreateTextureFromPng(const char* filename)
{
	LOGI("CreateTextureFromPng 1");
	LOGI(filename);
	unsigned char header[8]; //ͷ����Ϣ
	int k; //ѭ��
	GLuint textureID; //��������
	int width,height;
	png_byte color_type; //ͼƬ����
	png_byte bit_depth; //�ֽ����
	png_structp png_ptr; //ͼƬ
	png_infop info_ptr; //ͼƬ��Ϣ
	int number_of_passes; //����ɨ��
	png_bytep *row_pointers; //ͼƬ��������
	int row,col,pos; //���ڸı�png�������е�����
	GLubyte *rgba;
	FILE *fp=fopen(filename,"rb"); //ֻ����pngͼƬ
	LOGI("CreateTextureFromPng 2");
	if(!fp) //��ȡʧ��
	{
		LOGI("CreateTextureFromPng 21");
		//fclose(fp);
		return 0;
	}
	LOGI("CreateTextureFromPng 22");
	fread(header,1,8,fp); //��ȡ8���ֽ�
	LOGI("CreateTextureFromPng 23");
	if(png_sig_cmp(header,0,8)) //����pngͼƬ
	{
		LOGI("CreateTextureFromPng 24");
		fclose(fp);
		return 0;
	}
	//��ʼ��png_structp png_infop
	LOGI("CreateTextureFromPng 3");
	png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL); //�������������ô���ص�
	if(!png_ptr)  //��ʼ��ʧ��
	{
		fclose(fp);
		return 0;
	}

	//���ݳ�ʼ����png_ptr��ʼ��png_info
	info_ptr=png_create_info_struct(png_ptr);
	if(!info_ptr)
	{
		png_destroy_read_struct(&png_ptr,(png_infopp)NULL,(png_infopp)NULL);
		fclose(fp);
		return 0;
	}
	LOGI("CreateTextureFromPng 4");
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		//�ͷ��ڴ棬�ر��ļ�������һ����ͼID���˴�Ӧ����һ������Ĭ����ͼ����ID�ĺ���
		png_destroy_read_struct(&png_ptr,(png_infopp)NULL,(png_infopp)NULL);
		fclose(fp);
		return 0;
	}

	//ͨ��2���ƴ��ļ���ͨ��i/o���ƺ���png_init_io
	png_init_io(png_ptr,fp);

	png_set_sig_bytes(png_ptr,8); //png��־ͷ ����

	png_read_info(png_ptr,info_ptr); //ʵ�ʶ�ȡͼƬ��Ϣ

	width=png_get_image_width(png_ptr,info_ptr); //��ȡͼƬ���

	height=png_get_image_height(png_ptr,info_ptr); //��ȡͼƬ�߶�

	color_type=png_get_color_type(png_ptr,info_ptr); //��ȡͼƬ�ֽ���� λ���http://t.cn/8suqDV1

	//���ͼƬ����alphaͨ��
	//if(color_type==PNG_COLOR_TYPE_RGB_ALPHA)
	//{
	//	png_set_swap_alpha(png_ptr);
	//}
	LOGI("CreateTextureFromPng 5");
	bit_depth=png_get_bit_depth(png_ptr,info_ptr);

	number_of_passes=png_set_interlace_handling(png_ptr); //����ɨ��;

	png_read_update_info(png_ptr,info_ptr); //����ȡ������Ϣ���µ�info_ptr;

	if(setjmp(png_jmpbuf(png_ptr))) //���ļ�
	{
		fclose(fp);
		return 0;
	}

	rgba=(GLubyte*)malloc(width * height *4);

	//ʹ�ö�̬���� ���ó���
	row_pointers=(png_bytep*) malloc (sizeof(png_bytep)*height);
	LOGI("CreateTextureFromPng 6");
	for (k = 0; k < height; k++)
	{
		row_pointers[k]=NULL;
	}

	//ͨ��ɨ���������ÿһ�н��õ������ݸ�ֵ����̬����
	for(k=0;k<height;k++)
	{
		row_pointers[k]=(png_bytep)png_malloc(png_ptr,png_get_rowbytes(png_ptr,info_ptr));
	}
	LOGI("CreateTextureFromPng 7");
	//Png�Ǵ����� �Ӷ�����  ����ͼ��Ҫ�������� ������ �ӵ׵��� ����������Ҫ��������
	png_read_image(png_ptr,row_pointers);
	pos=(width*height*4)-(4*width);
	for (row = 0; row < height; row++)
	{
		for (col= 0; col< (4*width); col+=4)
		{
			rgba[pos++]=row_pointers[row][col]; //red
			rgba[pos++]=row_pointers[row][col+1]; //green
			rgba[pos++]=row_pointers[row][col+2]; //blue
			rgba[pos++]=row_pointers[row][col+3]; //alpha
		}
		pos=(pos-(width*4)*2);
	}
	LOGI("CreateTextureFromPng 8");
	//����������ͼ OpenGL ES2.0 ����Ҫ�������˻ᱨ�� invalid_enum
	//glEnable(GL_TEXTURE_2D);
	LOGI("CreateTextureFromPng 81");

	//��������
	glGenTextures(1,&textureID);
	LOGI("CreateTextureFromPng 82");
	CheckGLError("glGenTextures");
	//������
	glBindTexture(GL_TEXTURE_2D,textureID);
	LOGI("CreateTextureFromPng 83");
	CheckGLError("glBindTexture");
	
	 //������ͼ������Ļ��Ч��������Ĭ��ֻ������
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	//�����������õ�ͼƬ����
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,rgba);
	LOGI("CreateTextureFromPng 84");
	CheckGLError("glTexImage2D");

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	CheckGLError("glTexParameteri");
	LOGI("CreateTextureFromPng 9");
	free(row_pointers);
	fclose(fp);
	return textureID;
}


//��ʼ������
bool NativeInit(int width,int height)
{
	PrintGLString("Version",GL_VERSION);
	PrintGLString("Vendor",GL_VENDOR);//GL_VENDOR
	PrintGLString("Renderer",GL_RENDERER);
	PrintGLString("Extensions",GL_EXTENSIONS);
	
	LOGI("NativeInit(%d,%d)",width,height);
	
	//͸��
	glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	g_GLProgram=CreateGLProgram(g_VertexShader,g_FragmentShader);
	if(!g_GLProgram)
	{
		LOGE("Could not create program");
		return false;
	}
	//��ȡVertexShader�е�vPosition
	g_VertexShaderPositionHandle=glGetAttribLocation(g_GLProgram,"vPosition");
	CheckGLError("glGetAttribLocation");

	//��ȡ��������
	g_VertexShaderTexCoordHande=glGetAttribLocation(g_GLProgram,"textureCoords");
	CheckGLError("glGetAttribLocation");
	LOGI("g_VertexShaderTexCoordHande");

	//��������
	g_FragShaderTexSamplerHandel=glGetAttribLocation(g_GLProgram,"s_texture");
	CheckGLError("glGetAttribLocation");
	LOGI("g_FragShaderTexSamplerHandel");

	//�������ش洢ģʽ
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	CheckGLError("glPixelStorei");
	LOGI("glPixelStorei");

	//��������
	string savepath=g_SavePath;
	string filename=savepath+"/test.png";
	g_TextureID=CreateTextureFromPng(filename.c_str());
	LOGI("CreateTextureFromPng");


	LOGI("glGetAttribLocation(\"vPosition\")=%d\n",g_VertexShaderPositionHandle);
	glViewport(0,0,width,height);//�����ӿ�
	LOGI("glViewport width=%d,height=%d",width,height);
	CheckGLError("glViewport");

	return true;
}

const GLfloat g_Vertices[]=
{
	-0.75f,1.0f,0.0f, //Position 0
	0.0f,0.0f, //TexCoord 0
	-0.75f,-1.0f,0.0f, //Position 1
	0.0f,1.0f, //TexCoord1
	0.75f,-1.0f,0.0f, //Position 2
	1.0f,1.0f, //TexCoord 2
	0.75f,1.0f,0.0f, //Position 3
	1.0f,0.0f //TexCoord3
};

const GLushort indices[]={0,1,2,0,2,3};  //�����λ��Ʒ�ʽ triangle_strip

GLsizei stride=5*sizeof(GLfloat); //���5  ���궥��3  ������2


void NativeDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(g_GLProgram);
	CheckGLError("glUseProgram");

	//���ض�������
	glVertexAttribPointer(g_VertexShaderPositionHandle,3,GL_FLOAT,GL_FALSE,stride,g_Vertices);
	CheckGLError("glVertexAttribPointer");

	//������������
	glVertexAttribPointer(g_VertexShaderTexCoordHande,2,GL_FLOAT,GL_FALSE,stride,&g_Vertices[3]);

	glEnableVertexAttribArray(g_VertexShaderPositionHandle);
	glEnableVertexAttribArray(g_VertexShaderTexCoordHande);
	CheckGLError("glEnableVertexAttribArray");


	glActiveTexture(GL_TEXTURE0);
	CheckGLError("glActiveTexture");
	glBindTexture(GL_TEXTURE_2D,g_TextureID);
	CheckGLError("glBindTexture");

	//�������� Ϊ0
	glUniform1i(g_FragShaderTexSamplerHandel,0);
	CheckGLError("glUniform1i");

	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,indices);
	CheckGLError("glDrawElements");
}


void NativeTouch(float x,float y,TOUCH_EVENT event)
{
	LOGI("NativeTouch x = %f y=%f event=%d",x,y,(int)event);
	switch(event)
	{
		case TOUCH_DOWN:
			LOGI("NativeTouch x = %f y=%f event=TOUCH_DOWN",x,y);
			break;
		case TOUCH_UP:
			LOGI("NativeTouch x = %f y=%f event=TOUCH_UP",x,y);
			break;
		case TOUCH_MOVE:
			LOGI("NativeTouch x = %f y=%f event=TOUCH_MOVE",x,y);
			break;
		default:
			break;
	}
}

extern "C"
{
	JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnCreate(JNIEnv* env,jclass obj,jint width,jint height);
	JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeSetDataPath(JNIEnv* env,jclass obj,jstring savepath);
	JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnUpdate(JNIEnv* env,jclass obj);
	JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnDraw(JNIEnv *env,jclass obj);
	JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnTouch(JNIEnv *env,jclass obj,jfloat x,jfloat y,jint touchtype);
}

//����render
JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnCreate(JNIEnv* env,jclass obj,jint width,jint height)
{
	NativeInit(width,height);
}

//������Դ�洢·��
JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeSetDataPath(JNIEnv* env,jclass obj,jstring savepath)
{
	g_JavaObject=obj;

	jboolean bRet;
	const char *savepathCStr=env->GetStringUTFChars(savepath,&bRet); //��ȡsavepath
	memset(g_SavePath,0,1024);
	memcpy(g_SavePath,savepathCStr,strlen(savepathCStr)); //����

	LOGI("g_SavePath = %s",g_SavePath);

	env->ReleaseStringUTFChars(savepath,savepathCStr); //֪ͨ���������ڴ治�ٱ����ʣ���Ҫ�ͷ� (*env)->ReleaseStringUTFChars(env, jstring, str);
}

//Update
JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnUpdate(JNIEnv* env,jclass obj)
{
	
}

//Draw
JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnDraw(JNIEnv *env,jclass obj)
{
	NativeDraw();
}

//��Ļ����¼�
JNIEXPORT jint JNICALL Java_com_teamtop_xgame_GameNativeInterface_nativeOnTouch(JNIEnv *env,jclass obj,jfloat x,jfloat y,jint touchevent)
{
	NativeTouch((float)x,(float)y,(TOUCH_EVENT)touchevent);
}

string NativeJstringToString(JNIEnv *env,jclass obj,jstring jstr)
{
	char charArray[1024]={0};
	jboolean bRet;
	const char *cstr=env->GetStringUTFChars(jstr,&bRet);
	memset(charArray,0,strlen(cstr));
	env->ReleaseStringUTFChars(jstr,cstr);
	return string(charArray);
}
