#pragma once

#include "Client.h"
#include "../Component/Transform.h"

namespace ClientAPI
{
	void Connect();
	void Disconnect();
	void Step();
	void Draw();

	bool IsConnected();

	//サーバーへのリクエスト処理
	void RequestLogin();
	void RequestLogout(int playerID);
	void RequestTransform(int playerID, Transform transform);

	//サーバーからの受信処理
	void OnReceiveLogin();
	void OnReceiveJoin();
	void OnReceiveLogout();
	void OnReceiveAllTransform();
	void OnReceiveDead();

	void Fin();
}
