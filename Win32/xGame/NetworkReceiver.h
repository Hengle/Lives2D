#pragma once

#include "GameMessage.h"

class NetworkReceiver
{
public:
	/// <summary>
	/// ע���������
	/// </summary>
	void RegisterNetworkReceiver();


	/// <summary>
	/// ȡ���������
	/// </summary>
	void UnRegisterNetworkReceiver();


	//�յ�������Ϣ;
	void OnNetworkReceive(GameMessage varGameMessage, char* varData);
};
