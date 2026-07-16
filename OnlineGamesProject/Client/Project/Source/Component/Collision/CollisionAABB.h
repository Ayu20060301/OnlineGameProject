#pragma once

#include "DxLib.h"
#include "CollisionBase.h"

class CollisionAABB : public CollisionBase
{
public:
	CollisionAABB();
	~CollisionAABB();

public:
	void Draw() override;			// ï`âÊ

public:
	void SetSize(VECTOR size) { m_Size = size; }

	VECTOR GetSize() { return m_Size; }

public:
	bool CheckAABB(CollisionAABB* other);

private:
	// ècâ°âúçsÇ´ïù
	VECTOR m_Size;
};