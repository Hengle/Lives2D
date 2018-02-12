#include "Reflection.h"
#include"Component.h"

//std::map<std::string, FunCreateInstance> Reflection::gMapTypeInfo;//�����͹��캯��ָ�� �б�

Reflection::Reflection()
{
}


Reflection::~Reflection()
{
}

std::map<std::string, FunCreateInstance>& gMapTypeInfo()
{
	static std::map<std::string, FunCreateInstance> gMapTypeInfo= std::map<std::string, FunCreateInstance>();//�����͹��캯��ָ�� �б�
	return gMapTypeInfo;
}

Reflection::Reflection(std::string varTypeName, FunCreateInstance varFuncCreateInstance)
{
	std::map<std::string, FunCreateInstance>& tmpMapTypeInfo = gMapTypeInfo();
	tmpMapTypeInfo[varTypeName] = varFuncCreateInstance;
}

bool Reflection::ContaisType(std::string varTypeName)
{
	std::map<std::string, FunCreateInstance>& tmpMapTypeInfo = gMapTypeInfo();
	if (tmpMapTypeInfo[varTypeName] != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}

}

Component * Reflection::CreateInstance(std::string varTypeName)
{
	std::map<std::string, FunCreateInstance>& tmpMapTypeInfo = gMapTypeInfo();
	if (ContaisType(varTypeName))
	{
		Component* tmpComponent = tmpMapTypeInfo[varTypeName]();
		tmpComponent->SetComponentName(varTypeName);
		return tmpComponent;
	}
	else
	{
		return nullptr;
	}
}
