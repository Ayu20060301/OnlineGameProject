#pragma once

#include "ColliderComponent.h"
#include "DxLib.h"

class AABB3D : public ColliderComponent
{
public:
	AABB3D();
	virtual ~AABB3D() = default;

	void Draw();

	void SetCenter(const VECTOR& center) { m_Center = center; }
	void SetSize(const VECTOR& size) { m_Center = size; }


	CollisionResult CheckCollide(const ColliderComponent& other) const override;
	CollisionResult CheckCollideAABB(const AABB3D& other) const;

private:
	VECTOR m_Center;
	VECTOR m_Size;
};


class AABB2D : public ColliderComponent
{
public:
	AABB2D();
	virtual ~AABB2D() = default;

	void Draw();

	void SetCenter(const VECTOR& center) { m_Center = center; }
	void SetSize(const VECTOR& size) { m_Center = size; }


	CollisionResult CheckCollide(const ColliderComponent& other) const override;
	CollisionResult CheckCollideAABB(const AABB2D& other) const;

private:
	VECTOR m_Center;
	VECTOR m_Size;
};
