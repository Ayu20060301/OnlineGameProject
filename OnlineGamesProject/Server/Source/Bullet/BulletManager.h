#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <vector>

class Bullet;

class BulletManager : public Singleton<BulletManager>
{
public:
	BulletManager();
	~BulletManager() = default;

public:
	void Draw();

	Bullet& CreateBullet();
	void RemoveBullet(int handle);

	int GetBulletCount() const { return static_cast<int>(m_Bullets.size()); }
	std::vector<SharedPtr<Bullet>> GetBullets() const { return m_Bullets; }
	Bullet* GetBullet(int id) const;

private:
	std::vector<SharedPtr<Bullet>> m_Bullets;
};
