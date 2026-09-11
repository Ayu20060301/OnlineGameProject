#include "DxLIb.h"
#include "../GameSetting/GameSetting.h"
#include "TitleScene.h"
#include "../Input/Input.h"
#include "../Network/ClientAPI.h"
#include "SceneManager.h"


TitleScene::TitleScene() : SceneBase()
, m_State(TitleState::LOGO)
, m_FadeTimer(0)
, m_SelectIndex(0)
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
	m_State = TitleState::LOGO;
	m_FadeTimer = 0;
	m_SelectIndex = 0;
}

void TitleScene::Step()
{
	switch (m_State)
	{
	   case TitleState::LOGO:
		   StepLogo();
		   break;
	   case TitleState::MENU:
		   StepMenu();
		   break;
	}
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	switch (m_State)
	{
	    case TitleState::LOGO:
			DrawLogo();
			break;
		case TitleState::MENU:
			DrawMenu();
			break;
    }
}

void TitleScene::Fin()
{
}

void TitleScene::StepLogo()
{
	//フェード用タイマー
	m_FadeTimer++;

	//Enterキーでメニューへ
	if (Input::IsTriggerKey(KEY_RETURN))
	{
		m_State = TitleState::MENU;
	}
}

void TitleScene::StepMenu()
{

	//上キー
	if (Input::IsTriggerKey(KEY_UP))
	{
		m_SelectIndex--;

		if (m_SelectIndex < 0)
		{
			m_SelectIndex = 1;
		}
	}

	//下キー
	if (Input::IsTriggerKey(KEY_DOWN))
	{
		m_SelectIndex++;

		if (m_SelectIndex > 1)
		{
			m_SelectIndex = 0;
		}
	}

	//決定
	if (Input::IsTriggerKey(KEY_RETURN))
	{
		switch (m_SelectIndex)
		{
		    case 0:
				ClientAPI::Connect(); //オンライン
				break;
			case 1:
				SceneManager::GetInstance()->ChangeScene(PLAY); //オフライン
				break;
		}

		//接続完了
		if (ClientAPI::IsConnected())
		{
			SceneManager::GetInstance()->ChangeScene(NETWORK_PLAY);
		}
	}

	//オンラインプレイ
	if (Input::IsTriggerKey(KEY_Z))
	{
		ClientAPI::Connect();
	}

	//オフラインプレイ
	if (Input::IsTriggerKey(KEY_X))
	{
		SceneManager::GetInstance()->ChangeScene(PLAY);
	}

	//接続完了
	if (ClientAPI::IsConnected())
	{
		SceneManager::GetInstance()->ChangeScene(NETWORK_PLAY);
	}
}

void TitleScene::DrawLogo()
{
	const char* title = "オンラインゲーム";

	DrawCenterString(title, 300, GetColor(255, 255, 255),100);

	//----------------
	//Enterキー表示
	//----------------

	const char* text = "Pressed Enter Key!";

	int alpha = GetFadeAlpha();

	//フェード
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawCenterString(text, 500, GetColor(255, 255, 255),32);

	//ブレンド解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::DrawMenu()
{
	const char* online = "オンラインでプレイ";
	const char* offline = "オフラインでプレイ";

	DrawCenterString(online, 420, GetColor(255, 255, 255),32);
	DrawCenterString(offline, 480, GetColor(255, 255, 255),32);

	//選択中の項目に矢印を表示
	const char* arrow = ">";

	int arrowY;

	if (m_SelectIndex == 0)
	{
		arrowY = 420;
	}
	else
	{
		arrowY = 480;
	}

	DrawString(580, arrowY, arrow, GetColor(255, 255, 255));
}

void TitleScene::DrawCenterString(const char* text, int y, unsigned int color,int size)
{
	SetFontSize(size);

	int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)));

	int x = (SCREEN_WIDTH - textWidth) / 2;

	DrawString(x, y, text, color);
}

int TitleScene::GetFadeAlpha() const
{
	const float value = 128.0f + 127.0f * sinf(m_FadeTimer * 0.05f);

	return static_cast<int>(value);
}
