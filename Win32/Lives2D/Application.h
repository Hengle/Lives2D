#pragma once

class Application
{
public:
	static char* DataPath;//�ڲ��洢

	static char* persistentDataPath;//�ⲿ�洢

public:
	Application()
	{
		DataPath = "../../Resources/";
		persistentDataPath = "./";
	}
};

char* Application::DataPath = "";
char* Application::persistentDataPath = "";