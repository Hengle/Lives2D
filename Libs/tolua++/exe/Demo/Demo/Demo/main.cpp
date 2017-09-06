#include <stdio.h>    
#include<windows.h>    

extern "C"
{
#include "lua.h"    
#include "lualib.h"    
#include "lauxlib.h"    
#include "luaconf.h"    
}
#include "tolua++.h"  
#include"Student.h"  

extern int tolua_Student_open(lua_State* tolua_S);

void PrintLuaError(lua_State* L, int sErr)
{
	if (sErr == 0)
	{
		return;
	}
	const char* error;
	char sErrorType[256] = { 0 };
	switch (sErr)
	{
	case LUA_ERRSYNTAX://����ʱ���� 
					   /*const char *buf = "mylib.myfun()2222";���������������������ʱ����*/
		sprintf_s(sErrorType, sizeof(sErrorType), "%s", "syntax error during pre-compilation");
		break;
	case LUA_ERRMEM://�ڴ���� 
		sprintf_s(sErrorType, sizeof(sErrorType), "%s", "memory allocation error");
		break;
	case LUA_ERRRUN://����ʱ���� 
					/*const char *buf = "my222lib.myfun()";����������������������ʱ����my222libʵ���ϲ����������Ŀ⣬���ص�ֵ��nil*/
		sprintf_s(sErrorType, sizeof(sErrorType), "%s", "a runtime error");
		break;
	case LUA_YIELD://�̱߳�������� 
		sprintf_s(sErrorType, sizeof(sErrorType), "%s", "Thread has Suspended");
		break;
	case LUA_ERRERR://�ڽ��д�����ʱ�������� 
		sprintf_s(sErrorType, sizeof(sErrorType), "%s", "error while running the error handler function");
		break;
	default:
		break;
	}
	error = lua_tostring(L, -1);//��ӡ������ 
	printf("%s:%s", sErrorType, error);
	lua_pop(L, 1);
}

int main(int argc, char* argv[])
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	tolua_Student_open(L);

	int ret= luaL_dofile(L, "./test.lua");

	PrintLuaError(L, ret);

	lua_close(L);

	system("pause");
	return 0;
}