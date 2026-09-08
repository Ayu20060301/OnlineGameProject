#include "Bullet.h"
#include "../Player/Player.h"
#include "../GameSetting/GameSetting.h"


//バレットごとの画像
const char* BULLET_GRAPHIC_PATH[] =
{
	"Data/Play/Bullet/Bullet1.png", //1Pのバレット
	"Data/Play/Bullet/Bullet2.png", //2Pのバレット
};

Bullet::Bullet() : GameObject()
, m_IsActive(true)
, m_MoveSpeed(0.0f)
, m_Velocity{}
, m_Handle(-1)
, m_FireTimer(0)
, m_PlayerNumber(0)
{

}

Bullet::~Bullet() = default;

void Bullet::Init()
{
	//バレット速度
	m_MoveSpeed = 16.0f;
}

void Bullet::Load()
{
	m_Handle = LoadGraph(BULLET_GRAPHIC_PATH[m_PlayerNumber]);
}

void Bullet::Start()
{
}

void Bullet::Step()
{
	if (!m_IsActive) return;

	//発射タイマー
	if (m_FireTimer > 0)
	{
		--m_FireTimer;
	}

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

	VECTOR pos = GetRenderTransform().GetPosition();

	DrawGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), m_Handle, true);
}

void Bullet::Fin()
{
	if (m_Handle != -1)
	{
		DeleteGraph(m_Handle);
		m_Handle = -1;
	}
}

/// <summary>
/// 弾を発射させる処理
/// </summary>
void Bullet::FireBullet(VECTOR playerPos)
{
	if (!m_IsActive) return;

	//インターバル中は発射しない
	if (m_FireTimer > 0) return;

	//プレイヤーの中心に弾の中心を合わせる
	VECTOR pos;

	pos.x = playerPos.x + PLAYER_WIDTH / 2.0f - BULLET_WIDTH / 2.0f;
	pos.y = playerPos.y + PLAYER_HEIGHT / 2.0f - BULLET_HEIGHT / 2.0f;
	pos.z = playerPos.z;

	//発射位置を設定
	m_Transform.SetPosition(pos);

	//プレイヤーによって弾の方向を変更
	if (m_PlayerNumber == 0)
	{
		//1P→右
		m_Velocity = VGet(m_MoveSpeed, 0.0f, 0.0f);
	}
	else
	{
		//2P→左
		m_Velocity = VGet(-m_MoveSpeed, 0.0f, 0.0f);
	}

	//タイマーをリセット
	m_FireTimer = FIRE_INTERVAL;
}
