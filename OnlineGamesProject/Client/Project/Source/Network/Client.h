#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <vector>

class InputString;


class Client
{
public:
	Client();
	~Client();

public:
	void Step();
	void Draw();
	void Fin();

	void Connect();
	void SendData(const void* data, unsigned int size) const;
	bool CheckReceive();
	void ReceiveData(void* buffer, unsigned int size);
	void Disconnect();

	//通信の状態
	enum State
	{
		OFFLINE, //オフライン
		WAIT,   //接続待ち
		ONLINE  //オンライン
	};

	State GetState() const { return m_State; }
	int GetServerHandle() const { return m_ServerHandle; }

private:
	void UpdateWaiting();
	void StepOnline();

	int m_ServerHandle;
	State m_State;
};
