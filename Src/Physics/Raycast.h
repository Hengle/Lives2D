#pragma once
#include"Math/Math.h"
#include"3D/Camera.h"
#include"RaycastHit.h"

class GameObject;
class Raycast
{
public:
	Raycast();
	~Raycast();

	//����Ļ���귢������
	static bool ScreenPointToRay(Vector3& varScreenTouchPosition, Camera* varCamera,RaycastHit* varRaycastHit);

};

