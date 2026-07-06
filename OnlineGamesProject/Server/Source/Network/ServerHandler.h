#pragma once
#include "NetworkCommonParam.h"

namespace ServerHandler
{
	//クライアントのリクエストに対するハンドラー
	void HandleLogin(int nwHandle);
	void HandleLogout(int nwHandle);

	//サーバーからクライアントへ通知する処理
	void OnJoined(int nwHandle, int joinPlayerID);
	void OnDead(int deadPlayerID);

	void SyncTransform();
}
