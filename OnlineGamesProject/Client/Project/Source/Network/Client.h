#pragma once

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
	bool IsConnected() const { return m_State == ONLINE; }

	//通信の状態
	enum State
	{
		OFFLINE, //オフライン
		WAIT,   //接続待ち
		ONLINE  //オンライン
	};

	State GetState() const { return m_State; }
	
private:
	void UpdateWaiting();
	void StepOnline();

	int m_ServerHandle;
	State m_State;
};
