#include "DxLib.h"
#include "../GameSetting/GameSetting.h"
#include "StraightBullet.h"

constexpr int BULLET_SIZE = 16;

StraightBullet::StraightBullet(VECTOR pos, VECTOR velocity) : BulletBase()
{
	m_Transform.SetPosition(pos);
	m_Velocity = velocity;
}

StraightBullet::~StraightBullet()
{
	BulletBase::Init();
}

void StraightBullet::Init()
{
}

void StraightBullet::Load()
{
	m_Handle = LoadGraph("Data/Play/Bullet/Bullet1.png");
}

void StraightBullet::Start()
{
	m_IsActive = true;
}

void StraightBullet::Step()
{
	if (!m_IsActive) return;

	//現在位置
	VECTOR pos = m_Transform.GetPosition();

	//速度分移動
	pos = VAdd(pos, m_Velocity);

	//位置を更新
	m_Transform.SetPosition(pos);

	//画面外に出たら消す
	if (pos.x < -BULLET_SIZE ||
		pos.x > SCREEN_WIDTH + BULLET_SIZE ||
		pos.y < -BULLET_SIZE ||
		pos.y > SCREEN_HEIGHT + BULLET_SIZE)
	{
			m_IsActive = false;
	}

}

void StraightBullet::Update()
{
	if (!m_IsActive) return;
}

void StraightBullet::Draw()
{
	if (!m_IsActive) return;

	VECTOR pos = GetRenderTransform().GetPosition();

	DrawGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), m_Handle, true);
}

void StraightBullet::Fin()
{
	if (m_Handle != -1)
	{
		DeleteGraph(m_Handle);
		m_Handle = -1;
	}
}
