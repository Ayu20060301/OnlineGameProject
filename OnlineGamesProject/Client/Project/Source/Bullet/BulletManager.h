#pragma once

#include "DxLib.h"
#include "BulletParameter.h"
#include "../Singleton/Singleton.h"
#include <vector>

class BulletBase;

class BulletManager : public Singleton<BulletManager>
{
public:
	BulletManager();
	~BulletManager();

public:
	void Load();
	void Step();
	void Draw();
	void Fin();

public:
	std::vector<BulletBase*> GetBullets() const { return m_Bullets; }

	void SetupBullet(int id);
	BulletBase* FireBullet(int id, VECTOR pos, VECTOR vec);
	const BulletParameter* GetBulletParameter(int id);

private:
	BulletBase* CreateBullet(int id);

private:
	static BulletManager* m_Instance;

	// 使用するバレットのクローン元
	std::vector<BulletBase*> m_OriginalBullets;

	// vectorのオブジェクトプールで管理してみる
	std::vector<BulletBase*> m_Bullets;
};
