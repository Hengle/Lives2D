#pragma once
#include "Object.h"
#include"Component.h"
#include<vector>

class Transform;
class GameObject :
	public Object
{

private:
	GameObject();
public:
	GameObject(const char* varName);
	~GameObject();

	static void Destroy(GameObject* varGo);

public:
	std::string name;

	Transform* mTransform;

	//**************************************************���ӽṹ���

public:

	///���������
	void AddChild(GameObject* varGameObject);

	///��ȡ���������
	int GetChildCount();

	///��ȡ������
	GameObject* GetChild(int varIndex);

	///���ø��ڵ�
	void SetParent(GameObject* varGameObjectParent);

private:
	std::vector<GameObject*> mVectorChild;//�������б�

	GameObject* mGameObjectParent;//���ڵ�



	//**************************************************���
public:
	Component* AddComponent(const char* varComponentName);

	void RemoveComponent(const char* varComponentName);

private:
	std::vector<Component*> mVectorComponent;

	//**************************************************��������
public:
	void Awake() ;
	void OnEnable() ;
	void Start() ;

	void Update() ;

	void OnDisable() ;
	void OnDestroy() ;


	
};

