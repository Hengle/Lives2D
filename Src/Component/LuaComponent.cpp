#include "LuaComponent.h"
#include"LuaEngine/LuaEngine.h"
#include"Tools/Application.h"

IMPLEMENT_DYNCRT_ACTION(LuaComponent)
LuaComponent::LuaComponent():mAwakeIndex(0), mOnEnableIndex(0),mStartIndex(0),mUpdateIndex(0),mOnDisableIndex(0),mOnDestroyIndex(0)
{
}


LuaComponent::~LuaComponent()
{
}

void LuaComponent::DoFile(const char * varFilePath)
{
	mLuaFilePath = varFilePath;

	std::function<void(lua_State*)> tmpFunction = [&](lua_State* var_pLuaState)
	{
		int tmpTop = lua_gettop(var_pLuaState);

		if (lua_istable(var_pLuaState, tmpTop))
		{
			lua_pushnil(var_pLuaState);//lua_next�������ģ�һ��Ҫ��popһ����������Ϊ��ǰpop����lua���ص�table�ˣ����Ը�һ���յ�����pop

									   //top(-1)Ϊnil �ڶ���(-2)Ϊ lua���ص�table

			while (lua_next(var_pLuaState,-2))//lua_next����ȡkey��ѹ�룬��ȡvalueѹ�룬top(-1)Ϊvalue��(-2)Ϊkey,(-3)Ϊlua���ص�table
			{
				if (lua_isfunction(var_pLuaState, -1))
				{
					const char* tmpFunctionName = lua_tostring(var_pLuaState, -2);

					//printf("function %s", tmpFunctionName);

					if (strcmp(tmpFunctionName, "Start")==0)
					{
						//����Ψһ����
						lua_pushvalue(var_pLuaState, -1);
						mStartIndex = luaL_ref(var_pLuaState, LUA_REGISTRYINDEX);
					}
					else if (strcmp(tmpFunctionName, "Awake") == 0)
					{
						//����Ψһ����
						lua_pushvalue(var_pLuaState, -1);
						mAwakeIndex = luaL_ref(var_pLuaState, LUA_REGISTRYINDEX);
					}
					else if (strcmp(tmpFunctionName, "OnEnable") == 0)
					{
						//����Ψһ����
						lua_pushvalue(var_pLuaState, -1);
						mOnEnableIndex = luaL_ref(var_pLuaState, LUA_REGISTRYINDEX);
					}
					else if (strcmp(tmpFunctionName, "Update") == 0)
					{
						//����Ψһ����
						lua_pushvalue(var_pLuaState, -1);
						mUpdateIndex = luaL_ref(var_pLuaState, LUA_REGISTRYINDEX);
					}
					else if (strcmp(tmpFunctionName, "OnDisable") == 0)
					{
						//����Ψһ����
						lua_pushvalue(var_pLuaState, -1);
						mOnDisableIndex = luaL_ref(var_pLuaState, LUA_REGISTRYINDEX);
					}
					else if (strcmp(tmpFunctionName, "OnDestroy") == 0)
					{
						//����Ψһ����
						lua_pushvalue(var_pLuaState, -1);
						mOnDestroyIndex = luaL_ref(var_pLuaState, LUA_REGISTRYINDEX);
					}
				}

				//Ҫά��ѭ����lua���ص�table������д����-2����ôҪpop��һ��
				lua_pop(var_pLuaState, 1);//��ʱ top(-1)Ϊkey, (-2)Ϊlua���ص�table
			}

			//ѭ��������״̬  top(-1)Ϊkey, (-2)Ϊlua���ص�table
			//Ҫ�ָ���ԭ�� lua���ص�table��top����ôҪpop��һ��
			lua_pop(var_pLuaState, 1);
		}

	};
	LuaEngine::GetSingleton()->DoFile((Application::PersistentDataPath() + "/Resource/Script/"+ varFilePath).c_str(), tmpFunction);
}

void LuaComponent::Awake()
{
	LuaEngine::GetSingleton()->ExecuteLuaFunction(mAwakeIndex);
}

void LuaComponent::OnEnable()
{
	LuaEngine::GetSingleton()->ExecuteLuaFunction(mOnEnableIndex);
}

void LuaComponent::Start()
{
	LuaEngine::GetSingleton()->ExecuteLuaFunction(mStartIndex);
}

void LuaComponent::Update()
{
	LuaEngine::GetSingleton()->ExecuteLuaFunction(mUpdateIndex);
}

void LuaComponent::OnDisable()
{
	LuaEngine::GetSingleton()->ExecuteLuaFunction(mOnDisableIndex);
}

void LuaComponent::OnDestroy()
{
	LuaEngine::GetSingleton()->ExecuteLuaFunction(mOnDestroyIndex);
}
