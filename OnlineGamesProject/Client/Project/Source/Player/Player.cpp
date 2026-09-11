#include "Player.h"
#include "../GameSetting/GameSetting.h"
#include "../Component/Renderer/Splite.h"
#include "../Component/Controller/Controller2D.h"
#include "../MyMath/MyMath.h"

//コンストラクタ
Player::Player() : GameObject()
, m_IsActive(true)
, m_MoveSpeed(0.0f)
, m_Splite(nullptr)
, m_Controller(nullptr)
{
}

//デストラクタ
Player::~Player() = default;

//初期化
void Player::Init()
{
	//移動速度
	m_MoveSpeed = 10.0f;

	//コンポーネントの追加
	m_Splite = AddComponent<Splite>();
	m_Controller = AddComponent<Controller2D>();
}


//ロード
void Player::Load()
{
	m_Splite->Load("Data/Play/Player/Player.png");
}


//スタート
void Player::Start()
{
	SetPosition(VGet(300.0f, 400.0f, 0.0f));
}

//ステップ
void Player::Step()
{
	if (!m_IsActive) return;

	VECTOR pos = m_Transform.GetPosition();
	VECTOR scale = m_Transform.GetScale();
	VECTOR rot = m_Transform.GetRotation();

	//移動入力
	VECTOR move = m_Controller->Move();

	//横方向の移動を禁止
	move.x = 0.0f;

	pos += move * m_MoveSpeed;

	//画面外に出ないようにする
	// 画面外に出ないようにする
	if (pos.y < 20.0f)
	{
		pos.y = 20.0f;
	}
	else if (pos.y > 880.0f)
	{
		pos.y = 880.0f;
	}

	m_Transform.SetPosition(pos);
	m_Transform.SetScale(scale);
	m_Transform.SetRotation(rot);
}

/// <summary>
/// 毎フレームの更新更新
/// </summary>
void Player::Update()
{
	//プレイヤーが無効なら何もしない
	if (!m_IsActive) return;

}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	//プレイヤーが無効なら何もしない
	if (!m_IsActive) return;
	m_Splite->Draw();
}

void Player::Fin()
{
}

//死亡処理
void Player::Die()
{
	m_IsActive = false;
}

