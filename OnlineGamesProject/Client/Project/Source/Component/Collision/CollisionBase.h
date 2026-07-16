#pragma once

#pragma once

#include "DxLib.h"

class CollisionBase
{
public:
	CollisionBase();
	virtual ~CollisionBase();

public:
	virtual void Draw() = 0;

	void SetTargetPos(VECTOR* targetPos) { m_TargetPos = targetPos; }
	void SetLocalPos(VECTOR localPos) { m_LocalPos = localPos; }
	void SetActive(bool active) { m_Active = active; }
	void SetTag(int tag) { m_Tag = tag; }

	VECTOR GetTargetPos() const { return *m_TargetPos; }
	VECTOR GetLocalPos() const { return m_LocalPos; }
	bool IsActive() const { return m_Active; }
	int GetID() const { return m_Id; }
	int GetTag() const { return m_Tag; }

protected:
	int m_Id;
	int m_Tag;
	bool m_Active;
	// 対象の座標
	VECTOR* m_TargetPos;
	// 対象の座標を原点としたローカル座標
	VECTOR m_LocalPos;

};
