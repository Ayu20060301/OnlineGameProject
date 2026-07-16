#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Draw()
{
}

void CollisionManager::Fin()
{
}

CollisionAABB* CollisionManager::CreateAABB()
{
	return nullptr;
}

CollisionSphere* CollisionManager::CreateSphere()
{
	return nullptr;
}

CollisionBase* CollisionManager::CreateCollision(int id)
{
	return nullptr;
}

void CollisionManager::CheckCollision()
{
}

void CollisionManager::CheckPlayerAndBlock()
{
}

void CollisionManager::CheckPlayerAndBullet()
{
}

void CollisionManager::CheckPlayerAndItem()
{
}

void CollisionManager::CheckBlockAndBullet()
{
}
