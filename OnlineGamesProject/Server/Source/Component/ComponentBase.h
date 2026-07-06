#pragma once

class GameObject;

class ComponentBase
{
public:
	ComponentBase();
	virtual ~ComponentBase() = default;

	void SetOwner(GameObject* owner) { m_Owner = owner; }
	void SetActive(bool isActive) { m_IsActive = isActive; }

	bool IsActive() const;
	GameObject* GetOwner() { return m_Owner; }

protected:
	bool m_IsActive;
	GameObject* m_Owner;
};
