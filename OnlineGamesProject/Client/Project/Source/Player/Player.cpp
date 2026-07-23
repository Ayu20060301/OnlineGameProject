#include "Player.h"
#include "../Component/Splite.h"
#include "../Component/Controller2D.h"
#include "../MyMath/MyMath.h"



//コンストラクタ
Player::Player() : GameObject()
, m_IsActive(true)
, m_MoveSpeed(0.0f)
, m_ScaleSpeed(0.0f)
, m_RotSpeed(0.0f)
, m_Splite(nullptr)
, m_Controller(nullptr)
{
}

//デストラクタ
Player::~Player() = default;

//初期化
void Player::Init()
{
	m_MoveSpeed = 10.0f;
	m_ScaleSpeed = 0.01f;
	m_RotSpeed = 0.01f;
	m_Splite = AddComponent<Splite>();
	m_Controller = AddComponent<Controller2D>();
}

//ロード
void Player::Load()
{
	m_Splite->Load("Data/Player/Player1.png");
}

//スタート
void Player::Start()
{
	//初期ポジション
	SetPosition(VGet(100.0f, 100.0f, 0.0f));
}

//ステップ
void Player::Step()
{
	if (!m_IsActive) return;

	VECTOR pos = m_Transform.GetPosition();
	VECTOR scale = m_Transform.GetScale();
	VECTOR rot = m_Transform.GetRotation();

	//移動入力
	pos += m_Controller->Move() * m_MoveSpeed;

	//拡縮入力
	scale += m_Controller->Scale() * m_ScaleSpeed;

	//回転入力
	rot += m_Controller->Rotate() * m_RotSpeed;
 
	m_Transform.SetPosition(pos);
	m_Transform.SetScale(scale);
	m_Transform.SetRotation(rot);
}

//描画
void Player::Draw()
{
	if (!m_IsActive) return;

	if (m_Splite)
	{
		m_Splite->Draw();
	}
}

//死亡処理
void Player::Die()
{
	m_IsActive = false;
}
