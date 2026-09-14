#pragma once

// NetworkCommonParam.hはクライアント/サーバー共通のパラメータ
// 必ず双方で同じ状態にする必要がある

// ポート番号は49152～65535が好ましい
#define PORT_NUMBER 50000

// 残す履歴の最大数
#define CHAT_LOG_MAX 10

// 通信できるユーザー名のMAXサイズ（全角5文字まで）
constexpr int NETWORK_USER_NAME_MAX = 10;
// 文字列の長さは文字数＋終端文字
constexpr int NETWORK_USER_NAME_BUFFER_MAX = NETWORK_USER_NAME_MAX + 1;

// 通信できる文字列のMAXサイズ（全角20文字まで）
constexpr int NETWORK_MESSAGE_MAX = 40;
// 文字列の長さは文字数＋終端文字
constexpr int NETWORK_MESSAGE_BUFFER_MAX = NETWORK_MESSAGE_MAX + 1;

// クライアントが送信するデータ
struct ChatData
{
	// ユーザー名
	char name[NETWORK_USER_NAME_BUFFER_MAX];

	// 文字列（全角30文字まで）
	char message[NETWORK_MESSAGE_BUFFER_MAX];
};
