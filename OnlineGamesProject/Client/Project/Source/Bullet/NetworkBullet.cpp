#include "NetworkBullet.h"

NetworkBullet::NetworkBullet(int id, int ownerID) : BulletBase()
, m_ID(id)
, m_OwnerID(ownerID)
, m_ServerVelocity(VGet(0.0f,0.0f,0.0f))
{
}

NetworkBullet::~NetworkBullet()
{
}

void NetworkBullet::Step()
{
	if (!m_IsActive) return;

	//サーバーから受け取った速度を使用
	m_Velocity = m_ServerVelocity;

	VECTOR pos = m_Transform.GetPosition();

	pos = VAdd(pos, m_Velocity);

	m_Transform.SetPosition(pos);
}
