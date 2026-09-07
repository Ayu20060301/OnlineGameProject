#include "NetworkBullet.h"
#include "../Network/Client.h"
#include "../Network/ClientAPI.h"
#include "../MyMath/MyMath.h"

NetworkBullet::NetworkBullet(int id, bool isSelf) : Bullet()
,m_IsSelf(isSelf)
,m_ID(id)
,m_ServerPosition(VGet(0.0f,0.0f,0.0f))
,m_ServerVelocity(VGet(0.0f,0.0f,0.0f))
{
	//サーバー座標を使用する
	m_UserServerTransform = !isSelf;
}

NetworkBullet::NetworkBullet(Client* client, int id, bool isSelf) : Bullet()
,m_IsSelf(isSelf)
,m_ID(id)
{
	//サーバー座標を使用する
	m_UserServerTransform = !isSelf;
}

NetworkBullet::~NetworkBullet() = default;

void NetworkBullet::Step()
{
	//自分自身しかステップしない

	//オフラインだったらステップしない
	if (!ClientAPI::IsConnected) return;


	if (m_IsSelf)
	{
		Bullet::Step();
	}
	else
	{
		m_Transform.SetPosition(m_ServerPosition);
	}
}
