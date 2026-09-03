#include "BulletManager.h"
#include "BulletBase.h"
#include "StraightBullet.h"
#include <algorithm>

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	Fin();
}

void BulletManager::Init()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Init();
	}
}

void BulletManager::Load()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Load();
	}
}

void BulletManager::Start()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Start();
	}
}

void BulletManager::Step()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Step();
	}

	//Ž€‚ñ‚¾’e‚ðíœ
	for (auto itr = m_Bullets.begin(); itr != m_Bullets.end();)
	{
		if (!(*itr)->IsActive())
		{
			(*itr)->Fin();
			itr = m_Bullets.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void BulletManager::Update()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Update();
	}
}

void BulletManager::Draw()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Draw();
	}
}

void BulletManager::Fin()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Fin();
	}

	m_Bullets.clear();
}

BulletBase& BulletManager::CreateStraightBullet(VECTOR pos, VECTOR velocity)
{
	UniquePtr<StraightBullet> bullet = MakeUnique<StraightBullet>(pos, velocity);

	bullet->Init();
	bullet->Load();
	bullet->Start();

	m_Bullets.push_back(std::move(bullet));

	return *m_Bullets.back();
}

void BulletManager::Clear()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->SetActive(false);
	}
}
