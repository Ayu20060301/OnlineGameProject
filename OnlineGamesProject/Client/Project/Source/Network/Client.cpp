#include "DxLib.h"
#include "../Input/Input.h"
#include "Client.h"
#include "NetworkCommonParam.h"
#include "../Input/InputString.h"

Client::Client()
{
	m_PartnerHandle = 0;
	m_NWState = NW_STATE_NONE;
	m_IPAddress = {};
	m_NameInput = nullptr;
	m_MessageInput = nullptr;
	m_SendChatData = {};
	m_ChatData = {};
}

Client::~Client()
{
	Fin();
}


void Client::Init()
{
	//キー文字列入力システム設定
	m_NameInput = MakeUnique<InputString>();
	m_MessageInput = MakeUnique<InputString>();

	m_NameInput->SetPos(VGet(0.0f, 20.0f, 0.0f));
	m_MessageInput->SetPos(VGet(0.0f, 20.0f, 0.0f));

	//最初は名前入力
	m_NameInput->Start();
	m_NWState = NW_STATE_INPUT_NAME;
}

void Client::Update()
{
	switch (m_NWState)
	{
	case NW_STATE_INPUT_NAME: UpdateInputName(); break;
	case NW_STATE_WAITING: UpdateWaiting(); break;
	case NW_STATE_INPUT_MESSAGE: UpdateInputMessage(); break;
	}
}

void Client::Draw()
{
	if (m_NWState == NW_STATE_INPUT_NAME)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "ユーザー名を入力");
	}
	else if (m_NWState = NW_STATE_WAITING)
	{
		DrawWaiting();
	}
	else if (m_NWState == NW_STATE_INPUT_MESSAGE)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "メッセージを入力");
		DrawFormatString(0, 840, GetColor(255, 255, 255), "Ctrl + Qで切断");
		DrawFormatString(0, 860, GetColor(255, 255, 255), "接続先IPアドレス：%d.%d.%d.%d", m_IPAddress.d1, m_IPAddress.d2, m_IPAddress.d3, m_IPAddress.d4);
	}

	m_NameInput->Draw();
	m_MessageInput->Draw();

	DrawChat();
}

void Client::Fin()
{
	//状態が接続中以降であれば切断
	if (m_NWState >= NW_STATE_WAITING)
	{
		Disconnect();
	}
}

/// <summary>
/// 切断中の更新処理
/// </summary>
void Client::UpdateInputName()
{
	//ユーザー名入力更新
	m_NameInput->Update();

	//Enterで接続
	if (Input::IsTriggerKey(KEY_ENTER))
	{
		//入力した名前を取得
		const char* name = m_NameInput->GetInputString();

		//文字数チェック
		int nameLen = (int)strlen(name);
		if (nameLen > 0)
		{
			if (nameLen <= NETWORK_USER_NAME_MAX)
			{
				//ユーザー名をチャットデータに登録
				strcpy_s(m_SendChatData.name, NETWORK_USER_NAME_MAX,name);

				//ユーザー名入力終了
				m_NameInput->Fin();

				//通信開始
				StartNetwork();
			}
			else
			{
				//長すぎたら再入力
				m_NameInput->Clear();
			}

		}

	}

}

/// <summary>
/// 接続中の更新処理
/// </summary>
void Client::UpdateInputMessage()
{
	// メッセージ入力更新
	m_MessageInput->Update();

	// Enterキーでメッセージ送信
	if (Input::IsTriggerKey(KEY_ENTER))
	{
		// 入力メッセージを取得
		const char* message = m_MessageInput->GetInputString();

		// 文字数チェック
		int messageLen = (int)strlen(message);
		if (messageLen > 0)
		{
			if (messageLen <= NETWORK_MESSAGE_MAX)
			{
				// メッセージをチャットデータに設定
				strcpy_s(m_SendChatData.message, NETWORK_MESSAGE_BUFFER_MAX, message);
				// 自分のメッセージは自分で追加
				m_ChatData.push_back(m_SendChatData);

				// 相手側に送信
				NetWorkSend(m_PartnerHandle, &m_SendChatData, sizeof(m_SendChatData));

				// メッセージをクリア
				m_MessageInput->Clear();
			}
			else
			{
				// 長すぎたら再入力
				m_MessageInput->Clear();
			}
		}
	}

	// Ctrl + Q で切断
	if ((Input::IsInputKey(KEY_CTRL_L) || Input::IsInputKey(KEY_CTRL_R)) && Input::IsTriggerKey(KEY_Q))
	{
		// 切断
		Disconnect();
	}

	// データ受信
	ReceiveData();
}

void Client::ReceiveData()
{
	//クライアントから送られたデータのサイズを取得
	int dataLength = GetNetWorkDataLength(m_PartnerHandle);

	//データが送られてきたかチェック
	if (dataLength > 0)
	{
		//受信
		ChatData receiveData = {};
		NetWorkRecv(m_PartnerHandle, &receiveData, sizeof(receiveData));

		//受信したデータをチャットに追加
		m_ChatData.push_back(receiveData);
	}
}

/// <summary>
/// チャット内容を描画
/// </summary>
void Client::DrawChat()
{
	int raw = 0;
	for (ChatData data : m_ChatData)
	{
		DrawFormatString(0, 40 + raw * 20, GetColor(255, 255, 255), "%s: %s", data.name, data.message);
		raw++;
	}
}

/// <summary>
/// ホストに接続する
/// </summary>
void Client::Connect()
{
	//指定したIPアドレスの端末に接続
	m_PartnerHandle = ConnectNetWork(m_IPAddress, PORT_NUMBER);
	//ハンドルが-1なら接続できてない
	if (m_PartnerHandle == -1)
	{
		//名前入力に戻る
		m_NameInput->Start();
	}
	else
	{
		//接続待ちへ
		m_NWState = NW_STATE_WAITING;
	}
}

/// <summary>
/// 切断する
/// </summary>
void Client::Disconnect()
{
	//切断
	CloseNetWork(m_PartnerHandle);
	m_PartnerHandle = 0;
	m_NWState = NW_STATE_INPUT_NAME;

	//メッセージ入力終了
	m_MessageInput->Fin();
	//ユーザー名入力開始
	m_MessageInput->Start();
}

/// <summary>
/// 接続開始
/// </summary>
void Client::StartNetwork()
{
	//接続
	Connect();
}

/// <summary>
/// 接続待ち
/// </summary>
void Client::UpdateWaiting()
{
	//接続できたかチェック
	if (GetNetWorkAcceptState(m_PartnerHandle))
	{
		//接続完了
		m_NWState = NW_STATE_INPUT_MESSAGE;

		//メッセージ入力開始
		m_MessageInput->Start();
	}
}

void Client::DrawWaiting()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "接続中...");
}
