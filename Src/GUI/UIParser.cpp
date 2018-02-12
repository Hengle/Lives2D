#include "UIParser.h"
#include"PlayerPrefs/TinyXml/tinyxml.h"
#include"Component/GameObject.h"
#include<fstream>
#include"Tools/Helper.h"

UIParser::UIParser()
{
}


UIParser::~UIParser()
{
}

void UIParser::CreateUI(const char * varFilePath)
{
	//�ļ������ڣ��ȴ���
	std::ifstream tmpXmlFile(varFilePath);
	if (!tmpXmlFile)
	{
		Helper::LOG("UIParser::CreateUI %s not exist",varFilePath);
		return;
	}

	//����һ��XML�ĵ�����;
	TiXmlDocument* tmpTiXmlDocument = new TiXmlDocument(varFilePath);
	tmpTiXmlDocument->LoadFile(TIXML_ENCODING_UTF8);

	//��ø�Ԫ�� PlayerPrefs;
	TiXmlElement *tmpTiXmlElementRoot = tmpTiXmlDocument->RootElement();
	if (tmpTiXmlElementRoot == NULL)
	{
		Helper::LOG("UIParser::CreateUI RootElement NULL");
		return;
	}

	//�������ڵ�
	GameObject* tmpGameObjectRoot = new GameObject(tmpTiXmlElementRoot->Value());

	RecursiveNode(tmpTiXmlElementRoot, tmpGameObjectRoot);

	
}

void UIParser::RecursiveNode(TiXmlElement * varTiXmlElementRoot, GameObject * varGameObjectRoot)
{
	//���� KeyValuePair;
	TiXmlNode *tmpTiXmlNode = NULL;

	for (tmpTiXmlNode = varTiXmlElementRoot->FirstChildElement(); tmpTiXmlNode != NULL; tmpTiXmlNode = tmpTiXmlNode->NextSiblingElement())
	{
		TiXmlElement
	}
}
