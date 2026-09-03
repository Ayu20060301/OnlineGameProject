#include "ColliderComponent.h"
#include "CollisionManager.h"

ColliderComponent::ColliderComponent() : ComponentBase()
, m_Type(ColliderType::NONE)
{
	CollisionManager::GetInstance()->Register(this);
}

ColliderComponent::~ColliderComponent()
{
	CollisionManager::GetInstance()->Unregister(this);
}

void ColliderComponent::Draw()
{

}
