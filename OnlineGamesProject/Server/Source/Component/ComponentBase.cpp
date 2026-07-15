#include "ComponentBase.h"
#include "../GameObject/GameObject.h"

ComponentBase::ComponentBase()
: m_Owner(nullptr)
, m_IsActive(true)
{
}

bool ComponentBase::IsActive() const
{
	return (m_IsActive && m_Owner && m_Owner->IsActive());
}
