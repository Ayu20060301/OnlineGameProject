#pragma once

#include <vector>
#include "../Memory/Memory.h"
#include "../Component/ComponentBase.h"
#include "../Component/Transform.h"
#include "../Component/Splite.h"
#include "../Component//Controller2D.h"


enum class GameObjectType
{
	NONE = -1,
	PLAYER
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	void SetActive(bool isActive) { m_IsActive = isActive; }
	void SetPosition(const VECTOR& pos) { m_Transform.SetPosition(pos);}
	void SetRotation(const VECTOR& rot) { m_Transform.SetRotation(rot);}
	void SetScale(const VECTOR& scale) { m_Transform.SetScale(scale); }

	bool IsActive() const { return m_IsActive; }
	GameObjectType GetType() const { return m_Type; }
	const VECTOR& GetPosition() const { return m_Transform.GetPosition(); }
	const VECTOR& GetRotatition() const { return m_Transform.GetRotation(); }
	const VECTOR& GetScale() const { return m_Transform.GetScale(); }
	const Transform& GetRenderTransform() const { return m_UserServerTransform ? m_ServerTransform : m_Transform; }

	void Move(const VECTOR& vec);

	virtual void OverlapGameObject(GameObject& other);

	//コンポーネント追加
	template <class T>
	T* AddComponent()
	{
		UniquePtr<T>component = MakeUnique<T>();
		component->SetOwner(this);
		T* rawPtr = component.get();
		m_Components.emplace_back(std::move(component));

		return rawPtr;
	}

protected:

	bool m_IsActive = true;

	//オブジェクトタイプ
	GameObjectType m_Type;

	//トランスフォームは必ず持つ
	Transform m_Transform;

	//以下ネットワーク用
	bool m_UserServerTransform;
	Transform m_ServerTransform;

private:

	std::vector<SharedPtr<ComponentBase>> m_Components;
};
