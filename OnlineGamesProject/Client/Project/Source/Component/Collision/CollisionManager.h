#pragma once

#include "../../Singleton/Singleton.h"
#include <vector>


class ColliderComponent;

class CollisionManager : public Singleton<CollisionManager>
{
public:
	CollisionManager() = default;
	virtual ~CollisionManager() = default;

	void Draw();

	void Register(ColliderComponent* col);
	void Unregister(ColliderComponent* col);

	void CheckCollision();

private:
	std::vector<ColliderComponent*> m_Colliders;
};
