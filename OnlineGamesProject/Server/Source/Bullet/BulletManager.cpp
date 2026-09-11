#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{
	m_Bullets = {};
}

void BulletManager::Init()
{
}

void BulletManager::Update()
{
	//全弾更新
	for (auto& bullet : m_Bullets)
	{
		bullet->Update();
	}
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
	//弾を生成して追加
	m_Bullets.push_back(MakeUnique<Bullet>());

	Bullet& bullet = *m_Bullets.back().get();

	bullet.Init();

	return bullet;
}

void BulletManager::RemoveBullet(int index)
{
	if (index < 0 || index >= static_cast<int>(m_Bullets.size())) return;

	m_Bullets.erase(m_Bullets.begin() + index);
}

