#include"UILabel.h"
#include"Tools\Application.h"
#include<string>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtx\transform2.hpp>
#include<glm\gtx\euler_angles.hpp>

UILabel::UILabel():mPosX(0), mPosY(0), mScaleX(1), mScaleY(1)
{

}

UILabel::~UILabel()
{
}

void UILabel::Init()
{
	mFont.buildSystemFont((Application::PersistentDataPath()+"/Resources/Font/msyh.ttf").c_str(), 30);
}

void UILabel::Draw()
{
	glm::mat4 trans = glm::translate(glm::vec3(mPosX, mPosY, 0));
	glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f));
	glm::mat4 scale = glm::scale(glm::vec3(mScaleX, mScaleY, 1.0f));

	//һ��Ҫ��trans��Ȼ��������;�����ţ�Ȼ�����ƶ�����ô�ƶ���λ��Ҳ�������ˡ����ƶ������žͲ���Ŵ��ƶ���λ��;
	glm::mat4 model = trans*scale*rotation;

	//View
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


	//���������
	glm::mat4 proj = glm::ortho(-(float)Application::DesignWidth / 2, (float)Application::DesignWidth / 2, -(float)Application::DesignHeight / 2, (float)Application::DesignHeight / 2, 0.0f, 100.0f);


	glm::mat4 mvp = proj*view*model;

	mFont.beginText(mvp);

	char buffer[1024];
	sprintf(buffer, "LOVE 123%^&*()", 1000);

	mFont.drawText(0, 0, 0, RGBA_4_BYTE(255, 255, 255), (const char *)(buffer), -1);

	mFont.endText();
}

void UILabel::SetPosition(float varPosX, float varPosY)
{
}

void UILabel::SetScale(float varScaleX, float varScaleY)
{
}
