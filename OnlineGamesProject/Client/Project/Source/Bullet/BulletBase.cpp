#include "BulletBase.h"

BulletBase::BulletBase() : GameObject()
, m_IsActive(true)
, m_Velocity(VGet(0.0f,0.0f,0.0f))
, m_Handle(-1)
{
}

BulletBase::~BulletBase()
{
}

void BulletBase::Init()
{
	m_IsActive = true;
	m_Velocity = VGet(0.0f, 0.0f, 0.0f);
	m_Handle = -1;
}


void BulletBase::Load()
{
}

void BulletBase::Start()
{
	m_IsActive = true;
}

void BulletBase::Step()
{
}

void BulletBase::Update()
{
}

void BulletBase::Draw()
{
}

void BulletBase::Fin()
{
}
