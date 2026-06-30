#include "GameObject.h"

GameObject::GameObject()
: m_IsActive(true)
, m_Type(GameObjectType::NONE)
, m_Transform({})
, m_UserServerTransform(false)
, m_ServerTransform({})
{
}

void GameObject::Move(const VECTOR& vec)
{
	VECTOR pos = m_Transform.GetPosition();
	pos = VAdd(pos, vec);
	m_Transform.SetPosition(pos);
}

void GameObject::OverlapGameObject(GameObject& other)
{
}
