#include "GameApp.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Network/ClientAPI.h"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
	ClientAPI::Fin();
	Input::Fin();
	SceneManager::DeleteInstance();
}

void GameApp::Init()
{
	Input::Init();

	SceneManager::CreateInstance();
	SceneManager::GetInstance()->Init();
}

void GameApp::Exec()
{
	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		// 画面をクリア
		ClearDrawScreen();

		// 入力更新
		Input::Update();

		// シーン更新
		SceneManager::GetInstance()->Step();

		// ネットワーク更新
		ClientAPI::Step();
		ClientAPI::Draw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}
}
