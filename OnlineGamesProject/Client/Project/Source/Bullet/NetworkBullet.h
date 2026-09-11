#pragma once

#include "Bullet.h"

class Client;

class NetworkBullet : public Bullet
{
public:
	NetworkBullet(VECTOR pos,VECTOR velocity);

	virtual ~NetworkBullet();

	void Step() override;

	bool IsNetworkBullet() const override { return true; }

	//サーバー座標を設定
	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }

	void SetServerTransform(const VECTOR& pos, const VECTOR& velocity) { m_ServerPosition = pos; m_ServerVelocity = velocity; }

private:
	VECTOR m_ServerPosition;//サーバーから受信した座標
	VECTOR m_ServerVelocity; //サーバーから受信した速度
};
