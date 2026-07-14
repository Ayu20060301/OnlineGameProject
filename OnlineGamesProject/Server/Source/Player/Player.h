#pragma once

#include "../GameObject/GameObject.h"
#include "DxLib.h"

class ComponentBase;

//サーバー用プレイヤークラス
class Player : public GameObject
{
public:
	Player();
	~Player() = default;

	void Init(int nwHandle);
	void Draw();

	int GetID() const { return m_ID; }
	int  GetNetworkHandle() const { return m_NWHandle; }

	void OverlapGameObject(GameObject& other) override;

private:
	int m_ID;
	int m_NWHandle;
	IPDATA m_IPAddress;
};
