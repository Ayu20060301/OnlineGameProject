#include "Player.h"
#include "../Component/Splite.h"
#include "../Component/Controller2D.h"
#include "../MyMath/MyMath.h"

constexpr int PLAYER_CHANGE_ANIM_TIME = 5;
constexpr int PLAYER_CHANGE_GRAPH_NUM = 4;

Player::Player() : GameObject()
, m_IsActive(true)
, m_MoveSpeed(0.0f)
, m_ScaleSpeed(0.0f)
, m_RotSpeed(0.0f)
, m_Splite(nullptr)
, m_Controller(nullptr)
{
}

Player::~Player() = default;

void Player::Init()
{
	m_MoveSpeed = 10.0f;
	m_ScaleSpeed = 0.01f;
	m_RotSpeed = 0.01f;
	m_Splite = AddComponent<Splite>();
	m_Controller = AddComponent<Controller2D>();
}

void Player::Load()
{
	m_Splite->Load("Data/Play/Player/Player1.png");
}

void Player::Start()
{
	SetPosition(VGet(100.0f, 100.0f, 0.0f));
}

void Player::Step()
{
	if (!m_IsActive) return;

	VECTOR pos = m_Transform.GetPosition();
	VECTOR scale = m_Transform.GetScale();
	VECTOR rot = m_Transform.GetRotation();

	// 移動入力
	pos += m_Controller->Move() * m_MoveSpeed;


	m_Transform.SetPosition(pos);
	m_Transform.SetScale(scale);
	m_Transform.SetRotation(rot);
}

void Player::Update()
{
	if (!m_IsActive) return;
}

void Player::Draw()
{
	if (!m_IsActive) return;

	if (m_Splite)
	{
		m_Splite->Draw();
	}
}

/// <summary>
/// アニメーションの更新
/// </summary>
void Player::UpdateAnimation()
{
	//移動していなければ0コマ目で停止
	if (MyMath::VecLong(m_Controller->Move()) <= 0)
	{
		m_AnimationTimer = 0;
		m_AnimationIndex = 0;
		return;
	}

	if (m_AnimationTimer >= PLAYER_CHANGE_ANIM_TIME)
	{
		m_AnimationTimer = 0;
		m_AnimationIndex++;
	}
}

/// <summary>
/// 死亡処理
/// </summary>
void Player::Die()
{
	m_IsActive = false;
}
