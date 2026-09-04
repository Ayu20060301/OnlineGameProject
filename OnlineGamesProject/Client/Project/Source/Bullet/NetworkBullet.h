#pragma once

#include "BulletBase.h"

class Client;

class NetworkBullet : public BulletBase
{
public:
	NetworkBullet(int id, int ownerID);
	virtual ~NetworkBullet();

	void Step() override;

	//ネットワーク弾かどうか
	bool IsNetworkBullet() const override { return true; }

	int GetID() const { return m_ID; } //弾のIDを取得
	int GetOwnerID() const { return m_OwnerID; } //発射した弾のプレイヤーのIDを取得

	//サーバー座標を設定
	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }

	//サーバー速度を設定
	void SetServerVelocity(const VECTOR& velocity) { m_ServerVelocity = velocity; }

private:
	int m_ID; //弾のID
	int m_OwnerID; //この球を発射したプレイヤーのID

	//サーバーから発射したプレイヤーのID
	VECTOR m_ServerVelocity;
};
