#include "Image.h"

#include"Game2D_Main\Game2D.h"
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtx\transform2.hpp>
#include<glm\gtx\euler_angles.hpp>


Image::Image(void)
{
	mTexture2D = new Texture2D();
}




Image::~Image(void)
{
}

void Image::Init(const char * varFilePath)
{
	m_GLProgram.Initialize();
	mTexture2D->LoadTexture(varFilePath);
}

void Image::Draw(float varX, float varY)
{
	glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0));
	glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f));
	glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));

	//һ��Ҫ��trans��Ȼ��������;�����ţ�Ȼ�����ƶ�����ô�ƶ���λ��Ҳ�������ˡ����ƶ������žͲ���Ŵ��ƶ���λ��;
	glm::mat4 model = trans*scale*rotation; 

	//View
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


	//͸��
	glm::mat4 proj = glm::perspective(glm::radians(60.0f), Game2D::mAspectRatio, 0.3f, 1000.0f);

	glm::mat4 mvp = proj*view*model;

	m_GLProgram.begin();
	{
		glm::vec3 pos[] =
		{
			//Front
			glm::vec3(-1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),

			glm::vec3(-1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(-1.0f, 1.0f, 1.0f),
		};

		glm::vec2 uv[] =
		{
			//front
			glm::vec2(0, 0),
			glm::vec2(1, 0),
			glm::vec2(1, 1),

			glm::vec2(0, 0),
			glm::vec2(1, 1),
			glm::vec2(0, 1),

		};

		glm::vec4 color[] =
		{
			glm::vec4(1, 1, 1, 0.4),
			glm::vec4(1, 1, 1, 0.4),
			glm::vec4(1, 1, 1, 0.4),

			glm::vec4(1, 1, 1, 0.4),
			glm::vec4(1, 1, 1, 0.4),
			glm::vec4(1, 1, 1, 0.4),
		};

		glUniformMatrix4fv(m_GLProgram.m_mvp, 1, false, &mvp[0][0]);

		glVertexAttribPointer(m_GLProgram.m_position, 3, GL_FLOAT, false, sizeof(glm::vec3), pos);
		glVertexAttribPointer(m_GLProgram.m_uv, 2, GL_FLOAT, false, sizeof(glm::vec2), uv);
		glVertexAttribPointer(m_GLProgram.m_color, 4, GL_FLOAT, false, sizeof(glm::vec4), color);


		glDrawArrays(GL_TRIANGLES, 0, 6);
	};
	m_GLProgram.end();
}
