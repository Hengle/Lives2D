#pragma once
class CCVector3
{
public:
	CCVector3(void);
	~CCVector3(void);

	CCVector3(float x,float y,float z);

	//��ȡ����
	float* GetData();

public:
	float m_Data[3];
};

