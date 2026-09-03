#pragma once

#include "DxLib.h"
#include "../GameObject/GameObject.h"

class BulletBase : public GameObject
{
public:
	BulletBase();
	virtual ~BulletBase();

public:
	virtual void Init();
	virtual void Load();
	virtual void Start();
	virtual void Step() = 0;
	virtual void Update();
	virtual void Draw() = 0;
	virtual void Fin();
	
public:
	bool IsActive() { return m_IsActive; }

	void SetActive(bool isActive) { m_IsActive = isActive; }

	void SetPosition(VECTOR pos) { m_Transform.SetPosition(pos); }

	VECTOR GetPos() const { return m_Transform.GetPosition(); }

protected:
	bool m_IsActive;

	VECTOR m_Velocity;

	int m_Handle;
};
