#pragma once

#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <vector>

namespace Network
{
	template<typename T>
	std::vector<uint8_t> MakePacket(PacketType type, const T& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(T);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.type = type;
		header.size = sizeof(T);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(T));

		return buffer;
	}
}
