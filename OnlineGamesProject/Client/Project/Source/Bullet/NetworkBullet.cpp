#include "NetworkBullet.h"
#include "../Network/Client.h"
#include "../Network/ClientAPI.h"

NetworkBullet::NetworkBullet(int id, int ownerID) : BulletBase()
, m_ID(id)
, m_OwnerID(ownerID)
{
}

NetworkBullet::~NetworkBullet() = default;

void NetworkBullet::Step()
{
	if (!m_IsActive) return;

	//オフラインだったらステップしない
	if (!ClientAPI::IsConnected()) return;

    //StraightBullet::Step();

	//サーバーから受け取った速度を使用
	m_Velocity = m_ServerVelocity;

	VECTOR pos = m_Transform.GetPosition();

	pos = VAdd(pos, m_Velocity);

	m_Transform.SetPosition(pos);
}
