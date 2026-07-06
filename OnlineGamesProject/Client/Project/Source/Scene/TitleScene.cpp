#include "DxLIb.h"
#include "TitleScene.h"
#include "../Input/Input.h"
#include "../Network/ClientAPI.h"
#include "SceneManager.h"
#include "../GameApp/GameApp.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Load()
{
}

void TitleScene::Start()
{
}

void TitleScene::Step()
{
	if (Input::IsTriggerKey(KEY_Z))
	{
		//ネットワーク開始
		ClientAPI::Connect();
	}
	else if (Input::IsTriggerKey(KEY_X))
	{
		SceneManager::GetInstance()->ChangeScene(PLAY);
	}

	//接続したらプレイシーンへ
	if (ClientAPI::IsConnected())
	{
		SceneManager::GetInstance()->ChangeScene(NETWORK_PLAY);
	}
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Zキーでオンラインプレイ");
	DrawFormatString(0, 20, GetColor(255, 255, 255), "Xキーでオフラインプレイ");
}

void TitleScene::Fin()
{
}
