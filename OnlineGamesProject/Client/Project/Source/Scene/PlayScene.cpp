#include "PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
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

	//バレットマネージャーを生成
	BulletManager::CreateInstance();
}

void PlayScene::Load()
{
	//プレイヤーをロード
	PlayerManager::GetInstance()->Load();


	BulletManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	//プレイヤー開始
	PlayerManager::GetInstance()->Start();

	BulletManager::GetInstance()->Start();
}

void PlayScene::Step()
{
	PlayerManager::GetInstance()->Step();


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

	BulletManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();

	BulletManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();

	BulletManager::DeleteInstance();
}
