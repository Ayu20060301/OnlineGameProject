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
#include "../Bullet/BulletParameter.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BulletBase.h"
#include "../Input/Input.h"

constexpr int PLAYER_WIDTH = 40; //横幅
constexpr int PLAYER_HEIGHT = 40; //縦幅
constexpr int PLAYER_ANIM_GRAPH_NUM = 4; //アニメーション枚数
constexpr int PLAYER_CHANGE_ANIM_TIME = 5; //アニメーション切り替え時間
constexpr float PLAYER_CHANGE_DIR_MOVE_DISTANCE = 0.1f; 
constexpr float DEFAULT_MOVE_SPEED = 3.0f;
constexpr int PLAYER_INVISIBLE_BLINK_TIME = 4; //無敵点滅時間
constexpr int BULLET_INTERVAL = 180.0f;
constexpr int DEFAULT_BULLET_CHARGE_SPEED = 1.0f;
constexpr int DEFAULT_BULLET_SPEED = 2; //弾丸速度

const VECTOR BULLET_FIRE_DIR[] =
{
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{-1.0f,0.0f,0.0f},
	{0.0f,-1.0f,0.0f},
};

const CollisionTag COLLISION_TAG[] =
{
	COLLISION_TAG_PLAYER1,
	COLLISION_TAG_PLAYER2,
	COLLISION_TAG_PLAYER3,
	COLLISION_TAG_PLAYER4,
};

const BulletID USE_BULLET[] =
{
	BULLET_ID_PLAYER1,
	BULLET_ID_PLAYER2,
	BULLET_ID_PLAYER3,
	BULLET_ID_PLAYER4,
};

const char* PLAYER_GRAPHIC_PATH[] =
{
	"Data/Play/Player/Player1.png",
	"Data/Play/Player/Player2.png",
	"Data/Play/Player/Player3.png",
	"Data/Play/Player/Player4.png",
};

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
, m_ScaleSpeed(0.0f)
, m_RotSpeed(0.0f)
, m_Splite(nullptr)
, m_Controller(nullptr)
, m_Handle(0)
, m_InvisibleTimer(0)
, m_PlayerNumber(0)
, m_Direction(0)
, m_AnimationIndex(0)
, m_AnimationTimer(0)
, m_UseBulletID(0)
, m_Stiffness(0)
, m_BulletInterval(0.0f)
, m_BulletIntervalTime(0.0f)
, m_BulletSpeed(0.0f)
, m_BulletChargeSpeed(0.0f)
, m_Pos(VGet(0.0f,0.0f,0.0f))
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
	m_MoveSpeed = 10.0f;
	m_ScaleSpeed = 0.01f;
	m_RotSpeed = 0.01f;
	m_Splite = AddComponent<Splite>();
	m_Controller = AddComponent<Controller2D>();
}


//ロード
void Player::Load()
{
	m_Handle = LoadGraph(PLAYER_GRAPHIC_PATH[m_PlayerNumber]);
}


//スタート
void Player::Start()
{

	m_IsActive = true;

	Stage* stage = StageManager::GetInstance()->GetStage();
	float stagePosX = stage->GetPosX();
	float stagePosY = stage->GetPosY();

	//無敵タイマーを初期化
	m_InvisibleTimer = 0;

	//アニメーション初期化
	m_AnimationIndex = 0;
	m_AnimationTimer = 0;

	//移動量を初期化
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	//初期座標
	m_Pos = MyMath::VecAdd(VGet(stagePosX, stagePosY, 0.0f), DEFAULT_POS[m_PlayerNumber]);


	//通常弾のインターバル
	m_BulletInterval = 0.0f;
	m_BulletIntervalTime = BULLET_INTERVAL;
	m_BulletChargeSpeed = DEFAULT_BULLET_CHARGE_SPEED;

	//向き
	m_Direction = PLAYER_DIRECTION_DOWN;

	//移動速度
	m_MoveSpeed = DEFAULT_MOVE_SPEED;

	//移動量を初期化
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	//弾丸の速度	
	m_BulletSpeed = DEFAULT_BULLET_SPEED;

}

//ステップ
void Player::Step()
{
	if (!m_IsActive) return;

	m_OldPos = m_Pos;

	//バレットインターバル
	if (m_BulletInterval > 0.0f) m_BulletInterval -= m_BulletChargeSpeed;
	if (m_BulletInterval < 0.0f) m_BulletInterval = 0.0f;

	//硬直
	if (m_Stiffness > 0) m_Stiffness--;

	//無敵時間
	if (m_InvisibleTimer > 0) m_InvisibleTimer--;

	//移動入力
	if (m_Controller != nullptr)
	{
		VECTOR moveInput = m_Controller->Move();

		m_Move = VScale(moveInput, m_MoveSpeed);

		m_Pos = VAdd(m_Pos, m_Move);

		//画面外に出ないように制御
		if (m_Pos.x < 0.0f)
		{
			m_Pos.x = 0.0f;
		}
		if (m_Pos.x > 1600.0f - PLAYER_WIDTH)
		{
			m_Pos.x = 1600.0f - PLAYER_WIDTH;
		}

		if (m_Pos.y < 0.0f)
		{
			m_Pos.y = 0.0f;
		}
		if (m_Pos.y > 900.0f - PLAYER_HEIGHT)
		{
			m_Pos.y = 900.0f - PLAYER_HEIGHT;
		}
	}
	else
	{
		m_Move = VGet(0.0f, 0.0f, 0.0f);
	}

	//弾を発射させる処理
	if (Input::IsTriggerKey(KEY_Z))
	{
		//FireBullet();
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
	if (!m_IsActive) return;

	UpdateAnimation();
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	if (!m_IsActive) return;

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
		static_cast<int>(m_Pos.x),
		static_cast<int>(m_Pos.y),
		m_AnimationIndex * PLAYER_WIDTH,
		m_Direction * PLAYER_HEIGHT,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		m_Handle,
		true
	);

	//プレイヤー番号を表示
	DrawFormatString(
		static_cast<int>(m_Pos.x) + 10,
		static_cast<int>(m_Pos.y) - 20,
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

void Player::FireBullet()
{
	//インターバル中は撃てない
	if (IsBulletInterval()) return;

	//少し前方に発射
	VECTOR move = BULLET_FIRE_DIR[m_Direction];
	VECTOR offset = MyMath::VecScale(move, 10.0f);
	VECTOR pos = MyMath::VecAdd(m_Pos, offset);

	//発射速度
	move = BULLET_FIRE_DIR[m_Direction];
	move = MyMath::VecScale(move, m_BulletSpeed);

	BulletBase* bullet = BulletManager::GetInstance()->FireBullet(m_UseBulletID, pos, move);
	bullet->ScaleSpeed(m_BulletSpeed);

	//インターバルと硬直
	m_BulletInterval = m_BulletIntervalTime;
	

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
	VECTOR moveVec = MyMath::VecCreate(m_OldPos, m_Pos);

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
