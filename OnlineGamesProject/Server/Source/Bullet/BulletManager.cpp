#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{
	m_Bullets = {};
	m_NextBulletID = 0;
}

void BulletManager::Init()
{
}

void BulletManager::Update()
{
}

void BulletManager::Draw()
{
	//全バレットの描画
	for (const auto& bullet : m_Bullets)
	{
		bullet->Draw();
	}
}

Bullet& BulletManager::CreateBullet()
{
	//バレットを作成して動的配列に追加
	m_Bullets.push_back(MakeUnique<Bullet>());

	Bullet& bullet = *m_Bullets.back().get();

	bullet.SetID(m_NextBulletID++);

	return bullet;
}

void BulletManager::RemoveBullet(int handle)
{
	for (auto itr = m_Bullets.begin();itr != m_Bullets.end();)
	{
		if ((*itr)->GetNetworkHandle() == handle)
		{
			itr = m_Bullets.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

Bullet* BulletManager::GetBullet(int id) const
{
	for (const auto& player : m_Bullets)
	{
		if (player->GetID() == id)
		{
			return player.get();
		}
	}

	return nullptr;
}
