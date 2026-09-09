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
	m_NWHandle = nwHandle;

	//IPアドレス設定
	GetNetWorkIP(m_NWHandle, &m_IPAddress);

	//当たり判定を設定
	AABB2D* aabb = AddComponent<AABB2D>();
	aabb->SetCenter(VGet(0.0f, 0.0f, 0.0f));
	aabb->SetSize(VGet(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));



}

void Bullet::Draw()
{
}

void Bullet::OverlapGameObject(GameObject& other)
{
}
