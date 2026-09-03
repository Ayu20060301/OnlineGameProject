#include "Bullet.h"
#include "../Component/Collision/AABB.h"
#include "BulletManager.h"
#include "../Network/NetworkCommonParam.h"
#include "../Network/ServerHandler.h"

using namespace Network;

//バレットサイズ
constexpr int BULLET_WIDTH = 8;
constexpr int BULLET_HEIGHT = 8;

Bullet::Bullet() : GameObject()
, m_ID(-1)
, m_NWHandle(-1)
, m_IPAddress{}
{
	m_Type = GameObjectType::BULLET;
}

void Bullet::Init(int nwHandle)
{
}

void Bullet::Draw()
{
}

void Bullet::OverlapGameObject(GameObject& other)
{
}
