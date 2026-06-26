#include "DxLib.h"
#include "Input/Input.h"
#include "Memory/Memory.h"
#include "Scene/SceneManager.h"


//関数のプロトタイプ宣言
void GameExec();

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);
	
	// 画面解像度の設定
	SetGraphMode(1600, 900, 32);

	// 多重起動を許可する
	SetDoubleStartValidFlag(TRUE);

	// バックグラウンドでも動作し続ける
	SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ウィンドウサイズ設定
	SetWindowSize(1600, 900);

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//入力初期化
	Input::Init();

	//シーンマネージャー
	SceneManager::CreateInstance();
	SceneManager::GetInstance()->Init();

	//ゲーム実行
	GameExec();

	//入力終了
	Input::Fin();

	DxLib_End();   //DXライブラリ仕様の終了処理

	return 0; //ソフトの終了
}

/// <summary>
/// ゲームの実行処理
/// </summary>
void GameExec()
{
	//ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		//画面をクリア
		ClearDrawScreen();

		//入力更新
		Input::Update();

		//シーン更新
		SceneManager::GetInstance()->Step();

		//エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//画面フリップ
		ScreenFlip();
	}
}
