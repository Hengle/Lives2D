#pragma once
#include<assert.h>

#if IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include<egl\egl.h>
#include<gles2\gl2.h>
#endif
#include"../Tools/Helper.h"	

class ShaderProperty
{
public:
	const char* mName; //����
	GLint mID;
	const char* mValueType;
};

class ShaderPropertyFloat:public ShaderProperty
{
public:
	float mValue;
};


//��װOpenGL ��glProgram��һЩ��Ϣ;
class Shader
{
public:
	int mProgram;
	GLuint mVertexShader;
	GLuint mFragmentShader;


public:
	Shader()
	{
		mProgram = -1;
	}

public:
	//����shader���Ҵ���glProgram;
	bool CreateProgram(const char *vertex, const char *fragment)
	{
		bool error = false;
		do
		{
			if (vertex)
			{
				//����Shader;
				mVertexShader = glCreateShader(GL_VERTEX_SHADER);
				//Դ��;
				glShaderSource(mVertexShader, 1, &vertex, 0);
				//����;
				glCompileShader(mVertexShader);

				GLint compileStatus;
				glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &compileStatus);

				error = (compileStatus == GL_FALSE);
				if (error)
				{
					GLchar message[256];
					glGetShaderInfoLog(mVertexShader, sizeof(message), 0, message);

					LOGI("message %s", message);
					assert((message && 0) != 0);
					break;
				}
			}

			if (fragment)
			{
				//����Shader;
				mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				//Դ��;
				glShaderSource(mFragmentShader, 1, &fragment, 0);
				//����;
				glCompileShader(mFragmentShader);

				GLint compileStatus;
				glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &compileStatus);

				error = (compileStatus == GL_FALSE);
				if (error)
				{
					GLchar message[256];
					glGetShaderInfoLog(mFragmentShader, sizeof(message), 0, message);
					assert((message && 0) != 0);
					break;
				}
			}

			//����gl����;
			mProgram = glCreateProgram();

			//������ӵ�program��;
			if (mVertexShader)
			{
				glAttachShader(mProgram, mVertexShader);
			}
			if (mFragmentShader)
			{
				glAttachShader(mProgram, mFragmentShader);
			}

			//����;
			glLinkProgram(mProgram);

			GLint linkStatus;
			glGetProgramiv(mProgram, GL_LINK_STATUS, &linkStatus);

			if (linkStatus == GL_FALSE)
			{
				GLchar message[256];
				glGetProgramInfoLog(mProgram, sizeof(message), 0, message);
				assert((message && 0) != 0);
				break;
			}

			//ʹ��program;
			//glUseProgram(mProgram);

		} while (false);
		
		if (error)
		{
			if (mFragmentShader)
			{
				glDeleteShader(mFragmentShader);
				mFragmentShader = 0;
			}

			if (mVertexShader)
			{
				glDeleteShader(mVertexShader);
				mVertexShader = 0;
			}

			if (mProgram)
			{
				glDeleteProgram(mProgram);
				mProgram = 0;
			}
		}

		return true;
	}

	virtual void begin()
	{
		glUseProgram(mProgram);
	}

	virtual void end()
	{
		glUseProgram(0);
	}
};
