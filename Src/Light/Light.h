#pragma once

#include<glm\glm.hpp>


class Light
{
public:
	Light();
	~Light();

	///������ɫ
	void SetColor(int r,int g,int b,int a);


	///����λ��
	void SetPosition(float x, float y, float z);


private:
	int r;
	int g;
	int b;
	int a;

	float x;
	float y;
	float z;
};

