#pragma once

#include "Bullet.h"

class Client;

class NetworkBullet : public Bullet
{
public:
	NetworkBullet(int id, bool isSelf,VECTOR pos,VECTOR velocity);

	//Clientを受け取るバージョン
	NetworkBullet(Client* client,int id, bool isSelf);

	virtual ~NetworkBullet();

	void Step() override;

	int GetID() const { return m_ID; } //プレイヤーIDを取得

	bool IsNetworkBullet() const override { return true; }

	//サーバー座標を設定
	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }

	void SetServerTransform(const VECTOR& pos, const VECTOR& velocity) { m_ServerPosition = pos; m_ServerVelocity = velocity; }

private:
	bool m_IsSelf; //自分自身が操作するかどうか
	int m_ID;     //識別ID
	VECTOR m_ServerPosition;//サーバーから受信した座標
	VECTOR m_ServerVelocity; //サーバーから受信した速度
};
