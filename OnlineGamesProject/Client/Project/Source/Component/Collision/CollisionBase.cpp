#include "CollisionBase.h"
#include "CollisionManager.h"

CollisionBase::CollisionBase()
{
	m_Id = COLLISION_TYPE_NONE;
	m_Tag = COLLISION_TAG_NONE;
	m_Active = false;
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
}

CollisionBase::~CollisionBase()
{
}
