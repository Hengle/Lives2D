#pragma once
#include<string>
#include<map>

class Component;
typedef Component* (*FunCreateInstance)();//���캯��ָ��


#define DECLEAR_DYNCRT_ACTION(TypeName) \
public: \
	static TypeName* CreateInstance() \
	{ \
		return new TypeName(); \
	} \
	static Reflection* mReflection;

#define IMPLEMENT_DYNCRT_ACTION(TypeName) \
	Reflection* TypeName::mReflection=new Reflection(#TypeName,(FunCreateInstance)TypeName::CreateInstance);



class Reflection
{
public:
	Reflection();
	~Reflection();

	Reflection(std::string varTypeName, FunCreateInstance varFuncCreateInstance);

	static bool ContaisType(std::string varTypeName);

	static Component* CreateInstance(std::string varTypeName);

private:
	//static std::map<std::string, FunCreateInstance> gMapTypeInfo;//�����͹��캯��ָ�� �б�

	std::string mReflectionClassName;

	FunCreateInstance mReflectionClassConstrator;
};

