#include "DxLib.h"
#include "GameApp.h"
#include "../Input/Input.h""
#include "../Network/Client.h"

GameApp::GameApp()
{
	m_Client = new Client;
	m_State = MAIN_STATE_SELECT_MODE;
	m_SelectIndex = 0;
	m_IsRunning = true;
}

GameApp::~GameApp()
{
	delete m_Client;
	m_Client = nullptr;
	Input::Fin();
}

void GameApp::Init()
{
	Input::Init();

	m_Client->Init();
}

void GameApp::Exec()
{
	while (ProcessMessage() >= 0)
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
	   case MAIN_STATE_NAME_INPUT:
		   if (m_Client) m_Client->UpdateNameChange();
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
	switch (m_State)
	{
	    case MAIN_STATE_SELECT_MODE:

			SetFontSize(32);

			DrawString(10, 50, "ユーザー名 : ", GetColor(255, 255, 255));

			DrawString(120, 300, "ホスト", GetColor(255,255,255));
			DrawString(120, 380, "クライアント", GetColor(255,255,255));
			DrawString(120, 460, "ゲームをやめる", GetColor(255,255,255));

			// 選択カーソル
			DrawString(
				80,
				300 + m_SelectIndex * 80,
				">>",
				GetColor(255,255,255)
			);
			break;
		case MAIN_STATE_NAME_INPUT:
			SetFontSize(32);
			DrawString(100, 200, "ユーザー名を入力してください", GetColor(255, 255, 255));
			//if(m_Client) m_Client->DrawNameInput();
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
			m_SelectIndex = 2;
		}
	}

	//下
	if (Input::IsTriggerKey(KEY_DOWN))
	{
		m_SelectIndex++;

		if (m_SelectIndex > 2)
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
			// クライアント
			m_Client = new Client();
			m_Client->Init();

			m_State = MAIN_STATE_CHAT;
			break;

		case 2:
			// ゲームをやめる
			m_IsRunning = false;
			break;
		}
	}

	//Zキーでユーザー名を変更
	if (Input::IsTriggerKey(KEY_Z))
	{
		if (m_Client)
		{
			m_Client->StartNameInput();
			m_State = MAIN_STATE_NAME_INPUT;
		}
	}
}

void GameApp::SetIP()
{
	if (!m_Client) return;

	IPDATA ipData;

	ipData.d1 = 192;
	ipData.d2 = 168;
	ipData.d3 = 0;
	ipData.d4 = 54;
	m_Client->SetIPAddress(ipData);

	m_State = MAIN_STATE_CHAT;
}
