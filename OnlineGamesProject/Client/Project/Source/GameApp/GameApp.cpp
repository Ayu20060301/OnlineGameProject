#include "DxLib.h"
#include "GameApp.h"
#include "../Input/Input.h""
#include "../Network/Host.h"

GameApp::GameApp()
{
	m_Client = nullptr;
	m_State = MAIN_STATE_SELECT_MODE;
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
			DrawString(0, 0, "Zキー: ホスト / Xキー: クライアント",GetColor(255,255,255));
			break;
		case MAIN_STATE_CHAT:
			if(m_Client) m_Client->Draw();
			break;
	}
}


void GameApp::UpdateSelectMode()
{
	if (Input::IsTriggerKey(KEY_Z))
	{
		m_Client = new Host();
		m_Client->Init();

		m_State = MAIN_STATE_SET_IP;
	}
}

void GameApp::SetIP()
{
	if (!m_Client) return;

	IPDATA ipData;

	ipData.d1 = 10;
	ipData.d2 = 10;
	ipData.d3 = 10;
	ipData.d4 = 10;
	m_Client->SetIPAddress(ipData);

	m_State = MAIN_STATE_CHAT;
}
