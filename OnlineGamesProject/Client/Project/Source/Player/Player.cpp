#include "Player.h"
#include "PlayerParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Component/Renderer/Splite.h"
#include "../Component/Controller/Controller2D.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Component/Collision/CollisionAABB.h"
#include "../MyMath/MyMath.h"
#include "../Effect/SpriteAnimationManager.h"
#include "../Input/Input.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/Bullet.h"


//プレイヤーごとの画像
const char* PLAYER_GRAPHIC_PATH[] =
{
	"Data/Play/Player/Player1.png",
	"Data/Play/Player/Player2.png"
};

//コンストラクタ
Player::Player() : GameObject()
, m_IsActive(true)
, m_MoveSpeed(0.0f)
, m_Splite(nullptr)
, m_Controller(nullptr)
, m_Handle(0)
, m_InvisibleTimer(0)
, m_PlayerNumber(0)
, m_Direction(0)
, m_AnimationIndex(0)
, m_AnimationTimer(0)
, m_OldPos(VGet(0.0f,0.0f,0.0f))
, m_Move(VGet(0.0f,0.0f,0.0f))
, m_CollisionAABB(nullptr)
, m_FireTimer(0)
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
	m_IsActive = true;

	//無敵タイマーを初期化
	m_InvisibleTimer = 0;

	//アニメーション初期化
	m_AnimationIndex = 0;
	m_AnimationTimer = 0;

	//移動量を初期化
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	//プレイヤーごとに初期位置を変更
	VECTOR startPos;

	if (m_PlayerNumber == 0)
	{
		//1P
		startPos = VGet(100.0f, 100.0f, 0.0f);

		//右向き
		m_Direction = PLAYER_DIRECTION_RIGHT;
	}
	else
	{
		//2P
		startPos = VGet(1600.0f - PLAYER_WIDTH - 100.0f, 100.0f, 0.0f);

		//左向き
		m_Direction = PLAYER_DIRECTION_LEFT;
	}

	m_Transform.SetPosition(startPos);

	m_ServerTransform.SetPosition(startPos);

	//移動量を初期化
	m_Move = VGet(0.0f, 0.0f, 0.0f);
}

//ステップ
void Player::Step()
{
	//プレイヤーが無効なら何もしない
	if (!m_IsActive) return;

	//弾の発射タイマーを減らす
	if (m_FireTimer > 0)
	{
		m_FireTimer--;
	}

	//現在位置を移動前の位置として保存
	m_OldPos = m_Transform.GetPosition();

	//移動入力
	if (m_Controller != nullptr)
	{
		VECTOR moveInput = m_Controller->Move();

		//x方向の移動を禁止
		moveInput.x = 0.0f;

		//移動量を計算
		m_Move = VScale(moveInput, m_MoveSpeed);

		//現在位置+移動量
		VECTOR pos = VAdd(m_Transform.GetPosition(), m_Move);

		//画面外に出ないように制御
		if (pos.x < 0.0f)
		{
			pos.x = 0.0f;
		}
		if (pos.x > 1600.0f - PLAYER_WIDTH)
		{
			pos.x = 1600.0f - PLAYER_WIDTH;
		}

		if (pos.y < 0.0f)
		{
			pos.y = 0.0f;
		}
		if (pos.y > 900.0f - PLAYER_HEIGHT)
		{
			pos.y = 900.0f - PLAYER_HEIGHT;
		}

		//計算した座標をTransformへ設定
		m_Transform.SetPosition(pos);
	}
	else
	{
		//コントローラーが存在しない場合は移動しない
		m_Move = VGet(0.0f, 0.0f, 0.0f);
	}

	
	if (Input::IsTriggerKey(KEY_Z))
	{
		//BulletManager::GetInstance()->FireBullet(GetPos(),m_PlayerNumber);
	}
	
	//無敵時間
	if (m_InvisibleTimer > 0) m_InvisibleTimer--;
}

/// <summary>
/// 毎フレームの更新更新
/// </summary>
void Player::Update()
{
	//プレイヤーが無効なら何もしない
	if (!m_IsActive) return;

	//アニメーションの更新
	UpdateAnimation();
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
	//画像削除
	DeleteGraph(m_Handle);
}

//死亡処理
void Player::Die()
{
	m_IsActive = false;
}

/// <summary>
/// アニメーションの更新
/// </summary>
void Player::UpdateAnimation()
{
	//移動していなければ0コマ目で停止
	if (MyMath::VecLong(m_Move) <= 0)
	{
		m_AnimationTimer = 0;
		m_AnimationIndex = 0;
		return;
	}

	//アニメーションの切り替え
	if (m_AnimationTimer >= PLAYER_CHANGE_ANIM_TIME)
	{
		m_AnimationTimer = 0;
		m_AnimationIndex++;
		if (m_AnimationIndex >= PLAYER_ANIM_GRAPH_NUM)
		{
			m_AnimationIndex = 0;
		}
	}
	m_AnimationTimer++;
}
