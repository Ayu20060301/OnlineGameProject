#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <list>

class InputString;


enum NetworkState
{
	NW_STATE_NANE_INPUT,			// 名前入力
	NW_STATE_WAITING_CONNECTION,	// 接続待ち
	NW_STATE_MESSAGE_INPUT,			// メッセージ入力
	NW_STATE_SHIRITORI
};

class Client
{
public:
	Client();
	virtual ~Client();

public:
	void Init();
	void Update();
	void Draw();
	void Fin();

	void Connect();
	void Disconnect();

	void StartNameInput();
	void UpdateNameChange();

	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

	const char* GetUserName() const { return m_SendChatData.name; }

private:
	void UpdateNameInput();
	void UpdateWaitingConnection();
	void UpdateMessageInput();
	void ReceiveData();
	void DrawChat();
private:
	void UpdateShiritori();
	void ReceiveShiritoriData();
	void DrawShiritori();

protected:
	int m_ServerHandle;
	ChatData m_SendChatData;
	ShiritoriData m_SendShiritoriData;
	std::list<ShiritoriData> m_WordList;
	InputString* m_UserNameInput;
	InputString* m_MessageInput;
	NetworkState m_NWState;
	IPDATA m_IPAddress;
	std::list<ChatData> m_ServerChatData;
};
