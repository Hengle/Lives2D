#pragma once

#include "GameMessage.h"

class NetworkReceiver
{
public:
	/// <summary>
	/// ע���������
	/// </summary>
	virtual void RegisterNetworkReceiver()=0;


	/// <summary>
	/// ȡ���������
	/// </summary>
	virtual void UnRegisterNetworkReceiver()=0;


	//�յ�������Ϣ;
	virtual void OnNetworkReceive(GameMessage varGameMessage, char* varData)=0;
};
