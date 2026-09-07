#include "NetworkWall.h"
#include "../Network/Client.h"
#include "../Network/ClientAPI.h"
#include "../MyMath/MyMath.h"


NetworkWall::NetworkWall() : Wall()
{
	//サーバーの座標を使用
	m_UserServerTransform = true;
}

NetworkWall::~NetworkWall()
{
}

void NetworkWall::Step()
{
	//オフラインだったらステップしない
	if (!ClientAPI::IsConnected()) return;

	Wall::Start();

	//サーバーから受信した座標を使用
	m_Transform.SetPosition(m_ServerTransform.GetPosition());
}
