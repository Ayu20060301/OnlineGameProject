#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <list>
#include <DxLib.h>
#include "../Network/NetworkCommonParam.h"

class BulletBase;
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
	//弾生成
	BulletBase& CreateStraightBullet(VECTOR pos,VECTOR velocity);

	//ネットワーク弾
	NetworkBullet& CreateNetworkBullet(int id, int ownerID, VECTOR pos, VECTOR velocity);

	//ネットワーク関係
	void SyncServerTransform(Network::ResponseBulletTransformData data);
	void DieBullet(int bulletID);

	//弾を全削除
	void Clear();

private:
	//IDからネットワーク弾を検索
	NetworkBullet* FindNetworkBullet(int bulletID);
private:
	std::list<UniquePtr<BulletBase>> m_Bullets;
};