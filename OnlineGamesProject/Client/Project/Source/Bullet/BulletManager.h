#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <list>
#include <DxLib.h>
#include "../Network/NetworkCommonParam.h"

class Bullet;
class NetworkBullet;
class Client;

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

	void FireBullet(VECTOR playerPos);

	//弾の生成
	Bullet& CreateBullet();


	//ネットワーク関係
	void SyncServerTransform(Network::ResponseBulletTransformData data);
	void DieBullet(int bulletID);

	//弾を全削除
	void Clear();

private:
	std::list<UniquePtr<Bullet>> m_Bullets;
};