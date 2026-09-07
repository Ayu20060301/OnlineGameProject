#include "PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Wall/WallManager.h"
#include "../Wall/Wall.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/Bullet.h"


PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	//プレイヤーマネージャーを生成
	PlayerManager::CreateInstance();
	Player& player = PlayerManager::GetInstance()->CreatePlayer();

	//ウォールマネージャーを生成
	WallManager::CreateInstance();
	Wall& wall = WallManager::GetInstance()->CreateWall();

	BulletManager::CreateInstance();
	Bullet& bullet = BulletManager::GetInstance()->CreateBullet();
}

void PlayScene::Load()
{
	//プレイヤーをロード
	PlayerManager::GetInstance()->Load();

	//ウォールをロード
	WallManager::GetInstance()->Load();

	//バレットをロード
	BulletManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	//プレイヤー開始
	PlayerManager::GetInstance()->Start();

	//ウォール開始
	WallManager::GetInstance()->Start();

	//バレット開始
	BulletManager::GetInstance()->Start();
}

void PlayScene::Step()
{
	PlayerManager::GetInstance()->Step();

	WallManager::GetInstance()->Step();

	BulletManager::GetInstance()->Step();
}

void PlayScene::Update()
{
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();

	//ウォール更新
	WallManager::GetInstance()->Update();

	//バレット更新
	BulletManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();

	//ウォール描画
	WallManager::GetInstance()->Draw();

	//バレット描画
	BulletManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();

	WallManager::DeleteInstance();

	BulletManager::DeleteInstance();
}
