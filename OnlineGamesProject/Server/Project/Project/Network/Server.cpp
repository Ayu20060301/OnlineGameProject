#include "DxLib.h"
#include "Server.h"
#include "NetworkCommonParam.h"

Server::Server()
{
	m_ClientData = {};
	m_ChatData = {};
	m_WordList = {};
	m_TurnPlayerID = 0;

	//しりとりの最初の文字
	m_StartChar[0] = '\0';

	//ゲーム開始状態
	m_IsGameStarted = false;
}

Server::~Server()
{
	Fin();
}

void Server::Init()
{
	// 接続してくるのを待つ状態にする
	int success = PreparationListenNetWork(PORT_NUMBER);
}

void Server::Update()
{
	// 新しい接続があったらそのネットワークハンドルを得る
	int acceptHandle = GetNewAcceptNetWork();

	// 新しい接続があった
	if (acceptHandle != -1)
	{
		AddUserData(acceptHandle);
	}

	// 切断があったらそのネットワークハンドルを得る
	int lostHandle = GetLostNetWork();

	// 切断があった
	if (lostHandle != -1)
	{
		RemoveUserData(lostHandle);
	}

	// データ受信処理
	ReceiveData();
}

void Server::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "接続数：%d 人 / %d人", m_ClientData.size(),PLAYER_MAX);


	//ゲーム開始済みなら最初の文字を表示
	if (m_IsGameStarted)
	{
		DrawFormatString(0, 30, GetColor(0, 255, 255), "最初の文字 : %s", m_StartChar);
	}
}

void Server::Fin()
{
	m_ClientData.clear();
	m_ChatData.clear();
	m_WordList.clear();

	m_StartChar[0] = '\0';
	m_IsGameStarted = false;
}

/// <summary>
/// ユーザーデータを追加する
/// </summary>
/// <param name="handle">追加するユーザーのハンドル</param>
void Server::AddUserData(int handle)
{
	ClientData client;

	client.handle = handle;

	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &client.ip);

	//プレイヤーIDを設定
	client.playerID = static_cast<int>(m_ClientData.size());

	//ユーザー配列に追加
	m_ClientData.push_back(client);

	//最初のプレイヤーなら、そのプレイヤーを最初のターンにする
	if (m_ClientData.size() == 1)
	{
		m_TurnPlayerID = 0;
	}

	// 現状を送信しておく
	SendChatData();

	//しりとりの現在状態も送信
	SendShiritoriData();

	//-----------------------------
	//プレイヤーが必要人数分集まった
	//-----------------------------
	if (!m_IsGameStarted && m_ClientData.size() >= PLAYER_MAX)
	{
		StartShiritori();
	}
}

/// <summary>
/// ユーザーデータを取り除く
/// </summary>
/// <param name="handle">取り除くユーザーのハンドル</param>
void Server::RemoveUserData(int handle)
{
	// イテレータを使って部分削除する
	for (auto itr = m_ClientData.begin(); itr != m_ClientData.end(); itr++)
	{
		// 削除するユーザーをハンドルから検索
		if ((*itr).handle == handle)
		{
			int removePlayerID = (*itr).playerID;

			//プレイヤーを削除
			m_ClientData.erase(itr);

			//誰もいなくなった
			if (m_ClientData.empty())
			{
				m_TurnPlayerID = 0;

				//ゲームをリセット
				m_IsGameStarted = false;
				m_StartChar[0] = '\0';
				m_WordList.clear();
			}
			//現在のターンプレイヤーが抜けた
			else if (removePlayerID == m_TurnPlayerID)
			{
				m_TurnPlayerID = m_ClientData.front().playerID;
			}

			//最新の接続人数を全員に通知
			SendChatData();

			return;
		}
	}
}

