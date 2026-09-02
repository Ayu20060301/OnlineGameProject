#include "Player.h"
#include "PlayerParameter.h"
#include "../Component/Splite.h"
#include "../Component/Controller2D.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Component/Collision/CollisionAABB.h"
#include "../Component/Collision/CollisionSphere.h"
#include "../Block/Block.h"
#include "../Stage/StageParameter.h"
#include "../Stage/StageManager.h"
#include "../Stage/Stage.h"
#include "../MyMath/MyMath.h"
#include "../Effect/SpriteAnimationManager.h"
#include "../Input/Input.h"

//プレイヤーのサイズ
constexpr int PLAYER_WIDTH = 40; 
constexpr int PLAYER_HEIGHT = 40; 

//プレイヤーアニメーション
constexpr int PLAYER_ANIM_GRAPH_NUM = 4; //アニメーション枚数
constexpr int PLAYER_CHANGE_ANIM_TIME = 5; //アニメーション切り替え時間
constexpr float PLAYER_CHANGE_DIR_MOVE_DISTANCE = 0.1f; 

//プレイヤーの初期移動速度
constexpr float DEFAULT_MOVE_SPEED = 3.0f;

//無敵中の点滅間隔
constexpr int PLAYER_INVISIBLE_BLINK_TIME = 4; //無敵点滅時間

//プレイヤーごとの当たり判定タグ
const CollisionTag COLLISION_TAG[] =
{
	COLLISION_TAG_PLAYER1,
	COLLISION_TAG_PLAYER2,
	COLLISION_TAG_PLAYER3,
	COLLISION_TAG_PLAYER4,
};

//プレイヤーごとの画像
const char* PLAYER_GRAPHIC_PATH[] =
{
	"Data/Play/Player/Player1.png",
	"Data/Play/Player/Player2.png",
	"Data/Play/Player/Player3.png",
	"Data/Play/Player/Player4.png",
};

//プレイヤーごとの初期位置
const VECTOR DEFAULT_POS[] =
{
	{40.0f,40.0f,0.0f},
	{560.0f,40.0f,0.0f},
	{40.0f,320.0f,0.0f},
	{560.0f,320.0f,0.0f},
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
, m_CollisionSphere(nullptr)
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
	//プレイヤー番号に対応した画像をロード
	m_Handle = LoadGraph(PLAYER_GRAPHIC_PATH[m_PlayerNumber]);
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

	//初期座標
	//m_Pos = MyMath::VecAdd(VGet(stagePosX, stagePosY, 0.0f), DEFAULT_POS[m_PlayerNumber]);

	VECTOR startPos = VGet(100.0f, 100.0f, 0.0f);

	m_Transform.SetPosition(startPos);

	m_ServerTransform.SetPosition(startPos);

	//向き
	m_Direction = PLAYER_DIRECTION_DOWN;

	//移動速度
	m_MoveSpeed = DEFAULT_MOVE_SPEED;

	//移動量を初期化
	m_Move = VGet(0.0f, 0.0f, 0.0f);

}

//ステップ
void Player::Step()
{
	//プレイヤーが無効なら何もしない
	if (!m_IsActive) return;

	//現在位置を移動前の位置として保存
	m_OldPos = m_Transform.GetPosition();

	//移動入力
	if (m_Controller != nullptr)
	{
		VECTOR moveInput = m_Controller->Move();

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

	//無敵時間
	if (m_InvisibleTimer > 0) m_InvisibleTimer--;

	//移動方向からプレイヤーの向きを設定
	SetDirectionForMove();

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

	const Transform& renderTransform = GetRenderTransform();

	const VECTOR& pos = renderTransform.GetPosition();

	//無敵中の点滅
	if (IsInvisible())
	{
		//一定フレームだけ描画しない
		if ((m_InvisibleTimer / PLAYER_INVISIBLE_BLINK_TIME) % 2 == 0)
		{
			return;
		}
	}

	//プレイヤーの描画
	DrawRectGraph(
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		m_AnimationIndex * PLAYER_WIDTH,
		m_Direction * PLAYER_HEIGHT,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		m_Handle,
		true
	);

	//プレイヤー番号を表示
	DrawFormatString(
		static_cast<int>(pos.x) + 10,
		static_cast<int>(pos.y) - 20,
		GetColor(255, 255, 255),
		"%dP",
		m_PlayerNumber + 1
	);
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
	m_CollisionAABB->SetActive(false);
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

/// <summary>
/// 移動方向からプレイヤーの向きを決定
/// </summary>
void Player::SetDirectionForMove()
{
	//移動前の座標から向きを決定
	VECTOR moveVec = MyMath::VecCreate(m_OldPos, m_Transform.GetPosition());

	//移動量が少なすぎたら向きを変えない
	if (MyMath::VecLong(moveVec) < PLAYER_CHANGE_DIR_MOVE_DISTANCE) return;

	//XとY大きい方を優先
	if (MyMath::Absolute(moveVec.x) > MyMath::Absolute(moveVec.y))
	{
		//右
		if (moveVec.x > 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_RIGHT;
		}
		//左
		else
		{
			m_Direction = PLAYER_DIRECTION_LEFT;
		}
	}
	else
	{
		//下
		if(moveVec.y > 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_DOWN;
		}
		//上
		else
		{
			m_Direction = PLAYER_DIRECTION_UP;
		}
	}
}
