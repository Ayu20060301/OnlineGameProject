#include "BulletManager.h"
#include "Bullet.h"
#include "../GameSetting/GameSetting.h"
#include "NetworkBullet.h"
#include "../Network/Client.h"
#include <algorithm>

constexpr float PI = 3.14159265f;

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


Bullet& BulletManager::CreateBullet()
{
	//生成して初期化
	UniquePtr<Bullet> bullet = MakeUnique<Bullet>();
	bullet->Init();

	bullet->Load();

	bullet->Start();

	//リストに追加
	m_Bullets.push_back(std::move(bullet));

	return *(m_Bullets.back().get());
}

void BulletManager::CreateRandomBullets(int count)
{
	//画面中央
	const VECTOR centerPos = VGet(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f);

	//弾を生成
	for (int i = 0; i < count; ++i)
	{
		Bullet& bullet = CreateBullet();

		//中央に配置
		bullet.SetPosition(centerPos);

		//左右どちらかをランダムに配置
		bool isRight = (rand() % 2 == 0);

		float angle;

		//右方向
		if (isRight)
		{
			angle = static_cast<float>(rand() % 61 - 30);
		}
		else
		{
			angle = static_cast<float>(rand() % 61 + 150);
		}

		//ラジアンに変換
		angle *= PI / 180.0f;

		//弾速
		const float speed = 18.0f;

		//速度ベクトルを作る
		VECTOR velocity =VGet(cosf(angle) * speed,sinf(angle) * speed,0.0f);

		bullet.SetVelocity(velocity);
	}
}

NetworkBullet& BulletManager::CreateNetworkBullet(VECTOR pos,VECTOR velocity)
{
	UniquePtr<NetworkBullet> bullet = MakeUnique<NetworkBullet>(pos, velocity);

	bullet->Init();
	bullet->Load();
	bullet->Start();

	// 初期位置・速度を設定
	bullet->SetPosition(pos);
	bullet->SetVelocity(velocity);

	m_Bullets.push_back(std::move(bullet));

	return *static_cast<NetworkBullet*>(m_Bullets.back().get());
}

void BulletManager::Login(Network::ResponseLoginData data)
{
	Clear();
}

void BulletManager::Logout(Network::LogoutData data)
{
	Clear();
}

void BulletManager::SyncServerBullet(const Network::AllBulletTransformData& data)
{
	// 既存のネットワーク弾を削除
	for (auto itr = m_Bullets.begin();
		itr != m_Bullets.end();)
	{
		if ((*itr)->IsNetworkBullet())
		{
			(*itr)->Fin();
			itr = m_Bullets.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	// サーバーに存在する弾を生成
	for (int i = 0; i < data.count; ++i)
	{
		CreateNetworkBullet(data.bullets[i].pos,data.bullets[i].velocity);
	}
}

void BulletManager::Clear()
{
	for (auto& bullet : m_Bullets)
	{
		bullet->Fin();
	}

	m_Bullets.clear();
}
