#include "Bullet.h"
#include "../Player/Player.h"
#include "../GameSetting/GameSetting.h"


Bullet::Bullet() : GameObject()
, m_IsActive(true)
, m_Velocity{}
, m_FireTimer(0)
, m_PlayerNumber(0)
, m_Splite(nullptr)
{

}

Bullet::~Bullet() = default;

void Bullet::Init()
{

}

void Bullet::Load()
{
}

void Bullet::Start()
{
}

void Bullet::Step()
{
	if (!m_IsActive) return;

	//現在位置
	VECTOR pos = m_Transform.GetPosition();

	//速度分移動
	pos = VAdd(pos, m_Velocity);

	//位置を更新
	m_Transform.SetPosition(pos);


	//画面外に出たら消す
	if (pos.x < -BULLET_WIDTH ||
		pos.x > SCREEN_WIDTH + BULLET_WIDTH ||
		pos.y < -BULLET_HEIGHT ||
		pos.y > SCREEN_HEIGHT + BULLET_HEIGHT)
	{
		m_IsActive = false;
	}
}

void Bullet::Update()
{
}

void Bullet::Draw()
{
	if (!m_IsActive) return;

	VECTOR pos = m_Transform.GetPosition();

	DrawBox(
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		static_cast<int>(pos.x) + BULLET_WIDTH,
		static_cast<int>(pos.y) + BULLET_HEIGHT,
		GetColor(255, 255, 255),
		true
	);
}

void Bullet::Fin()
{
}
