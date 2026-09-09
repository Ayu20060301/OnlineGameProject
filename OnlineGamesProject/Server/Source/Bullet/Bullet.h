#pragma once

#include "../GameObject/GameObject.h"
#include "DxLib.h"

class ComponentBase;

//サーバー用プレイヤークラス
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet() = default;

	void Init(int nwHandle);
	void Draw();

	int  GetID() const { return m_ID; }
	void SetID(int id) { m_ID = id; }
	int  GetNetworkHandle() const { return m_NWHandle; }

	VECTOR GetPosition() const { return m_Transform.GetPosition(); }

	VECTOR GetVelocity() const { return m_Velocity; }

	void SetPosition(VECTOR pos) { m_Transform.SetPosition(pos); }

	void SetVelocity(VECTOR velocity) { m_Velocity = velocity; }

	void OverlapGameObject(GameObject& other) override;

private:
	int m_ID; //弾のID
	int m_NWHandle; //所有クライアント
	IPDATA m_IPAddress; 

	VECTOR m_Velocity; //弾の速度
};
