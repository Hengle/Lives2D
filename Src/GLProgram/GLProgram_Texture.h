#pragma once
#include"GLProgram.h"

class GLProgram_Texture :public GLProgram
{
public:

	//����shader�е�ֵ;
	GLint m_position;
	GLint m_color;
	GLint m_mvp;

	GLint m_texture;
	GLint m_uv;

public:
	GLProgram_Texture()
	{
		m_position = -1;
		m_color = -1;
		m_mvp = -1;

		m_texture = -1;
		m_uv = -1;
	}

	~GLProgram_Texture()
	{}

	GLint getPositionAttribute() const
	{
		return m_position;
	}

	GLint getColorAttribute() const
	{
		return m_color;
	}

	GLint getMVP() const
	{
		return m_mvp;
	}

	//attribute:ֻ����Vertexshader��ʹ��;
	//Unifrom:��Vertex��Fragment�й���ʹ��,�Ҳ��ܱ��޸�;
	//Varying:��Vertex�������ݵ�Fragment��ʹ��;
	virtual bool Initialize()
	{
		const char* vertexShader=
		{
			"precision lowp float;"
			"uniform mat4 m_mvp;"
			"attribute vec3 m_position;"
			"attribute vec4 m_color;"
			"attribute vec2 m_uv;"

			"varying vec4 m_outColor;"
			"varying vec2 m_outUV;"

			"void main()"
			"{"
			"	vec4 pos=vec4(m_position,1);"
			"	gl_Position=m_mvp*pos;"
			"	m_outColor=m_color;"
			"	m_outUV=m_uv;"
			"}"
		};

		const char* fragmentShader =
		{
			"precision lowp float;"
			"uniform sampler2D m_texture;"

			"varying vec4 m_outColor;"
			"varying vec2 m_outUV;"

			"void main()"
			"{"
			"	gl_FragColor=m_outColor*texture2D(m_texture,m_outUV);"
			"}"
		};

		bool ret = createProgram(vertexShader, fragmentShader);
		if (ret)
		{
			m_position = glGetAttribLocation(m_programId, "m_position");
			m_color = glGetAttribLocation(m_programId, "m_color");
			m_mvp = glGetUniformLocation(m_programId, "m_mvp");

			m_uv = glGetAttribLocation(m_programId, "m_uv");
			m_texture = glGetUniformLocation(m_programId, "m_texture");
		}
		return ret;
	}

	virtual void begin()
	{
		glUseProgram(m_programId);

		// Enable depth test
		//glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		//glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glEnableVertexAttribArray(m_position);
		glEnableVertexAttribArray(m_color);
		glEnableVertexAttribArray(m_uv);
	}

	virtual void end()
	{
		glDisable(GL_BLEND);

		glDisableVertexAttribArray(m_position);
		glDisableVertexAttribArray(m_color);
		glDisableVertexAttribArray(m_uv);
		glUseProgram(0);
	}
};