#include "Bullet.h"
#include "../GameSetting/GameSetting.h"
#include "../Component/Collision/AABB.h"
#include "BulletManager.h"
#include "../Network/NetworkCommonParam.h"
#include "../Network/ServerHandler.h"

using namespace Network;

//バレットサイズ
constexpr int BULLET_WIDTH = 8;
constexpr int BULLET_HEIGHT = 8;

Bullet::Bullet() : GameObject()
, m_Velocity({})
{
	m_Type = GameObjectType::BULLET;
}

void Bullet::Init()
{

	//当たり判定を設定
	AABB2D* aabb = AddComponent<AABB2D>();
	aabb->SetCenter(VGet(0.0f, 0.0f, 0.0f));
	aabb->SetSize(VGet(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));

	// 中央から発射
	SetPosition(VGet(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	// 例：右方向
	SetVelocity(VGet(10.0f, 0.0f, 0.0f));
}

void Bullet::Update()
{
	if (!m_IsActive) return;

	// 速度分移動
	VECTOR pos = m_Transform.GetPosition();

	pos = VAdd(pos, m_Velocity);

	m_Transform.SetPosition(pos);

	// 画面外に出たら無効化
	if (pos.x < -BULLET_WIDTH ||
		pos.x > SCREEN_WIDTH + BULLET_WIDTH ||
		pos.y < -BULLET_HEIGHT ||
		pos.y > SCREEN_HEIGHT + BULLET_HEIGHT)
	{
		m_IsActive = false;
	}
}

void Bullet::Draw()
{
#ifdef _DEBUG
	VECTOR pos = GetPosition();

	DrawBox(
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		static_cast<int>(pos.x) + BULLET_WIDTH,
		static_cast<int>(pos.y) + BULLET_HEIGHT,
		GetColor(255, 255, 255),
		TRUE
	);
#endif
}

void Bullet::OverlapGameObject(GameObject& other)
{
	//プレイヤーに当たった
	if (other.GetType() == GameObjectType::PLAYER)
	{
		//弾を消す
		m_IsActive = false;
	}
}
