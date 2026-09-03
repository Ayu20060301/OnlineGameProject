#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <list>
#include <DxLib.h>

class BulletBase;

class BulletManager : public Singleton<BulletManager>
{
public:
	BulletManager();
	virtual ~BulletManager();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	//’e¶¬
	BulletBase& CreateStraightBullet(VECTOR pos,VECTOR velocity);

	//’e‚ğ‘Síœ
	void Clear();

private:
	std::list<UniquePtr<BulletBase>> m_Bullets;
};