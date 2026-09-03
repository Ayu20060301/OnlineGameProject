#pragma once

#include "BulletBase.h"

class Client;

class NetworkBullet : public BulletBase
{
public:
	NetworkBullet(int id, int ownerID);
	virtual ~NetworkBullet();

	void Step() override;

	int GetID() const { return m_OwnerID; }

	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }

	void SetServerVelocity(const VECTOR& velocity) { m_ServerVelocity = velocity; }

private:
	int m_ID;
	int m_OwnerID;

	VECTOR m_ServerVelocity;
};
