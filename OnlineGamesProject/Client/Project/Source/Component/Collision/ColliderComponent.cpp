#include "ColliderComponent.h"
#include "CollisionManager.h"

ColliderComponent::ColliderComponent() : ComponentBase()
, m_Type(ColliderType::NONE)
{
	
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Draw()
{

}
