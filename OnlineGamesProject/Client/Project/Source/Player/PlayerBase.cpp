/*
#include "PlayerBase.h"
#include "PlayerManager.h"
#include "PlayerParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BulletParameter.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Component/Collision/CollisionAABB.h"
#include "../Component/Collision/CollisionSphere.h"
#include "../Bullet/BulletBase.h"
#include "../Stage/StageParameter.h"
#include "../Stage/StageManager.h"
#include "../Stage/Stage.h"
#include "../Block/Block.h"
#include "../Item/Item.h"
#include "../Item/ItemParameter.h"
#include "../UI/UIManager.h"
#include "../UI/UIImage.h"
#include "../UI/UIGauge.h"
#include "../Effect/SpriteAnimationManager.h"
#include "../Effect/EffectParameter.h"

constexpr int PLAYER_WIDTH = 40;
constexpr int PLAYER_HEIGHT = 40;
constexpr int PLAYER_ANIM_GRAPH_NUM = 4;
constexpr int PLAYER_CHANGE_ANIM_TIME = 5;
constexpr float PLAYER_CHANGE_DIR_MOVE_DISTANCE = 0.1f;
constexpr float BLOCK_PUSH_OFFSET = 0.1f;
constexpr int ATTACK_STIFFNESS = 40;
constexpr int DAMAGE_INVISIBLE_TIME = 240;
constexpr float DEFAULT_MOVE_SPEED = 1.0f;
constexpr float MOVE_SPEED_MAX = 3.0f;
constexpr float BULLET_INTERVAL = 180.0f;
constexpr float DEFAULT_BULLET_CHARGE_SPEED = 1.0f;
constexpr float BULLET_CHARGE_SPEED_MAX = 3.0f;
constexpr float DEFAULT_BULLET_SPEED = 1.0f;
constexpr float BULLET_SPEED_MAX = 2.0f;
constexpr int PLAYER_HP = 3;

const VECTOR BULLET_FIRE_DIR[] =
{
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{-1.0f,0.0f,0.0f},
	{0.0f,-1.0f,0.0f},

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
	{40.0f, 40.0f, 0.0f},
	{560.0f, 40.0f, 0.0f},
	{40.0f, 320.0f, 0.0f},
	{560.0f, 320.0f, 0.0f},
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

//コンストラクタ
PlayerBase::PlayerBase()
{
	m_IsActive = false;
	m_Handle = 0;
	m_HP = 0;
	m_InvisibleTimer = 0;
	m_PlayerNumber = 0;
	m_Direction = 0;
	m_AnimationIndex = 0;
	m_AnimationTimer = 0;
	m_UseBulletID = 0;
	m_Stiffness = 0;
	m_BulletInterval = 0.0f;
	m_BulletIntervalTime = 0.0f;
	m_MoveSpeed = 0.0f;
	m_BulletSpeed = 0.0f;
	m_BulletChargeSpeed = 0.0f;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_OldPos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_CollisionAABB = nullptr;
	m_CollisionSphere = nullptr;
	m_BulletChargeGauge = nullptr;
	m_UIHP = nullptr;
	m_Transform = {};
	m_IsUserServerTransform = false;
	m_ServerTransform = {};
}

//デストラクタ
PlayerBase::~PlayerBase()
{
	Fin();
}

//初期化
void PlayerBase::Init()
{
	//使用する弾丸
	m_UseBulletID = USE_BULLET[m_PlayerNumber];


	//弾丸をセットアップ
	BulletManager::GetInstance()->SetupBullet(m_UseBulletID);

	//UIを生成
	m_UIHP = new UIImage * [PLAYER_HP];
	m_UIHP[0] = UIManager::GetInstance()->CreateUI<UIImage>();
	m_BulletChargeGauge = UIManager::GetInstance()->CreateUI<UIGauge>();
}

//ロード
void PlayerBase::Load()
{
	m_Handle = LoadGraph(PLAYER_GRAPHIC_PATH[m_PlayerNumber]);

	//UIのロード
	LoadUI();
}

//開始
void PlayerBase::Start()
{
	m_IsActive = true;

	Stage* stage = StageManager::GetInstance()->GetStage();
	float stagePosX = stage->GetPosX();
	float stagePosY = stage->GetPosY();

	//初期トランスフォーム
	m_Pos = MyMath::VecAdd(VGet(stagePosX, stagePosY, 0.0f), DEFAULT_POS[m_PlayerNumber]);

	//移動量を初期化
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	//当たり判定(AABB)
	CollisionAABB* aabb = CollisionManager::GetInstance()->CreateAABB();
	aabb->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
	aabb->SetTargetPos(&m_Pos);
	aabb->SetTag(COLLISION_TAG[m_PlayerNumber]);
	m_CollisionAABB = aabb;

	//当たり判定(円)
	CollisionSphere* sphere = CollisionManager::GetInstance()->CreateSphere();
	sphere->SetRadius(20.0f);
	sphere->SetTargetPos(&m_Pos);
	sphere->SetTag(COLLISION_TAG[m_PlayerNumber]);
	m_CollisionSphere = sphere;

	//通常弾のインターバル
	m_BulletInterval = 0.0f;
	m_BulletIntervalTime = BULLET_INTERVAL;
	m_BulletChargeSpeed = DEFAULT_BULLET_CHARGE_SPEED;

	//HP
	m_HP = PLAYER_HP;

	//向き
	m_Direction = PLAYER_DIRECTION_DOWN;

	//移動速度
	m_MoveSpeed = DEFAULT_MOVE_SPEED;

	//弾丸の速度
	m_BulletSpeed = DEFAULT_BULLET_SPEED;


}


void PlayerBase::Step()
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

	//ゲージ更新
	m_BulletChargeGauge->SetValue(m_BulletIntervalTime - m_BulletInterval);
}


//更新
void PlayerBase::Update()
{
	if (!m_IsActive) return;

	//アニメーションの更新
	UpdateAnimation();
}


//描画
void PlayerBase::Draw()
{
	if (!m_IsActive) return;

	//無敵中は点滅
	if (IsInvisible())
	{
		if (m_InvisibleTimer % 4 == 0)
		{
			//描画
			DrawRectGraph((int)m_Pos.x, (int)m_Pos.y,
				m_AnimationIndex * PLAYER_WIDTH, m_Direction * PLAYER_HEIGHT,
				PLAYER_WIDTH, PLAYER_HEIGHT,
				m_Handle, true
			);
		}
	}
	else
	{
		//描画
		DrawRectGraph((int)m_Pos.x, (int)m_Pos.y,
			m_AnimationIndex * PLAYER_WIDTH, m_Direction * PLAYER_HEIGHT,
			PLAYER_WIDTH, PLAYER_HEIGHT,
			m_Handle, true
		);
	}
}

//終了
void PlayerBase::Fin()
{
	//画像削除
	DeleteGraph(m_Handle);
}

void PlayerBase::FireBullet()
{
	//インターバル中は撃てない
	if (IsBulletInterval()) return;

	//少し前方に発射
	VECTOR move = BULLET_FIRE_DIR[m_Direction];
	VECTOR offset = MyMath::VecScale(move, 10.0f);
	VECTOR pos = MyMath::VecAdd(m_Pos, offset);

	//発射速度
	move = BULLET_FIRE_DIR[m_Direction];
	move = MyMath::VecAdd(m_Pos, offset);

	BulletBase* bullet = BulletManager::GetInstance()->FireBullet(m_UseBulletID, pos, move);
	bullet->ScaleSpeed(m_BulletSpeed);

	//インターバルと硬直
	m_BulletInterval = m_BulletIntervalTime;
	m_Stiffness = ATTACK_STIFFNESS;
}

void PlayerBase::Dead()
{
	m_IsActive = false;
	m_CollisionAABB->SetActive(false);
}

void PlayerBase::UpdateAnimation()
{
	//移動していなければ0コマ目で停止
	if (MyMath::VecLong(m_Move) <= 0)
	{
		m_AnimationTimer = 0;
		m_AnimationIndex = 0;
		return;
	}

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

void PlayerBase::HitBlock(Block* block)
{
	//当たり判定情報を構築
	VECTOR checkPos = m_OldPos;
	CollisionAABB playerCollision;
	playerCollision.SetTargetPos(&checkPos);
	playerCollision.SetSize(m_CollisionAABB->GetSize());
	CollisionAABB* blockCollision = block->GetCollision();

	//X軸移動チェックをする
	checkPos.x += m_Move.x;

	if (playerCollision.CheckAABB(blockCollision))
	{
		VECTOR playerSize = playerCollision.GetSize();
		VECTOR blockPos = block->GetPos();
		VECTOR blockSize = blockCollision->GetSize();

		//左からあたった
		if (m_Move.x > 0.0f)
		{
			//左に押し出す
			checkPos.x -= checkPos.x + playerSize.x - blockPos.x;
		}
		//右にあたった
		else if (m_Move.x < 0.0f)
		{
			//右に押し出す
			checkPos.x += blockPos.x + blockSize.x - checkPos.x;
		}
	}

	//Y軸移動チェックをする
	checkPos = m_OldPos;
	checkPos.y += m_Move.y;

	if (playerCollision.CheckAABB(blockCollision))
	{
		VECTOR playerSize = playerCollision.GetSize();
		VECTOR blockPos = block->GetPos();
		VECTOR blockSize = blockCollision->GetSize();
		//上からあたった
		if (m_Move.y > 0.0f)
		{
			//上に押し出す
			checkPos.y -= checkPos.y + playerSize.y - blockPos.y;
		}
		//下からあたった
		else if (m_Move.y < 0.0f)
		{
			//下に押し出す
			checkPos.y += blockPos.y + blockSize.y - checkPos.y;
		}
	}

	//押し出し後の座標を設定
	m_Pos = checkPos;
}

void PlayerBase::HitBullet()
{
	//無敵中であれば何もしない
	if (IsInvisible()) return;

	//ダメージ
	Damage(1);

	//無敵時間
	m_InvisibleTimer = DAMAGE_INVISIBLE_TIME;
}

void PlayerBase::HitItem(Item* item)
{
	const ItemParameter* itemParam = item->GetParam();

	switch (itemParam->id)
	{
	    case ITEM_ID_PLAYER_SPEED_UP:
			m_MoveSpeed += itemParam->value;
			if (m_MoveSpeed > MOVE_SPEED_MAX) m_MoveSpeed = MOVE_SPEED_MAX;
			break;
		case ITEM_ID_BULLET_RAPID_UP:
			m_BulletChargeSpeed += itemParam->value;
			if (m_BulletChargeSpeed > BULLET_CHARGE_SPEED_MAX) m_BulletChargeSpeed = BULLET_CHARGE_SPEED_MAX;
			break;
		case ITEM_ID_BULLET_SPEED_UP:
			m_BulletSpeed += itemParam->value;
			if (m_BulletSpeed > BULLET_SPEED_MAX) m_BulletSpeed = BULLET_SPEED_MAX;
			break;
	}
}

void PlayerBase::SetDirectionForMove()
{
	// 移動前の座標から向きを決定
	VECTOR moveVec = MyMath::VecCreate(m_OldPos, m_Pos);

	// 移動量が少なすぎたら向きを変えない
	if (MyMath::VecLong(moveVec) < PLAYER_CHANGE_DIR_MOVE_DISTANCE)return;

	// XとY大きい方を優先
	if (MyMath::Absolute(moveVec.x) > MyMath::Absolute(moveVec.y))
	{
		if (moveVec.x > 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_RIGHT;
		}
		else
		{
			m_Direction = PLAYER_DIRECTION_LEFT;
		}
	}
	else
	{
		if (moveVec.y > 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_DOWN;
		}
		else
		{
			m_Direction = PLAYER_DIRECTION_UP;
		}
	}
}

void PlayerBase::LoadUI()
{
	m_UIHP[0]->Load("Data/Play/UI/Heart.png");
	m_BulletChargeGauge->Load("Data/Play/UI/BulletGaugeFrame.png", "Data/Play/UI/BulletGauge.png");
}

void PlayerBase::LocateUI()
{
	// １個目のハートの座標
	const VECTOR HP_POS[] = {
		{20.0f, 90.0f, 0.0f},
		{1480.0f, 90.0f, 0.0f},
		{20.0f, 720.0f, 0.0f},
		{1480.0f, 720.0f, 0.0f},
	};

	// 1個目のハートを配置
	VECTOR pos = HP_POS[m_PlayerNumber];
	m_UIHP[0]->SetPos(pos);

	// 2個目以降のハートを配置
	// プレイヤー番号が偶数か奇数かで並ぶ向きを変える
	int offset = (m_PlayerNumber % 2) == 0 ? m_UIHP[0]->GetWidth() : -m_UIHP[0]->GetWidth();
	for (int i = 1; i < PLAYER_HP; i++)
	{
		m_UIHP[i] = static_cast<UIImage*>(UIManager::GetInstance()->CloneUI(m_UIHP[0]));
		pos.x += offset;
		m_UIHP[i]->SetPos(pos);
	}

	const VECTOR BULLET_CHARGE_GAUGE_POS[] = {
		{20.0f, 190.0f, 0.0f},
		{1300.0f, 190.0f, 0.0f},
		{20.0f, 680, 0.0f},
		{1300.0f, 680, 0.0f},
	};

	pos = BULLET_CHARGE_GAUGE_POS[m_PlayerNumber];
	m_BulletChargeGauge->SetPos(pos);
	m_BulletChargeGauge->SetGaugePos(VGet(3.0f, 3.0f, 0.0f));
	m_BulletChargeGauge->SetMaxValue(m_BulletIntervalTime);
}

void PlayerBase::Damage(int damage)
{
	// ダメージ前HP
	int prevHP = m_HP;
	// HP減少
	m_HP -= damage;
	// ダメージを受けた分のハートを消す
	for (int i = (prevHP - 1); i >= m_HP; i--)
	{
		m_UIHP[i]->SetHide(true);
	}

	// 死亡判定
	if (m_HP <= 0)
	{
		m_IsActive = false;
		// 死亡アニメーション
		const int ANIM_ID[] = { PLAYER1_DEAD,PLAYER2_DEAD,PLAYER3_DEAD,PLAYER4_DEAD };
		SpriteAnimationManager::GetInstance()->Play(ANIM_ID[m_PlayerNumber], m_Pos, 20);
	}
}*/