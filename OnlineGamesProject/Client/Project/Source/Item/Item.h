#pragma once

#include "DxLib.h"
#include "ItemParameter.h"

class CollisionAABB;
class SpriteAnimation;

class Item
{
public:
	Item();
	~Item();

public:
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Fin();
	Item* Clone();

	void Spawn();
	void HitPlayer();

public:

	bool IsActive() const { return m_IsActive; }
	CollisionAABB* GetAABB() const { return m_CollisionAABB; }
	const ItemParameter* GetParam() const { return m_Param; }
	VECTOR GetPos() const { return m_Pos; }

	void SetActive(bool isActive) { m_IsActive = isActive; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetParam(const ItemParameter* param) { m_Param = param; }

private:
	void Destroy();
private:
	bool m_IsActive;
	int  m_Life;
	VECTOR m_Pos;
	const ItemParameter* m_Param;
	CollisionAABB* m_CollisionAABB;
	SpriteAnimation* m_SpriteAnim;
};
