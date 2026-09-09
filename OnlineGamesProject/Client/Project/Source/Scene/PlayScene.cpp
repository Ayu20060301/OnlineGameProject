#include "PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Wall/WallManager.h"
#include "../Wall/Wall.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/Bullet.h"


PlayScene::PlayScene()
{
	m_BulletTimer = 0;
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	//プレイヤーマネージャーを生成
	PlayerManager::CreateInstance();
	PlayerManager::GetInstance()->CreatePlayer();

	//ウォールマネージャーを生成
	WallManager::CreateInstance();
	WallManager::GetInstance()->CreateWall();

	//バレットマネージャーを生成
	BulletManager::CreateInstance();
}

void PlayScene::Load()
{
	//プレイヤーをロード
	PlayerManager::GetInstance()->Load();

	//ウォールをロード
	WallManager::GetInstance()->Load();

	BulletManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	//プレイヤー開始
	PlayerManager::GetInstance()->Start();

	//ウォール開始
	WallManager::GetInstance()->Start();

	BulletManager::GetInstance()->Start();
}

void PlayScene::Step()
{
	PlayerManager::GetInstance()->Step();

	WallManager::GetInstance()->Step();

	++m_BulletTimer;

	if (m_BulletTimer >= 10)
	{
		m_BulletTimer = 0;

		//1発だけ生成
		BulletManager::GetInstance()->CreateRandomBullets(1);
	}

	BulletManager::GetInstance()->Step();
}

void PlayScene::Update()
{
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();

	//ウォール更新
	WallManager::GetInstance()->Update();

	BulletManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();

	//ウォール描画
	WallManager::GetInstance()->Draw();

	BulletManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();

	WallManager::DeleteInstance();

	BulletManager::DeleteInstance();
}
