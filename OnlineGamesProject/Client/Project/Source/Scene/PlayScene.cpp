#include "PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Bullet/BulletManager.h"
#include "../Effect/SpriteAnimationManager.h"
#include "../Fade/ScreenFade.h"

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

	//バレットマネージャーを生成
	BulletManager::CreateInstance();

	//スプライトアニメーションを生成
	//SpriteAnimationManager::CreateInstance();
}

void PlayScene::Load()
{
	//プレイヤーをロード
	PlayerManager::GetInstance()->Load();

	BulletManager::GetInstance()->Load();

	//スプライトアニメーションをロード
	//SpriteAnimationManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	//プレイヤー開始
	PlayerManager::GetInstance()->Start();

	BulletManager::GetInstance()->Start();

	//フェードイン
	//ScreenFade::FadeIn(8.0f);
}

void PlayScene::Step()
{
	PlayerManager::GetInstance()->Step();

	BulletManager::GetInstance()->Step();

	//SpriteAnimationManager::GetInstance()->Step();
}

void PlayScene::Update()
{
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();

	BulletManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	/// スプライトアニメーション描画
	//SpriteAnimationManager::GetInstance()->Draw();
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();

	BulletManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();
	BulletManager::DeleteInstance();
	//SpriteAnimationManager::DeleteInstance();
}