void Server::ReceiveData()
{
	bool isChatUpdate = false;
	bool isShiritoriUpdate = false;

	// 接続しているクライアント全員分処理する
	for (ClientData& client : m_ClientData)
	{
		// クライアントから送られたデータのサイズを取得
		int dataLength = GetNetWorkDataLength(client.handle);

		if (dataLength <= 0) continue;

		//-----------------------
		//しりとりデータ
		//-----------------------
		if (dataLength == sizeof(ShiritoriData))
		{
			ShiritoriData receiveData = {};

			//受信
			NetWorkRecv(client.handle, &receiveData, sizeof(receiveData));

			//現在のプレイヤーの番かチェック
			if (client.playerID != m_TurnPlayerID) continue;
			
			//送信されたプレイヤーIDをサーバー側で設定
			receiveData.playerID = client.playerID;

			//プレイヤー側をセーバー側で設定
			strcpy_s(receiveData.name, NETWORK_USER_NAME_BUFFER_MAX, client.name);

			//同じ単語が使われているか
			if (IsUseWord(receiveData.word))
			{
				//既に使われている
				receiveData.result = Network::SHIRITORI_ALREADY_USED;

				//ターンは変更しない
				receiveData.turnPlayerID = m_TurnPlayerID;

				//結果だけ送信
				NetWorkSend(client.handle, &receiveData, sizeof(receiveData));

				continue;
			}

			//正常な単語
			receiveData.result = Network::SHIRITORI_OK;

			//次のターンを計算
			int nextPlayerID = m_TurnPlayerID + 1;

			if (nextPlayerID >= static_cast<int>(m_ClientData.size()))
			{
				nextPlayerID = 0;
			}

			//次のプレイヤーに変更
			m_TurnPlayerID = nextPlayerID;

			//次に入力するプレイヤーを記録
			receiveData.turnPlayerID = m_TurnPlayerID;

			//しりとり履歴に追加
			m_WordList.push_back(receiveData);

			//最大数を超えたら古いログを削除
			if (m_WordList.size() > CHAT_LOG_MAX)
			{
				m_WordList.pop_front();
			}
			isShiritoriUpdate = true;
		}
		
		//----------------------
		//チャットデータ
		//----------------------
		else if (dataLength == sizeof(ChatData))
		{
			ChatData receiveData = {};

			//受信
			NetWorkRecv(client.handle, &receiveData, sizeof(receiveData));

			//メッセージが空ならユーザー名登録
			if (strlen(receiveData.message) == 0)
			{
				strcpy_s(client.name, NETWORK_USER_NAME_MAX, receiveData.name);
				//最新情報を送信
				isChatUpdate = true;
				continue;
			}

			//チャットデータに追加
			m_ChatData.push_back(receiveData);

			//最大数を超えたら最も古いログを削除
			if (m_ChatData.size() > CHAT_LOG_MAX)
			{
				m_ChatData.pop_front();
			}

			isChatUpdate = true;

		}

	}

	// 更新されたら全クライアントに送信して共有
	if (isChatUpdate)
	{
		SendChatData();
	}

	//しりとりが更新されたら全員に送信
	if (isShiritoriUpdate)
	{
		SendShiritoriData();

		//接続人数・ターン情報も送信
		SendChatData();
	}
}

void Server::SendShiritoriData()
{
	//しりとり履歴を配列にする
	ShiritoriData serialize[CHAT_LOG_MAX] = {};

	int i = 0;

	for (const ShiritoriData& data : m_WordList)
	{
		serialize[i] = data;
		i++;

		if (i >= CHAT_LOG_MAX) break;
	}

	//全クライアントに送信
	for (ClientData& client : m_ClientData)
	{
		NetWorkSend(client.handle, serialize, sizeof(serialize));
	}

}

/// <summary>
/// しりとりを開始する
/// </summary>
void Server::StartShiritori()
{
	//ゲーム開始済みならなにもしない
	if (m_IsGameStarted) return;
		
	//最初の文字候補
	const char* startChars[] =
	{
		"あ", "い", "う", "え", "お",
		"か", "き", "く", "け", "こ",
		"さ", "し", "す", "せ", "そ",
		"た", "ち", "つ", "て", "と",
		"な", "に", "ぬ", "ね", "の",
		"は", "ひ", "ふ", "へ", "ほ",
		"ま", "み", "む", "め", "も",
		"や", "ゆ", "よ",
		"ら", "り", "る", "れ", "ろ",
		"わ"
	};

	//ランダムに選択
	int index = GetRand(static_cast<int>(_countof(startChars)) - 1);

	//最初の文字を保存
	strcpy_s(m_StartChar, NETWORK_WORD_BUFFER_MAX, startChars[index]);

	//ゲーム開始
	m_IsGameStarted = true;

	//最初のターンはプレイヤーID 0 
	m_TurnPlayerID = 0;

	//全クライアントに開始文字を送信
	SendStartShiritoriData();

	//ターン情報も送信
	SendChatData();
}

/// <summary>
/// しりとり開始情報を全クライアントに送信する
/// </summary>
void Server::SendStartShiritoriData()
{
	ShiritoriStartData startData = {};

	strcpy_s(startData.startChar, NETWORK_WORD_BUFFER_MAX, m_StartChar);

	//全クライアントに送信
	for (ClientData& client : m_ClientData)
	{
		NetWorkSend(client.handle, &startData, sizeof(startData));
	}
}

bool Server::IsUseWord(const char* word)
{
	for (const ShiritoriData& data : m_WordList)
	{
		if (strcmp(data.word, word) == 0) return true;
	}

	return false;
}

/// <summary>
/// 全クライアントにデータを送信する
/// </summary>
void Server::SendChatData()
{
	ServerData serialize = {};

	///接続人数
	serialize.playerCount = static_cast<int>(m_ClientData.size());

	//現在のターンプレイヤー
	serialize.turnPlayerID = m_TurnPlayerID;

	//チャットログ
	int i = 0;

	for (const ChatData& data : m_ChatData)
	{
		serialize.chatData[i] = data;
		i++;
	}

	//全クライアントに送信する
	for (ClientData& client : m_ClientData)
	{
		NetWorkSend(client.handle, &serialize, sizeof(serialize));
	}
}
