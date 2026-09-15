#include "DxLib.h"
#include "GameApp.h"
#include "../Input/Input.h""
#include "../Network/Client.h"
#include "../BG/BackGround.h"

GameApp::GameApp()
{
	m_Client = new Client;
	m_BackGround = new BackGround;
	m_State = MAIN_STATE_SELECT_MODE;
	m_SelectIndex = 0;
	m_IsRunning = true;
}

GameApp::~GameApp()
{
	delete m_Client;
	m_Client = nullptr;

	delete m_BackGround;
	m_BackGround = nullptr;

	Input::Fin();
}

void GameApp::Init()
{
	Input::Init();

	m_BackGround->Load();
	m_Client->Init();
}

void GameApp::Exec()
{
	while (m_IsRunning && ProcessMessage() >= 0)
	{
		Sleep(1);

		ClearDrawScreen();

		Input::Update();

		Update();

		Draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();
	}
}

void GameApp::Update()
{
	switch (m_State)
	{
	   case MAIN_STATE_SELECT_MODE:
		UpdateSelectMode();
		   break;
	   case MAIN_STATE_SET_IP:
		   SetIP();
		   break;
	   case MAIN_STATE_CHAT:
		   if (m_Client) m_Client->Update();
		   break;
	}
}

void GameApp::Draw()
{

	//背景を最初に描画
	if (m_BackGround)
	{
		m_BackGround->Draw();
	}

	switch (m_State)
	{
	    case MAIN_STATE_SELECT_MODE:

			SetFontSize(32);


			DrawString(120, 300, "プレイ", GetColor(255,255,255));
			DrawString(120, 460, "ゲームをやめる", GetColor(255,255,255));

			// 選択カーソル
			DrawString(80,300 + m_SelectIndex * 160,">>",GetColor(255,255,255));
			break;
		case MAIN_STATE_CHAT:
			if(m_Client) m_Client->Draw();
			break;
	}
}


void GameApp::UpdateSelectMode()
{
	//上
	if (Input::IsTriggerKey(KEY_UP))
	{
		m_SelectIndex--;

		if (m_SelectIndex < 0)
		{
			m_SelectIndex = 1;
		}
	}

	//下
	if (Input::IsTriggerKey(KEY_DOWN))
	{
		m_SelectIndex++;

		if (m_SelectIndex > 1)
		{
			m_SelectIndex = 0;
		}
	}

	if (Input::IsTriggerKey(KEY_RETURN))
	{
		switch (m_SelectIndex)
		{
		case 0:
			// ホスト
			m_Client = new Client();
			m_Client->Init();
			m_State = MAIN_STATE_CHAT;
			break;
		case 1:
			//ゲームをやめる
			m_IsRunning = false;
			break;
		}
	}

}

void GameApp::SetIP()
{
	if (!m_Client) return;

	IPDATA ipData;

	ipData.d1 = 10;
	ipData.d2 = 0;
	ipData.d3 = 80;
	ipData.d4 = 123;
	m_Client->SetIPAddress(ipData);

	m_State = MAIN_STATE_CHAT;
}
