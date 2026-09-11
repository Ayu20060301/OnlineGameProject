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

	void Init();
	void Update();
	void Draw();


	bool IsActive() const { return m_IsActive; }

	VECTOR GetPosition() const { return m_Transform.GetPosition(); }

	VECTOR GetVelocity() const { return m_Velocity; }

	void SetPosition(VECTOR pos) { m_Transform.SetPosition(pos); }

	void SetVelocity(VECTOR velocity) { m_Velocity = velocity; }

	void OverlapGameObject(GameObject& other) override;

private:	
	VECTOR m_Velocity; //弾の速度
};
