#pragma once

#include "Player.h"

class Client;

class NetworkPlayer : public Player
{
public:
	NetworkPlayer(const Client* client, int id, bool isSelf);
	virtual ~NetworkPlayer();

	void Step() override;
	void Draw() override;

	int GetID() const { return m_ID; }

	void SetServerPos(const VECTOR& pos) { m_ServerTransform.SetPos(pos); }
	void SetServerRot(const VECTOR& rot) { m_ServerTransform.SetRot(rot); }
	void SetServerScale(const VECTOR& scale) { m_ServerTransform.SetScale(scale); }

	void StepOffline();
	void StepOnline();

private:
	//座標を送信
	void SendPosData();

private:
	bool m_IsSelf;                //自分自身が操作するかどうか
	int m_ID;                     //識別ID
	const Client* m_Client;       //通信用クライアントクラス
	Transform m_ServerTransform;  //サーバーから受信したトランスフォーム
};
