#include "Item.h"
#include "../Stage/StageManager.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Component/Collision/CollisionAABB.h"
#include "../Effect/SpriteAnimationManager.h"
#include "../Effect/SpriteAnimation.h"

constexpr int ITEM_LIFE = 480;
constexpr int BLINK_TIME = 180;

Item::Item()
{
	m_IsActive = false;
	m_Life = 0;
	m_Pos = {};
	m_Param = nullptr;
	m_CollisionAABB = nullptr;
	m_SpriteAnim = nullptr;
}

Item::~Item()
{
	Fin();
}

void Item::Init()
{
	m_Life = ITEM_LIFE;
}

void Item::Load()
{

}


void Item::Step()
{
	if (!m_IsActive) return;

	//寿命処理
	if (m_Life <= 0)
	{
		Destroy();
	}
	else
	{
		m_Life--;
	}

	//位置追従
	m_SpriteAnim->SetPos(m_Pos);
}

void Item::Update()
{
	if (!m_IsActive) return;
}


void Item::Draw()
{
	if (!m_IsActive) return;

	//寿命が切れそうなら点滅
	if (m_Life <= BLINK_TIME && m_Life % 4 == 0)
	{
		m_SpriteAnim->SetHide(!m_SpriteAnim->IsHide());
	}
}

void Item::Fin()
{

}

void Item::Spawn()
{
	m_IsActive = true;
	m_Life = ITEM_LIFE;
	m_SpriteAnim = SpriteAnimationManager::GetInstance()->Play(m_Param->animID, m_Pos, 5, true);
}

void Item::HitPlayer()
{
	Destroy();
}

Item* Item::Clone()
{
	Item* clone = new Item;
	*clone = *this;

	//当たり判定設定は必要
	CollisionAABB* aabb = CollisionManager::GetInstance()->CreateAABB();
	aabb->SetSize(VGet(ITEM_WIDTH, ITEM_HEIGHT, 0.0f));
	clone->m_CollisionAABB = aabb;

	return clone;
}

void Item::Destroy()
{
	m_IsActive = false;
	m_SpriteAnim->SetActive(false);
}
