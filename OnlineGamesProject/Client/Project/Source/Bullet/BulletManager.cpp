#include "BulletManager.h"
#include "StraightBullet.h"
#include "../Component/Collision/CollisionParameter.h"

// データ群はエクセルにしたい
const BulletParameter BULLET_MASTER_DATA[]
{
	{"Data/Play/Bullet/Bullet1.png", BULLET_CATEGORY_STRAIGHT, 180, 1, COLLISION_TAG_PLAYER1, BULLET_HIT_01, 3.0f, 20.0f, 40.0f, 40.0f},
	{"Data/Play/Bullet/Bullet2.png", BULLET_CATEGORY_STRAIGHT, 180, 1, COLLISION_TAG_PLAYER2, BULLET_HIT_02, 3.0f, 20.0f, 40.0f, 40.0f},
	{"Data/Play/Bullet/Bullet3.png", BULLET_CATEGORY_STRAIGHT, 180, 1, COLLISION_TAG_PLAYER3, BULLET_HIT_03, 3.0f, 20.0f, 40.0f, 40.0f},
	{"Data/Play/Bullet/Bullet4.png", BULLET_CATEGORY_STRAIGHT, 180, 1, COLLISION_TAG_PLAYER4, BULLET_HIT_04, 3.0f, 20.0f, 40.0f, 40.0f},
};

BulletManager* BulletManager::m_Instance = nullptr;

BulletManager::BulletManager()
{
	m_OriginalBullets = {};
	m_Bullets = {};
}

BulletManager::~BulletManager()
{
	Fin();
}

void BulletManager::Load()
{
	// クローン元のバレットをロード
	for (BulletBase* bullet : m_OriginalBullets)
	{
		bullet->Load();
	}
}

void BulletManager::Step()
{
	for (BulletBase* bullet : m_Bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Step();
		}
	}
}

void BulletManager::Draw()
{
	for (BulletBase* bullet : m_Bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Draw();
		}
	}

#ifdef _DEBUG
	// m_Bulletsの個数
	DrawFormatString(0, 100, GetColor(0, 0, 0), "m_Bulletsのサイズ：%d", m_Bullets.size());
#endif
}

void BulletManager::Fin()
{
	for (BulletBase* bullet : m_OriginalBullets)
	{
		delete bullet;
	}
	for (BulletBase* bullet : m_Bullets)
	{
		delete bullet;
	}

	m_OriginalBullets.clear();
	m_Bullets.clear();
}

void BulletManager::SetupBullet(int id)
{
	BulletBase* bullet = nullptr;
	BulletParameter param = BULLET_MASTER_DATA[id];

	switch (param.category)
	{
	case BULLET_CATEGORY_STRAIGHT: bullet = new StraightBullet; break;
	}

	bullet->Init(id);

	m_OriginalBullets.push_back(bullet);
}

BulletBase* BulletManager::FireBullet(int id, VECTOR pos, VECTOR vec)
{
	// 未使用で同じIDのバレットを探す
	for (BulletBase* bullet : m_Bullets)
	{
		if (id == bullet->GetID() && !bullet->IsActive())
		{
			// バレットを再利用する
			bullet->Fire(pos, vec);
			return bullet;
		}
	}

	// 再利用できなければ新規追加
	BulletBase* bullet = CreateBullet(id);
	bullet->Fire(pos, vec);

	// vectorに追加
	m_Bullets.push_back(bullet);

	return bullet;
}

const BulletParameter* BulletManager::GetBulletParameter(int id)
{
	return &BULLET_MASTER_DATA[id];
}

BulletBase* BulletManager::CreateBullet(int id)
{
	for (BulletBase* bullet : m_OriginalBullets)
	{
		if (id == bullet->GetID())
		{
			return bullet->Clone();
		}
	}

	// 引数のバレットがセットアップされていない
	return nullptr;
}
