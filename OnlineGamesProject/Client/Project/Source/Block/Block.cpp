#include "Block.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Component/Collision/CollisionAABB.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "BlockParameter.h"


Block::Block()
{
	m_IsActive = false;
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Collision = nullptr;
}

Block::~Block()
{
	Fin();
}

void Block::Load()
{
	m_Handle = LoadGraph("Data/Play/Stage/Block.png");
}

void Block::Start()
{
	m_IsActive = true;

	//“–‚½‚è”»’è‚ğİ’è
	m_Collision = CollisionManager::GetInstance()->CreateAABB();
	m_Collision->SetTargetPos(&m_Pos);
	m_Collision->SetSize(VGet(BLOCK_WIDTH, BLOCK_HEIGHT, 0.0f));
}

void Block::Draw()
{
	DrawGraph((int)m_Pos.x, (int)m_Pos.y, m_Handle, true);
}

void Block::Fin()
{
	DeleteGraph(m_Handle);
}

Block* Block::Clone()
{
	Block* clone = new Block;
	*clone = *this;

	clone->m_Handle = m_Handle;
	return clone;
}
