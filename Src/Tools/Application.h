#pragma once

#ifdef _WIN32
#include <Windows.h>    
#else

#endif
#include <iostream>
#include <string> 


class Application
{
private:
	static std::string mDataPath;//�ڰ�׿ϵͳ ָ���� AssetsĿ¼
	static std::string mPersistentDataPath;//�־��Դ洢Ŀ¼���ڰ�׿ϵͳ ָ����sdcard/Android/com.xxx.xxx/files

public:
	static int ScreenWidth;//��Ļ�ֱ���
	static int ScreenHeight;
	static int DesignWidth;//��Ʒֱ���
	static int DesignHeight;
	static int RenderWidth;//ʵ����Ⱦ�ֱ���
	static int RenderHeight;
    
    static bool isRunning;

public:
	static void SetDataPath(const char* varDataPath)
	{
		mDataPath = varDataPath;
	}
	
	static std::string DataPath()
	{
#ifdef ANDROID
		return mDataPath;
#endif

#ifdef _WIN32
		std::string tmpDataPath;
#ifdef _MSC_VER
		tmpDataPath = GetProgramDir() + "/../../../";
#else
		tmpDataPath = GetProgramDir() + "/../../../";
#endif
		while (std::string::npos != tmpDataPath.find("\\"))
		{
			tmpDataPath = tmpDataPath.replace(tmpDataPath.find("\\"), 1, "/");
		}
		return tmpDataPath;
#endif // _WIN32
        
#ifdef IOS
        return mDataPath;
#endif
	}


	static void SetPersistentDataPath(const char* varpersistentDataPath)
	{
		mPersistentDataPath = varpersistentDataPath;
	}

	static std::string PersistentDataPath()
	{
#ifdef ANDROID
		return mPersistentDataPath;
#endif

#ifdef _WIN32
		std::string tmpDataPath;
#ifdef _MSC_VER
		tmpDataPath = GetProgramDir() + "/../../../";
#else
		tmpDataPath = GetProgramDir() + "/../../../";
#endif
		while (std::string::npos != tmpDataPath.find("\\"))
		{
			tmpDataPath = tmpDataPath.replace(tmpDataPath.find("\\"), 1, "/");
		}
		return tmpDataPath;
#endif // _WIN32
        
#ifdef IOS
        
      return mPersistentDataPath;
#endif
	}

private:
#ifdef _WIN32
	static std::string GetProgramDir()
	{
		char exeFullPath[MAX_PATH]; // Full path   
		std::string strPath = "";

		GetModuleFileName(NULL, exeFullPath, MAX_PATH);
		strPath = (std::string)exeFullPath;    // Get full path of the file   

		int pos = strPath.find_last_of('\\', strPath.length());
		return strPath.substr(0, pos);  // Return the directory without the file name   
	}
#endif
};
