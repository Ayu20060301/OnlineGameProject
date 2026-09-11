#include "NetworkBullet.h"
#include "../Network/Client.h"
#include "../Network/ClientAPI.h"
#include "../MyMath/MyMath.h"

NetworkBullet::NetworkBullet(VECTOR pos,VECTOR velocity) : Bullet()
,m_ServerPosition(pos)
,m_ServerVelocity(velocity)
{
	//サーバー座標を使用する
	m_UserServerTransform = true;

	SetPosition(pos);
	SetVelocity(velocity);
}

NetworkBullet::~NetworkBullet() = default;

void NetworkBullet::Step()
{
	//自分自身しかステップしない

	//オフラインだったらステップしない
	if (!ClientAPI::IsConnected) return;

    m_Transform.SetPosition(m_ServerPosition);
}
