#pragma once

#include "../ComponentBase.h"
#include "CollisionParameter.h"

class ColliderComponent : public ComponentBase
{
public:
	ColliderComponent();
	virtual ~ColliderComponent();

	virtual void Draw();

	ColliderType GetType() const { return m_Type; }


	virtual CollisionResult CheckCollide(const ColliderComponent& other) const = 0;

protected:
	ColliderType m_Type;
};
