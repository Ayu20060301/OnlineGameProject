#pragma once
#include <list>
#include <string>
#include "NetworkCommonParam.h"

struct ClientData
{
	int handle;
	IPDATA ip;
	int playerID;
	char name[NETWORK_USER_NAME_BUFFER_MAX];
};

class Server
{
public:
	Server();
	~Server();

public:
	void Init();
	void Update();
	void Draw();
	void Fin();

private:
	void AddUserData(int handle);		// ユーザーデータを追加
	void RemoveUserData(int handle);	// ユーザーデータを除外
	void ReceiveData();					// データ受信
	void SendChatData();               //チャットデータを送信
	void SendShiritoriData();          //しりとりデータ送信
	void StartShiritori();             //しりとりを開始する
	void SendStartShiritoriData();             

	bool IsUseWord(const char* word);

private:
	std::list<ClientData> m_ClientData;

	//チャット履歴
	std::list<ChatData> m_ChatData;

	//しりとり履歴
	std::list<ShiritoriData> m_WordList;

	int m_TurnPlayerID;

	//しりとりの最初の文字
	char m_StartChar[NETWORK_WORD_BUFFER_MAX];

	//ゲーム開始すみか
	bool m_IsGameStarted;
};
