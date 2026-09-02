#include "DxLib.h"
#include "PlayScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Stage/StageManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Effect/SpriteAnimationManager.h"
#include "../Fade/ScreenFade.h"

PlayScene::PlayScene() : SceneBase()
{
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	//コリジョンマネージャーの生成
	CollisionManager::CreateInstance();

	//プレイヤーマネージャーを生成
	PlayerManager::CreateInstance();
	Player& player = PlayerManager::GetInstance()->CreatePlayer();

	//ステージマネージャーを生成
	StageManager::CreateInstance();
	StageManager::GetInstance()->CreateStage();

	//スプライトアニメーションを生成
	SpriteAnimationManager::CreateInstance();
}

void PlayScene::Load()
{
	//ステージをロード
	StageManager::GetInstance()->Load();


	//プレイヤーをロード
	PlayerManager::GetInstance()->Load();

	//スプライトアニメーションをロード
	SpriteAnimationManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	//プレイヤー開始
	PlayerManager::GetInstance()->Start();
	//フェードイン
	//ScreenFade::FadeIn(8.0f);
}

void PlayScene::Step()
{
	PlayerManager::GetInstance()->Step();

	//当たり判定
	CollisionManager::GetInstance()->CheckCollision();

	SpriteAnimationManager::GetInstance()->Step();
}

void PlayScene::Update()
{
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// ステージを描画
	StageManager::GetInstance()->Draw();
	// スプライトアニメーション描画
	SpriteAnimationManager::GetInstance()->Draw();
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();
	//当たり判定描画
	CollisionManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	StageManager::DeleteInstance();
	SpriteAnimationManager::DeleteInstance();
}
