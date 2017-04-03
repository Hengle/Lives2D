#pragma once
#include<iostream>
#include<map>
#include"CCSceneBase.h"
#include"Helper.h"

#define REGISTER_SCENE(SCENETYPE,SCENECLASS) \
	SCENECLASS* p ## SCENECLASS = new SCENECLASS(); \
	RegisterScene(SCENETYPE,p ## SCENECLASS); \

enum SCENE_TYPE
{
	SCENE_WELCOME,
	SCENE_MAIN,
	SCENE_COUNT
};

class CCSceneManager
{
public:
	static CCSceneManager* SharedInstance();


	//Update �����߼�����
	void Update();

	//Draw����������
	void Draw();

	//ע��Scene
	void RegisterScene(SCENE_TYPE type,CCSceneBase* scene);

	//ע�����е�Scene
	void RegisterAllScene();

private:
	CCSceneManager();
	~CCSceneManager();

private:
	static CCSceneManager* m_Instance;

	typedef std::map<SCENE_TYPE,CCSceneBase*> SCENE_MAP;
	SCENE_MAP m_SceneMap;
};

