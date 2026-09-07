#include "BulletManager.h"
#include "Bullet.h"
#include "NetworkBullet.h"
#include "../Network/Client.h"
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

	//死んだ弾を削除
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

void BulletManager::FireBullet(VECTOR playerPos)
{
	// 新しい弾を生成
	Bullet& bullet = CreateBullet();

	// プレイヤーの位置から発射
	bullet.FireBullet(playerPos);
}

Bullet& BulletManager::CreateBullet()
{
	//生成して初期化
	UniquePtr<Bullet> bullet = MakeUnique<Bullet>();
	bullet->Init();

	//ロード
	bullet->Load();

	//スタート
	bullet->Start();

	//リストに追加
	m_Bullets.push_back(std::move(bullet));

	return *(m_Bullets.back().get());
}

void BulletManager::SyncServerTransform(Network::ResponseBulletTransformData data)
{
}

void BulletManager::DieBullet(int bulletID)
{
}



void BulletManager::Clear()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->SetActive(false);
	}
}

