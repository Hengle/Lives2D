#include "Helper.h"

Helper::Helper(void)
{
}

//���GL����
void Helper::CheckGLError(const char* op)
{
	for(GLint error=glGetError();error;error=glGetError())
	{
		LOGE("after %s() glError (0x%x) \n",op,error);
	}
}

///���GL������ֵ
void Helper::PrintGLString(const char* name,GLenum s)
{
	const char *v=(const char *)glGetString(s);
	LOGI("GL %s = %s\n",name,v); //LOGI��ʽ���ַ���Ȼ���LOG
}


//���LOG
void Helper::CCLOG(const char* str)
{
	LOGI("\n%s \n",str);
}

Helper::~Helper(void)
{
}
