#pragma once

#include <list>
#include <string>
#include "NetworkCommonParam.h"

/// <summary>
/// クライアントデータ
/// </summary>
struct ClientData
{
	int handle;
	IPDATA ip;
};

/// <summary>
/// サーバークラス
/// </summary>
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
	void ReceiveData();	// ユーザーデータを除外
	void SyncTransform(int handle);  //同期用に座標設定
	void CheckCollision();
};
