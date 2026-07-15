#pragma once
#include "DxLib.h"
#include <cstdint>

// NetworkCommonParam.hはクライアント/サーバー共通のパラメータ
// 必ず双方で同じ状態にする必要がある

namespace Network
{
	//ポート番号
	constexpr int PORT_NUMBER = 50000;

	//プレイヤー最大人数
	constexpr int NETWORK_PLAYER_MAX = 4;

	//通信できるユーザー名のMAXサイズ(全角5文字まで)
	constexpr int NETWORK_USER_NAME_MAX = 10;

	//文字列の長さは文字数+終端文字
	constexpr int NETWORK_USER_NAME_BUFFER_MAX = NETWORK_USER_NAME_MAX + 1;

	//通信できる文字列のMAXサイズ
	constexpr int NETWORK_MESSAGE_MAX = 40;

	//文字列の長さは文字数+終端文字
	constexpr int NETWORK_MESSAGE_BUFFER_MAX = NETWORK_MESSAGE_MAX + 1;

	//パケットの種類
	enum class PacketType : uint8_t
	{
		LOGIN,
		JOIN,
		LOGOUT,
		TRANSFORM,
		ALL_TRANSFORM,
		DIE
	};

	//全通信に使用するパケットデータ
	struct PacketHeader
	{
		PacketType type; //種類
		uint16_t size; //データサイズ(符号なし16ビット)
	};

	//ログインデータ(リクエスト)
	struct RequestLoginData
	{
		char userName[NETWORK_USER_NAME_BUFFER_MAX];
	};

	//ログインデータ(レスポンス)
	struct ResponseLoginData
	{
		int selfID;
		int playerID[NETWORK_PLAYER_MAX];
		VECTOR spawnPos;
	};

	//他プレイヤー参加データ
	struct JoinData
	{
		int playerID;
		VECTOR spawnPos;
	};

	//プレイヤーログアウトデータ
	struct LogoutData
	{
		int playerID;
	};

	//プレイヤーの座標データ
	struct PosData
	{
		int playerID;
		VECTOR pos;
	};


	//プレイヤーの回転データ
	struct RotData
	{
		int playerID;
		VECTOR rot;
	};

	//プレイヤーの拡縮データ
	struct ScaleData
	{
		int playerID;
		VECTOR scale;
	};

	struct RequestTransformData
	{
		int playerID;
		VECTOR pos;
		VECTOR rot;
		VECTOR scale;
	};

	//全プレイヤーのトランスフォームデータ
	struct ResponseTransformData
	{
		VECTOR pos[NETWORK_PLAYER_MAX];
		VECTOR rot[NETWORK_PLAYER_MAX];
		VECTOR scale[NETWORK_PLAYER_MAX];
	};

	//プレイヤーの死亡データ
	struct DieData
	{
		int playerID;
	};
}
