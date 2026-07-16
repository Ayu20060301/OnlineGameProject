#include "DxLib.h"
#include "StraightBullet.h"
#include "../MyMath/MyMath.h"
#include "../Player/PlayerManager.h"

StraightBullet::StraightBullet()
{
}

StraightBullet::~StraightBullet()
{
}

void StraightBullet::Step()
{
	BulletBase::Step();

	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

void StraightBullet::Draw()
{
	DrawGraph((int)m_Pos.x, (int)m_Pos.y, m_Handle, true);
}

BulletBase* StraightBullet::Clone()
{
	StraightBullet* clone = new StraightBullet;
	*clone = *this;

	return clone;
}
