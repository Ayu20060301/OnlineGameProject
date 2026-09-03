#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{
	m_Bullets = {};
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

	//生成したバレットの参照を返す
	return *m_Bullets.back().get();
}

void BulletManager::RemoveBullet(int handle)
{
	//指定したバレットを削除
	for (auto itr = m_Bullets.begin(); itr != m_Bullets.end(); ++itr)
	{
		if ((*itr)->GetNetworkHandle() == handle)
		{
			m_Bullets.erase(itr);
			break;
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
