#include "DxLib.h"
#include "../Input/Input.h"
#include "Client.h"
#include "NetworkCommonParam.h"
#include "../Input/InputString.h"

Client::Client()
{
	m_State = OFFLINE;
	m_ServerHandle = 0;
}

Client::~Client()
{
	Fin();
}

void Client::Step()
{
	switch (m_State)
	{
	    case WAIT:     UpdateWaiting(); break;
	    case ONLINE:   StepOnline();    break;

		default: break;
	}
}

void Client::Draw()
{
	if (m_State == OFFLINE)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "オフライン");
	}
	else if (m_State == WAIT)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "接続中。。。");
	}
	else if (m_State == ONLINE)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "オンライン");
	}

	DrawString(0, 880, "クライアント側", GetColor(255, 255, 255));
}

void Client::Fin()
{
	if (m_State == ONLINE)
	{
		Disconnect();
	}
}

/// <summary>
/// サーバーに接続する
/// </summary>
void Client::Connect()
{
	IPDATA ip;
	ip.d1 = 192;
	ip.d2 = 168;
	ip.d3 = 0;
	ip.d4 = 54;

	//指定したIPアドレスの端末に接続
	m_ServerHandle = ConnectNetWork(ip, PORT_NUMBER);

	//ハンドルが-1なら接続できてない
	if (m_ServerHandle == -1)
	{
		m_State = OFFLINE;
	}
	else
	{
		//接続待ちへ
		m_State = WAIT;
	}
}

void Client::SendData(const void* data, unsigned int size) const
{
	if (m_State == ONLINE)
	{
		NetWorkSend(m_ServerHandle, data, size);
	}
}

bool Client::CheckReceive()
{
	return GetNetWorkDataLength(m_ServerHandle) > 0;
}

void Client::ReceiveData(void* buffer, unsigned int size)
{
	if (m_State == ONLINE)
	{
		NetWorkRecv(m_ServerHandle, buffer, size);
	}
}

/// <summary>
/// サーバーから切断する
/// </summary>
void Client::Disconnect()
{
	//切断
	CloseNetWork(m_ServerHandle);
	m_ServerHandle = 0;
	m_State = OFFLINE;
}

/// <summary>
/// 接続待機中の更新処理
/// </summary>
void Client::UpdateWaiting()
{
	//接続できたかチェック
	if (GetNetWorkAcceptState(m_ServerHandle))
	{
		//接続完了
		m_State = ONLINE;
	}
}

void Client::StepOnline()
{
	//Ctrl + Qで切断
	if ((Input::IsInputKey(KEY_CTRL_L) || Input::IsInputKey(KEY_CTRL_R)) && Input::IsTriggerKey(KEY_Q))
	{
		//切断
		Disconnect();
	}
}
