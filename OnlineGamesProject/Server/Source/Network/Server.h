#pragma once

#include <list>
#include <string>
#include "NetworkCommonParam.h"

struct ClientData
{
	int handle;
	IPDATA ip;
};

struct NetworkPlayerData
{
	ClientData client;
	int id;
	VECTOR pos;
	VECTOR rot;
	VECTOR scale;
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
	void SendLoginData(const NetworkPlayerData& loginPlayer);
	void SendJoinData(const NetworkPlayerData& joinPlayer);
	void SendLogoutData(int id);
	void SendAllTransformData();
	bool ReceiveData();  //データ受信
	void SyncPos(int handle);  //同期用に座標設定

private:
	std::list<NetworkPlayerData> m_NetworkPlayerData;
};
