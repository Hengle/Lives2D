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
void Helper::LOG(const char* str)
{
	LOGI("\n%s \n",str);
}

std::string Helper::ReadTxt(std::string& varFilePath)
{
	ifstream infile;
	infile.open(varFilePath.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

	std::string tmpAllContent;
	string s;
	while (getline(infile, s))
	{
		tmpAllContent.append(s);
	}
	infile.close();             //�ر��ļ������� 
	return tmpAllContent;
}

std::vector<std::string> Helper::ReadLine(std::string& varFilePath)
{
	ifstream infile;
	infile.open(varFilePath.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

	std::vector<std::string> tmpResult;
	string s;
	while (getline(infile, s))
	{
		tmpResult.push_back(s);
	}
	infile.close();             //�ر��ļ������� 
	return tmpResult;
}

std::vector<std::string> Helper::Split(std::string& varStr, std::string& varPattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	varStr += varPattern;//��չ�ַ����Է������  
	size_t size = varStr.size();

	for (int i = 0; i<size; i++)
	{
		pos = varStr.find(varPattern, i);
		if (pos<size)
		{
			std::string s = varStr.substr(i, pos - i);
			result.push_back(s);
			i = pos + varPattern.size() - 1;
		}
	}
	return result;
}




unsigned int Helper::GetTime()
{
	unsigned int tmpTime;
#ifdef WIN32
	tmpTime = GetTickCount();//��ȷ������
#endif
	return tmpTime;
}

std::string Helper::GetDirPath(std::string varFilePath)
{
	int tmpLastPatternIndex = varFilePath.find_last_of('/');
	std::string tmpDirPath = varFilePath.substr(0, tmpLastPatternIndex + 1);
	return tmpDirPath;
}

Helper::~Helper(void)
{
}
