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
	constexpr int NETWORK_PLAYER_MAX = 2;

	//弾の最大数
	constexpr int BULLET_MAX = 20;

	//パケットの種類
	enum class PacketType : uint8_t
	{
		LOGIN,
		JOIN,
		LOGOUT,
		TRANSFORM,
		ALL_TRANSFORM,

		//壁のトランスフォーム
		WALL_TRANSFORM,

		//弾のトランスフォームデータ
		BULLET_TRANSFORM,

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
		//char userName[NETWORK_USER_NAME_BUFFER_MAX];
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

	//弾トランスフォームデータ
	struct BulletTransformData
	{
		VECTOR pos;
		VECTOR velocity;
	};

	//全弾トランスフォームデータ
	struct AllBulletTransformData
	{
		int count;
		BulletTransformData bullets[BULLET_MAX];
	};

	//壁のトランスフォームデータ
	struct WallTransformData
	{
		VECTOR pos;
	};
}
