#include "BulletManager.h"
#include "BulletBase.h"
#include "StraightBullet.h"
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

BulletBase& BulletManager::CreateStraightBullet(VECTOR pos, VECTOR velocity)
{
	UniquePtr<StraightBullet> bullet = MakeUnique<StraightBullet>(pos, velocity);

	bullet->Init();
	bullet->Load();
	bullet->Start();

	m_Bullets.push_back(std::move(bullet));

	return *m_Bullets.back();
}

/// <summary>
/// ネットワーク弾の生成
/// </summary>
/// <param name="id">発射したバレットのID</param>
/// <param name="ownerID">発射した弾のプレイヤーID</param>
/// <param name="pos">発射する座標</param>
/// <param name="velocity">発射する向き</param>
/// <returns></returns>
NetworkBullet& BulletManager::CreateNetworkBullet(int id, int ownerID, VECTOR pos, VECTOR velocity)
{
	UniquePtr<NetworkBullet> bullet = MakeUnique<NetworkBullet>(id, ownerID);

	bullet->Init();
	bullet->Load();
	bullet->Start();

	//現在位置
	bullet->SetPosition(pos);

	//サーバー情報
	bullet->SetServerPosition(pos);
	bullet->SetServerVelocity(velocity);

	m_Bullets.push_back(std::move(bullet));

	return *static_cast<NetworkBullet*>(m_Bullets.back().get());
}

void BulletManager::SyncServerTransform(Network::ResponseBulletTransformData data)
{
	//全バレットのトランスフォームをサーバーから受信する
	int i = 0;
	for (auto& bullet : m_Bullets)
	{

		//NetworkBulletではない弾は無視
		if (!bullet->IsNetworkBullet()) continue;

		NetworkBullet* nwBullet = static_cast<NetworkBullet*>(bullet.get());


		nwBullet->SetServerPosition(data.pos[i]);
		nwBullet->SetServerVelocity(data.velocity[i]);

		i++;
	}
}

/// <summary>
/// 弾を死亡させる
/// </summary>
/// <param name="bulletID">発射した弾のID</param>
void BulletManager::DieBullet(int bulletID)
{
	//IDが一致したバレットを死亡させる
	for (auto itr = m_Bullets.begin(); itr != m_Bullets.end(); itr++)
	{
		NetworkBullet* nwBullet = static_cast<NetworkBullet*>((*itr).get());

		if (nwBullet->GetID() == bulletID)
		{
			//nwBullet->Die();
			break;
		}
	}
}

void BulletManager::Clear()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->SetActive(false);
	}
}

NetworkBullet* BulletManager::FindNetworkBullet(int bulletID)
{
	for (auto& bullet : m_Bullets)
	{
		if(!bullet->IsNetworkBullet()) continue;

		NetworkBullet* nwBullet = static_cast<NetworkBullet*>(bullet.get());

		if (nwBullet->GetID() == bulletID) return nwBullet;
	}

	return nullptr;
}
