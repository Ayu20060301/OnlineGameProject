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
	void Init();
	void Update();
	void Draw();

	Bullet& CreateBullet(); //’e‚Ì¶¬
	void RemoveBullet(int handle); //’e‚Ìíœ

	int GetBulletCount() const { return static_cast<int>(m_Bullets.size()); } //’e‚Ì”
	std::vector<SharedPtr<Bullet>> GetBullets() const { return m_Bullets; } //‘S’eæ“¾
private:
	std::vector<SharedPtr<Bullet>> m_Bullets;

};
