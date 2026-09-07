#include "DxLib.h"
#include "../GameSetting/GameSetting.h"
#include "Wall.h"

constexpr float WALL_WIDTH = 40.0f;
constexpr float WALL_HEIGHT = 200.0f;

Wall::Wall() : GameObject()
, m_MoveSpeed(0.0f)
, m_Direction(0)
{
}

Wall::~Wall() = default;

void Wall::Init()
{
}

void Wall::Load()
{
}

void Wall::Start()
{

	m_MoveSpeed = 12.0f;

	m_Direction = 1;

	//画面中央に配置
	VECTOR pos = VGet(SCREEN_WIDTH / 2.0f - WALL_WIDTH / 2.0f,
		SCREEN_HEIGHT / 2.0f - WALL_HEIGHT / 2.0f,
		0.0f
	);

	m_Transform.SetPosition(pos);

	
}

void Wall::Step()
{
	VECTOR pos = m_Transform.GetPosition();

	//上下に移動
	pos.y += m_MoveSpeed * m_Direction;

	//上端
	if (pos.y <= 0.0f)
	{
		pos.y = 0.0f;
		m_Direction = 1;
	}

	//下端
	if (pos.y >= SCREEN_HEIGHT - WALL_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - WALL_HEIGHT;
		m_Direction = -1;
	}

	m_Transform.SetPosition(pos);
}

void Wall::Update()
{
}

void Wall::Draw()
{
	VECTOR pos = m_Transform.GetPosition();

	DrawBox(static_cast<int>(pos.x),
		    static_cast<int>(pos.y),
			static_cast<int>(pos.x + WALL_WIDTH),
		    static_cast<int>(pos.y + WALL_HEIGHT),
			GetColor(255, 255, 255),
			true
			);
}

void Wall::Fin()
{
}
