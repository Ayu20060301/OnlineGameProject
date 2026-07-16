#pragma once

#include "DxLib.h"
#include "CollisionBase.h"

class CollisionSphere : public CollisionBase
{
public:
	CollisionSphere();
	~CollisionSphere();

public:
	void Draw() override;			// •`‰æ

public:
	void SetRadius(float radius) { m_Radius = radius; }

	float GetRadius() { return m_Radius; }

public:
	bool CheckSphere(CollisionSphere* other);

private:
	// ‹…‚Ì”¼Œa
	float m_Radius;
};
