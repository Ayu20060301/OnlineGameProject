#include "Wall.h"
#include "../GameSetting/GameSetting.h"
#include "../Component/Collision/AABB.h"
#include "WallManager.h"
#include "../Network/NetworkCommonParam.h"
#include "../Network/ServerHandler.h"

using namespace Network;

//壁サイズ
constexpr int WALL_WIDTH = 40;
constexpr int WALL_HEIGHT = 200;

Wall::Wall() : GameObject()
{
	m_Type = GameObjectType::WALL;
}

void Wall::Init()
{
	m_MoveSpeed = 12.0f;

	//下方向から開始
	m_MoveDirection = 1;

	//画面中央
	VECTOR pos = VGet(SCREEN_WIDTH / 2.0f - WALL_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - WALL_HEIGHT / 2.0f, 0.0f);

	m_Transform.SetPosition(pos);

	//当たり判定を設定
	AABB2D* aabb = AddComponent<AABB2D>();
	aabb->SetCenter(VGet(WALL_WIDTH / 2.0f, WALL_HEIGHT / 2.0f, 0.0f));
	aabb->SetSize(VGet(WALL_WIDTH, WALL_HEIGHT, 0.0f));
}

void Wall::Step()
{
	VECTOR pos = m_Transform.GetPosition();

	// 上下に移動
	pos.y += m_MoveSpeed * m_MoveDirection;

	// 上端
	if (pos.y <= 0.0f)
	{
		pos.y = 0.0f;
		m_MoveDirection = 1;
	}

	// 下端
	if (pos.y >= SCREEN_HEIGHT - WALL_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - WALL_HEIGHT;
		m_MoveDirection = -1;
	}

	m_Transform.SetPosition(pos);
}

void Wall::Draw()
{
	VECTOR pos = GetPosition();

	DrawBox(
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		static_cast<int>(pos.x + WALL_WIDTH),
		static_cast<int>(pos.y + WALL_HEIGHT),
		GetColor(255, 255, 255),
		true
	);

	//壁の現在位置を描画
	DrawFormatString(1000, 20, GetColor(255, 255, 255), "POS:[%.2f, %.2f, %.2f]", pos.x, pos.y, pos.z);
}

//-------------------------
//弾が壁に当たった場合の処理
//後で実装する
//-------------------------
void Wall::OverlapGameObject(GameObject& other)
{
}
