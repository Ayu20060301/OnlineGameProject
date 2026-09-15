#pragma once

// NetworkCommonParam.hはクライアント/サーバー共通のパラメータ
// 必ず双方で同じ状態にする必要がある

namespace Network
{
	enum ShiritoriPacketType
	{
		SHIRITORI_START,
		SHIRITORI_WORD,
		SHIRITORI_RESULT,
		SHIRITORI_TURN,
		SHIRITORI_FINISH,
	};

	enum ShiritoriResult
	{
		SHIRITORI_OK,
		SHIRITORI_WRONG_TURN,
		SHIRITORI_WRONG_WORD,
		SHIRITORI_ALREADY_USED,
		SHIRITORI_END_N,
	};
}

// ポート番号は49152～65535が好ましい
constexpr int PORT_NUMBER = 50000;

//プレイヤー最大数 
constexpr int PLAYER_MAX = 2;

// 残す履歴の最大数
constexpr int CHAT_LOG_MAX = 10;

// 通信できるユーザー名のMAXサイズ（全角5文字まで）
constexpr int NETWORK_USER_NAME_MAX = 10;
// 文字列の長さは文字数＋終端文字
constexpr int NETWORK_USER_NAME_BUFFER_MAX = NETWORK_USER_NAME_MAX + 1;

// 通信できる文字列のMAXサイズ（全角20文字まで）
constexpr int NETWORK_MESSAGE_MAX = 40;
// 文字列の長さは文字数＋終端文字
constexpr int NETWORK_MESSAGE_BUFFER_MAX = NETWORK_MESSAGE_MAX + 1;

constexpr int NETWORK_WORD_BUFFER_MAX = 64;


// クライアントが送信するデータ
struct ChatData
{
	// ユーザー名
	char name[NETWORK_USER_NAME_BUFFER_MAX];

	// 文字列（全角30文字まで）
	char message[NETWORK_MESSAGE_BUFFER_MAX];
};

/// <summary>
/// サーバーからクライアントへ送るデータ
/// </summary>
struct ServerData
{
	int playerCount; //接続人数
	int turnPlayerID; //現在のターンプレイヤー
	ChatData chatData[CHAT_LOG_MAX]; //チャットログ
};


struct ShiritoriData
{
	//通信の種類
	Network::ShiritoriPacketType type;

	//判定結果
	Network::ShiritoriResult result;

	//プレイヤーID
	int playerID;

	//次に入力するプレイヤー
	int turnPlayerID;

	char name[NETWORK_USER_NAME_BUFFER_MAX];

	//単語
	char word[NETWORK_WORD_BUFFER_MAX];
};

struct ShiritoriStartData
{
	char startChar[NETWORK_WORD_BUFFER_MAX];
};